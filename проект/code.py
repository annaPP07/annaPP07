import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from IPython.display import HTML, display

# Проверим, что train_ds и другие есть
print("Тип train_ds:", type(train_ds))
print("Тип val_ds:", type(val_ds))
print("Классов:", num_classes, "Примеры классов:", class_names[:5])

# ------ 3.1. ПАРАМЕТРЫ МОДЕЛИ (минимум, но настраиваемые) ------

MODEL_CONFIG = {
    "input_shape": (IMG_SIZE[0], IMG_SIZE[1], 3),
    "conv_filters": [32, 64],   # можно добавить 128
    "dense_units": 128,
    "dropout": 0.4,
    "learning_rate": 1e-3,
    "epochs": 15,                # маленькое число для скорости
    "limit_train_batches": 200,  # ограничим количество батчей 150
    "limit_val_batches": 100,
    "limit_test_batches": 100,
}

# Ограничение числа батчей (ускорение)
def limit_ds(ds, max_batches):
    if max_batches is None:
        return ds
    return ds.take(max_batches)

train_ds_small = limit_ds(train_ds, MODEL_CONFIG["limit_train_batches"])
val_ds_small   = limit_ds(val_ds,   MODEL_CONFIG["limit_val_batches"])
test_ds_small  = limit_ds(test_ds,  MODEL_CONFIG["limit_test_batches"])

# ------ 3.2. АУГМЕНТАЦИЯ И МОДЕЛЬ ------

data_augmentation = keras.Sequential([
    layers.RandomFlip("horizontal"),
    layers.RandomRotation(0.25),
])

def build_cnn(config, num_classes):
    inputs = keras.Input(shape=config["input_shape"])
    x = data_augmentation(inputs)
    x = layers.Rescaling(1./255)(x)

    for f in config["conv_filters"]:
        x = layers.Conv2D(f, 3, padding="same", activation="relu")(x)
        x = layers.MaxPooling2D(2)(x)

    x = layers.GlobalAveragePooling2D()(x)
    x = layers.Dense(config["dense_units"], activation="relu")(x)
    x = layers.Dropout(config["dropout"])(x)
    outputs = layers.Dense(num_classes, activation="softmax")(x)

    model = keras.Model(inputs, outputs)
    model.compile(
        optimizer=keras.optimizers.Adam(config["learning_rate"]),
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"],
    )
    return model

print("\n🏗 Создаём модель...")
model = build_cnn(MODEL_CONFIG, num_classes)
model.summary()

# ------ 3.3. ОБУЧЕНИЕ ------

print("\n🎯 Обучаем (ускоренный режим)...")
history = model.fit(
    train_ds_small,
    validation_data=val_ds_small,
    epochs=MODEL_CONFIG["epochs"],
    verbose=1,
)

print("\n📏 Оцениваем на небольшом тестовом наборе...")
test_loss, test_acc = model.evaluate(test_ds_small, verbose=1)
print(f"Test accuracy (small test): {test_acc:.4f}, loss: {test_loss:.4f}")

hist = history.history

# ------ 3.4. ГРАФИКИ ------

plt.figure(figsize=(10,4))
plt.subplot(1,2,1)
plt.plot(hist["accuracy"], label="train")
plt.plot(hist["val_accuracy"], label="val")
plt.title("Точность"); plt.xlabel("Эпоха"); plt.ylabel("Accuracy")
plt.grid(); plt.legend()

plt.subplot(1,2,2)
plt.plot(hist["loss"], label="train")
plt.plot(hist["val_loss"], label="val")
plt.title("Потери"); plt.xlabel("Эпоха"); plt.ylabel("Loss")
plt.grid(); plt.legend()
plt.tight_layout()
plt.show()
