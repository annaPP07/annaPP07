import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# --- Encoder ---
class Encoder(tf.keras.layers.Layer):
    def __init__(self, latent_dim):
        super(Encoder, self).__init__()
        self.latent_dim = latent_dim
        self.conv1 = tf.keras.layers.Conv2D(32, 3, strides=2, activation='relu', padding='same')
        self.conv2 = tf.keras.layers.Conv2D(64, 3, strides=2, activation='relu', padding='same')
        self.flatten = tf.keras.layers.Flatten()
        self.dense = tf.keras.layers.Dense(latent_dim * 2)  # mean и log_var

    def call(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.flatten(x)
        z_params = self.dense(x)
        mean, log_variance = tf.split(z_params, num_or_size_splits=2, axis=1)
        return mean, log_variance, x  # возвращаем x для совместимости, хотя не используется

# --- Decoder ---
class Decoder(tf.keras.layers.Layer):
    def __init__(self, latent_dim=20):
        super(Decoder, self).__init__()
        self.latent_dim = latent_dim
        self.dense = tf.keras.layers.Dense(7 * 7 * 32, activation='relu')
        self.reshape = tf.keras.layers.Reshape((7, 7, 32))
        self.conv2d_t1 = tf.keras.layers.Conv2DTranspose(32, 3, strides=2, activation='relu', padding='same')
        self.conv2d_t2 = tf.keras.layers.Conv2DTranspose(32, 3, strides=2, activation='relu', padding='same')
        self.conv2d_t3 = tf.keras.layers.Conv2DTranspose(1, 3, strides=1, activation='sigmoid', padding='same')

    def call(self, z):
        x = self.dense(z)
        x = self.reshape(x)
        x = self.conv2d_t1(x)
        x = self.conv2d_t2(x)
        x = self.conv2d_t3(x)
        return x

# --- VAE Model ---
class VAE(tf.keras.Model):
    def __init__(self, latent_dim=20, beta=1.0):
        super(VAE, self).__init__()
        self.latent_dim = latent_dim
        self.beta = beta

        self.encoder = Encoder(latent_dim)
        self.decoder = Decoder(latent_dim)

    def encode(self, x):
        mean, log_variance, _ = self.encoder(x)
        return mean, log_variance

    def sample(self, mean, log_variance):
        batch_size = tf.shape(mean)[0]
        epsilon = tf.random.normal(shape=(batch_size, self.latent_dim))
        z = mean + tf.exp(0.5 * log_variance) * epsilon  # reparameterization trick
        return z

    def decode(self, z):
        return self.decoder(z)

    def call(self, x):
        mean, log_variance = self.encode(x)
        z = self.sample(mean, log_variance)
        reconstructed = self.decode(z)
        return mean, log_variance, reconstructed

    def reconstruction_loss(self, original, reconstructed):
        # Binary cross-entropy для нормализованных изображений [0,1]
        bce = tf.keras.losses.BinaryCrossentropy(reduction=tf.keras.losses.Reduction.SUM)
        return bce(original, reconstructed)

    def kl_divergence_loss(self, mean, log_variance):
        # KL = -0.5 * sum(1 + log_var - mean^2 - exp(log_var))
        kl = -0.5 * tf.reduce_sum(1 + log_variance - tf.square(mean) - tf.exp(log_variance), axis=1)
        return tf.reduce_mean(kl)

    def vae_loss(self, original, reconstructed, mean, log_variance):
        recon_loss = self.reconstruction_loss(original, reconstructed)
        kl_loss = self.kl_divergence_loss(mean, log_variance)
        total_loss = recon_loss + self.beta * kl_loss
        return total_loss

    @tf.function
    def train_step(self, x):
        with tf.GradientTape() as tape:
            mean, log_variance, reconstructed = self(x)
            loss = self.vae_loss(x, reconstructed, mean, log_variance)

        gradients = tape.gradient(loss, self.trainable_variables)
        self.optimizer.apply_gradients(zip(gradients, self.trainable_variables))
        return loss

    def generate_new_images(self, num_images=10):
        z = tf.random.normal(shape=(num_images, self.latent_dim))
        generated = self.decode(z)
        return generated

    def interpolate(self, x1, x2, n_steps=10):
        """Интерполяция между двумя изображениями в латентном пространстве"""
        mean1, log_var1 = self.encode(tf.expand_dims(x1, 0))
        mean2, log_var2 = self.encode(tf.expand_dims(x2, 0))

        z1 = self.sample(mean1, log_var1)
        z2 = self.sample(mean2, log_var2)

        # Линейная интерполяция
        alphas = tf.linspace(0.0, 1.0, n_steps)
        interpolated = []
        for alpha in alphas:
            z = (1 - alpha) * z1 + alpha * z2
            img = self.decode(z)
            interpolated.append(img[0])
        return interpolated

# --- Подготовка данных (MNIST) ---
(x_train, _), (x_test, _) = tf.keras.datasets.mnist.load_data()
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

x_train = x_train[..., tf.newaxis]  # (60000, 28, 28, 1)
x_test = x_test[..., tf.newaxis]

train_dataset = tf.data.Dataset.from_tensor_slices(x_train).shuffle(60000).batch(128)
test_dataset = tf.data.Dataset.from_tensor_slices(x_test).batch(128)

# --- Обучение ---
latent_dim = 20
vae = VAE(latent_dim=latent_dim, beta=1.0)
vae.compile(optimizer=tf.keras.optimizers.Adam(1e-4))

epochs = 10
for epoch in range(epochs):
    print(f"Epoch {epoch + 1}/{epochs}")
    for step, batch in enumerate(train_dataset):
        loss = vae.train_step(batch)
        if step % 100 == 0:
            print(f"Step {step}, Loss: {loss:.4f}")

# --- Генерация новых изображений ---
generated_images = vae.generate_new_images(num_images=10)
plt.figure(figsize=(10, 2))
for i in range(10):
    plt.subplot(1, 10, i + 1)
    plt.imshow(generated_images[i, :, :, 0], cmap='gray')
    plt.axis('off')
plt.suptitle('Сгенерированные изображения')
plt.show()

# --- Интерполяция ---
# Выбираем два случайных изображения
idx1, idx2 = 0, 1
img1, img2 = x_test[idx1], x_test[idx2]

interpolated_images = vae.interpolate(img1, img2, n_steps=10)

plt.figure(figsize=(15, 2))
for i, img in enumerate(interpolated_images):
    plt.subplot(1, 10, i + 1)
    plt.imshow(img[:, :, 0], cmap='gray')
    plt.axis('off')
plt.suptitle('Интерполяция в латентном пространстве')
plt.show()
