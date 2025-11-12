1. Бинарная куча 
Определение:
Бинарная куча — это полное двоичное дерево, удовлетворяющее свойству кучи: для любой вершины её ключ не меньше (в max‑heap) или не больше (в min‑heap) ключей её потомков. Обычно реализуется на массиве, где для вершины с индексом i левый потомок имеет индекс 2i+1, правый — 2i+2, а родитель — ⌊(i−1)/2⌋.
Python
Модуль: heapq (встроенная библиотека).
Синтаксис:
Создание: пустой список heap = [].
Вставка: heapq.heappush(heap, value).
Извлечение минимума: heapq.heappop(heap).
Преобразование списка в кучу: heapq.heapify(lst).
Java
Класс: java.util.PriorityQueue.
Синтаксис:
Создание: PriorityQueue<Integer> heap = new PriorityQueue<>(); (min‑heap).
Вставка: heap.add(value) или heap.offer(value).
Извлечение минимума: heap.poll().
Просмотр минимума: heap.peek().
C++
Контейнер: std::priority_queue (из <queue>).
Синтаксис:
Создание min‑heap:
std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
Вставка: heap.push(value).
Извлечение минимума: heap.top() + heap.pop().
Проверка пустоты: heap.empty().

2. Биномиальная куча 
Определение:
Биномиальная куча — это набор биномиальных деревьев, каждое из которых удовлетворяет свойству кучи. Биномиальное дерево Bk порядка k имеет 2k
вершин, высоту k, и корень с k потомками, являющимися корнями биномиальных деревьев порядков k−1,k−2,…,0. Куча поддерживает эффективное объединение (O(logn)).
Python
Основа: классы для узла и кучи.
Синтаксис:
Узел: class BinomialNode: ... (поля: key, children, parent).
Куча: class BinomialHeap: ... (поле: список корней trees).
Операции: merge_trees(), insert(), extract_min() — реализуются вручную.
Java
Основа: классы BinomialNode и BinomialHeap.
Синтаксис:
Узел: поля int key, List<BinomialNode> children, BinomialNode parent.
Куча: поле List<BinomialNode> trees.
Операции: реализуются через методы (например, link(), union()).
C++
Основа: структуры BinomialNode и BinomialHeap.
Синтаксис:
Узел: поля int key, std::vector<BinomialNode*> children, BinomialNode* parent.
Куча: поле std::vector<BinomialNode*> trees.
Операции: реализуются через указатели и ручные манипуляции.

3. Куча Фибоначчи 
Определение:
Куча Фибоначчи — это набор деревьев, удовлетворяющих свойству кучи, с отложенными операциями (например, объединение, уменьшение ключа). Ключевая особенность — амортизированная сложность операций: вставка O(1), извлечение минимума O(logn), уменьшение ключа O(1). Деревья не обязаны быть сбалансированными, что позволяет откладывать «работу» по поддержанию структуры.
Python
Основа: классы для узла и кучи.
Синтаксис:
Узел: class FibNode: ... (поля: key, degree, parent, child, next, prev, mark).
Куча: class FibonacciHeap: ... (поля: min_node, total_nodes).
Операции: insert(), extract_min(), decrease_key() — реализуются вручную.
Java
Основа: классы FibNode и FibonacciHeap.
Синтаксис:
Узел: поля int key, int degree, FibNode parent, child, next, prev, boolean mark.
Куча: поля FibNode minNode, int totalNodes.
Операции: реализуются через ручные ссылки.
C++
Основа: структуры FibNode и FibonacciHeap.
Синтаксис:
Узел: поля int key, int degree, FibNode* parent, child, next, prev, bool mark.
Куча: поля FibNode* minNode, int totalNodes.
Операции: реализуются через указатели.

4. Хэш‑таблица 
Определение:
Хэш‑таблица — это структура данных для хранения пар «ключ‑значение», использующая хэш‑функцию для преобразования ключа в индекс массива. Основные операции: вставка, поиск, удаление. При коллизиях применяются методы разрешения (цепочки, открытая адресация). Средняя сложность операций — O(1).
Python
Синтаксис:
Вставка/обновление: ht['key'] = value
Получение: ht['key'] или ht.get('key', default)
Удаление: del ht['key'] или ht.pop('key')
Проверка ключа: 'key' in ht
Java
Синтаксис:
Вставка: ht.put(key, value)
Получение: ht.get(key)
Удаление: ht.remove(key)
Проверка ключа: ht.containsKey(key)
C++
Синтаксис:
Вставка: ht[key] = value или ht.insert({key, value})
Получение: ht[key] (создаёт ключ, если нет) или через find()
Удаление: ht.erase(key)
Проверка ключа: ht.find(key) != ht.end() (C++20: ht.contains(key))
