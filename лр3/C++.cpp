1. Бинарная куча 
#include <iostream>
#include <queue>
#include <vector>

class MinHeap {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
    
public:
    void push(int item) {
        heap.push(item);
    }
    
    int pop() {
        int item = heap.top();
        heap.pop();
        return item;
    }
    
    int peek() const {
        return heap.top();
    }
    
    size_t size() const {
        return heap.size();
    }
};

// Пример использования
int main() {
    MinHeap h;
    h.push(5);
    h.push(3);
    h.push(8);
    std::cout << h.pop() << std::endl;  // 3
    std::cout << h.peek() << std::endl;   // 5
    return 0;
}

2. Биномиальная куча
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Узел биномиального дерева
template <typename T>
struct BinomialNode {
    T key;
    int degree;  // ранг дерева (количество детей)
    BinomialNode<T>* parent;
    BinomialNode<T>* child;   // первый ребёнок
    BinomialNode<T>* sibling; // следующий брат

    explicit BinomialNode(T k) 
        : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

// Биномиальная куча
template <typename T>
class BinomialHeap {
private:
    BinomialNode<T>* head;  // указатель на первый корень (список корней по возрастанию ранга)

    // Слияние двух биномиальных деревьев одинакового ранга
    BinomialNode<T>* mergeTrees(BinomialNode<T>* t1, BinomialNode<T>* t2) {
        // Делаем t1 родителем t2 (t1.key <= t2.key)
        if (t1->key > t2->key) {
            swap(t1, t2);
        }
        
        t2->parent = t1;
        t2->sibling = t1->child;
        t1->child = t2;
        t1->degree++;
        
        return t1;  // новое дерево с корнем t1
    }

    // Объединение списков корней и консолидация (устранение деревьев одинакового ранга)
    void consolidate() {
        if (!head) return;

        // Вектор для хранения деревьев по рангам (максимум 64 ранга)
        vector<BinomialNode<T>*> trees(64, nullptr);
        BinomialNode<T>* current = head;
        head = nullptr;

        while (current) {
            BinomialNode<T>* next = current->sibling;
            current->sibling = nullptr;  // отсоединяем от списка
            
            int d = current->degree;
            // Объединяем деревья одинакового ранга
            while (trees[d]) {
                current = mergeTrees(current, trees[d]);
                trees[d] = nullptr;
                d++;
            }
            trees[d] = current;
            current = next;
        }

        // Собираем итоговый список корней
        for (auto& tree : trees) {
            if (tree) {
                tree->sibling = head;
                head = tree;
            }
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    // Вставка нового элемента
    void insert(T key) {
        BinomialHeap tempHeap;
        tempHeap.head = new BinomialNode<T>(key);
        merge(tempHeap);
    }

    // Слияние с другой биномиальной кучей
    void merge(BinomialHeap& other) {
        // Объединяем списки корней (как в сортировке слиянием)
        BinomialNode<T>* newHead = nullptr;
        BinomialNode<T>** curr = &newHead;
        BinomialNode<T>* h1 = head;
        BinomialNode<T>* h2 = other.head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *curr = h1;
                h1 = h1->sibling;
            } else {
                *curr = h2;
                h2 = h2->sibling;
            }
            curr = &((*curr)->sibling);
        }

        *curr = (h1 ? h1 : h2);

        head = newHead;
        other.head = nullptr;  // обнуляем вторую кучу после слияния

        // Консолидация: объединяем деревья одинакового ранга
        consolidate();
    }

    // Поиск минимального ключа
    T findMin() const {
        if (!head) {
            throw runtime_error("Heap is empty");
        }

        T minKey = head->key;
        BinomialNode<T>* curr = head->sibling;

        while (curr) {
            if (curr->key < minKey) {
                minKey = curr->key;
            }
            curr = curr->sibling;
        }

        return minKey;
    }

    // Проверка на пустоту
    bool empty() const {
        return head == nullptr;
    }

    // Деструктор (очистка памяти)
    ~BinomialHeap() {
        clear();
    }

    void clear() {
        while (head) {
            BinomialNode<T>* temp = head;
            head = head->sibling;
            delete temp;
        }
    }

    // Вывод структуры кучи (для отладки)
    void print() const {
        cout << "Binomial Heap: ";
        BinomialNode<T>* curr = head;
        while (curr) {
            cout << "B" << curr->degree << "(" << curr->key << ") ";
            curr = curr->sibling;
        }
        cout << endl;
    }
};

// Пример использования
int main() {
    BinomialHeap<int> heap;

    // Вставляем элементы
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(3);
    heap.insert(15);

    cout << "После вставки элементов:" << endl;
    heap.print();

    cout << "Минимальный элемент: " << heap.findMin() << endl;

    // Создаем вторую кучу
    BinomialHeap<int> heap2;
    heap2.insert(7);
    heap2.insert(12);

    cout << "Вторая куча:" << endl;
    heap2.print();

    // Сливаем кучи
    heap.merge(heap2);
    cout << "После слияния:" << endl;
    heap.print();

    cout << "Новый минимум: " << heap.findMin() << endl;

    return 0;
}


3. Куча Фибоначчи
#include <iostream>
#include <stdexcept>

template<typename T>
struct FibNode {
    T key;
    int degree;
    bool marked;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;

    explicit FibNode(T k) : key(k), degree(0), marked(false),
        parent(nullptr), child(nullptr), left(this), right(this) {}
};

template<typename T>
class FibonacciHeap {
private:
    FibNode<T>* minNode;
    int numNodes;

    void link(FibNode<T>* y, FibNode<T>* x);
    void consolidate();
    void cut(FibNode<T>* x, FibNode<T>* y);
    void cascadingCut(FibNode<T>* y);


public:
    FibonacciHeap() : minNode(nullptr), numNodes(0) {}
    ~FibonacciHeap();

    void insert(T key);
    T findMin() const;
    T extractMin();
    void decreaseKey(FibNode<T>* x, T newKey);
    void merge(FibonacciHeap<T>& other);
    bool empty() const { return numNodes == 0; }
    int size() const { return numNodes; }
};

// Деструктор
template<typename T>
FibonacciHeap<T>::~FibonacciHeap() {
    while (!empty()) {
        extractMin();
    }
}

// Вставка нового элемента
template<typename T>
void FibonacciHeap<T>::insert(T key) {
    FibNode<T>* node = new FibNode<T>(key);

    if (minNode == nullptr) {
        minNode = node;
    } else {
        // Вставляем node в список корней справа от minNode
        node->right = minNode->right;
        node->left = minNode;
        minNode->right->left = node;
        minNode->right = node;

        if (node->key < minNode->key) {
            minNode = node;
        }
    }
    numNodes++;
}

// Поиск минимума
template<typename T>
T FibonacciHeap<T>::findMin() const {
    if (minNode == nullptr) {
        throw std::runtime_error("Heap is empty");
    }
    return minNode->key;
}

// Извлечение минимума
template<typename T>
T FibonacciHeap<T>::extractMin() {
    if (minNode == nullptr) {
        throw std::runtime_error("Heap is empty");
    }

    T minKey = minNode->key;
    FibNode<T>* z = minNode;

    // Добавляем детей z в список корней
    if (z->child != nullptr) {
        FibNode<T>* child = z->child;
        do {
            child->parent = nullptr;
            child = child->right;
        } while (child != z->child);

        // Сливаем списки: корни кучи и дети z
        FibNode<T>* a = minNode->right;
        FibNode<T>* b = z->child;

        minNode->right = b;
        b->left->right = a;
        a->left = b->left;
        b->left = minNode;
    }

    // Удаляем z из списка корней
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
        minNode = nullptr;  // Куча стала пустой
    } else {
        minNode = z->right;  // Временный минимум
        consolidate();       // Перестраиваем кучу
    }

    numNodes--;
    delete z;
    return minKey;
}

// Объединение двух куч
template<typename T>
void FibonacciHeap<T>::merge(FibonacciHeap<T>& other) {
    if (other.minNode == nullptr) return;
    if (minNode == nullptr) {
        minNode = other.minNode;
    } else {
        // Сливаем списки корней
        FibNode<T>* a = minNode->right;
        FibNode<T>* b = other.minNode->right;

        minNode->right = b;
        b->left->right = a;
        a->left = b->left;
        b->left = minNode;

        if (other.minNode->key < minNode->key) {
            minNode = other.minNode;
        }
    }
    numNodes += other.numNodes;
    other.minNode = nullptr;
    other.numNodes = 0;
}

// Уменьшение ключа
template<typename T>
void FibonacciHeap<T>::decreaseKey(FibNode<T>* x, T newKey) {
    if (newKey > x->key) {
        throw std::invalid_argument("New key is greater than current key");
    }
    x->key = newKey;
    FibNode<T>* y = x->parent;

    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }

    if (x->key < minNode->key) {
        minNode = x;
    }
}

// Вспомогательные методы

template<typename T>
void FibonacciHeap<T>::link(FibNode<T>* y, FibNode<T>* x) {
    // Делаем y ребёнком x
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->marked = false;
}

template<typename T>
void FibonacciHeap<T>::consolidate() {
    int D = numNodes + 1;  // Максимальная возможная степень
    auto* A = new FibNode<T>*[D]();  // Массив для деревьев по степеням

    for (int i = 0; i < D; ++i) {
        A[i] = nullptr;
    }

    FibNode<T>* w = minNode;
    int rootCount = 0;
    if (w != nullptr) {
        rootCount = 1;
        w = w->right;
        while (w != minNode) {
            rootCount++;
            w = w->right;
        }
    }

    while (rootCount > 0) {
        int d = w->degree;
        FibNode<T>* x = w;
        w = w->right;
        rootCount--;

        while (A[d] != nullptr) {
            FibNode<T>* y = A[d];
            if (x->key > y->key) {
                std::swap(x, y);  // x — дерево с меньшим корнем
            }
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }

    minNode = nullptr;
    for (int i = 0; i < D; ++i) {
        if (A[i] != nullptr) {
            if (minNode == nullptr) {
                minNode = A[i];
                minNode->left = minNode;
                minNode->right = minNode;
            } else {
                // Вставляем A[i] в список корней
                A[i]->right = minNode->right;
                A[i]->left = minNode;
                minNode->right->left = A[i];
                minNode->right = A[i];

                if (A[i]->key < minNode->key) {
                    minNode = A[i];
                }
            }
        }
    }
    delete[] A;
}

template<typename T>
void FibonacciHeap<T>::cut(FibNode<T>* x, FibNode<T>* y) {
    // Удаляем x из списка детей y
    if (x == x->right) {
        y->child

4.Хэш‑таблица
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>

template<typename K, typename V>
class HashTable {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    size_t capacity;
    size_t count;

    // Хэш‑функция (используем std::hash)
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    explicit HashTable(size_t cap = 16) 
        : capacity(cap), count(0) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        size_t idx = hash(key);
        auto& chain = table[idx];

        // Проверяем, есть ли ключ уже в цепочке
        for (auto& pair : chain) {
            if (pair.first == key) {
                pair.second = value;  // Обновляем значение
                return;
            }
        }

        // Добавляем новую пару
        chain.emplace_back(key, value);
        count++;
    }

    bool find(const K& key, V& value) const {
        size_t idx = hash(key);
        const auto& chain = table[idx];

        for (const auto& pair : chain) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const K& key) {
        size_t idx = hash(key);
        auto& chain = table[idx];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                count--;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        V dummy;
        return find(key, dummy);
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }
};

// Пример использования
int main() {
    HashTable<std::string, int> ht(8);

    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("cherry", 30);

    int val;
    if (ht.find("apple", val)) {
        std::cout << "apple: " << val << std::endl;
    }

    ht.remove("banana");
    std::cout << "Size: " << ht.size() << std::endl;

    return 0;
}
