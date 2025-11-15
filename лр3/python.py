1. Бинарная куча
import heapq
class MinHeap:
    def __init__(self):
        self.heap = []
    
    def push(self, item):
        heapq.heappush(self.heap, item)
    
    def pop(self):
        return heapq.heappop(self.heap)
    
    def peek(self):
        return self.heap[0] if self.heap else None
    
    def size(self):
        return len(self.heap)
if __name__ == "__main__":
    h = MinHeap()
    h.push(5)
    h.push(3)
    h.push(8)
    print(h.pop())  # 3
    print(h.peek()) # 5
# Вывод:  3 5

2. Биномиальная куча
class BinomialNode:
    def __init__(self, key):
        self.key = key
        self.parent = None
        self.child = None
        self.sibling = None
        self.degree = 0  # ранг дерева


class BinomialHeap:
    def __init__(self):
        self.head = None  # список корней по возрастанию ранга

    def _merge_trees(self, t1, t2):
        """Сливает два дерева одинакового ранга (t1.key <= t2.key)"""
        t2.parent = t1
        t2.sibling = t1.child
        t1.child = t2
        t1.degree += 1
        return t1

    def merge(self, other):
        """Сливает две биномиальные кучи"""
        # Шаг 1: сливаем списки корней (как в сортировке слиянием)
        self.head = self._merge_root_lists(self.head, other.head)
        
        # Шаг 2: объединяем деревья одинакового ранга
        if not self.head:
            return
            
        prev = None
        curr = self.head
        next_node = curr.sibling
        
        while next_node:
            if (curr.degree != next_node.degree or 
                (next_node.sibling and next_node.sibling.degree == curr.degree)):
                prev = curr
                curr = next_node
            elif curr.key <= next_node.key:
                curr.sibling = next_node.sibling
                self._merge_trees(curr, next_node)
            else:
                if prev:
                    prev.sibling = next_node
                else:
                    self.head = next_node
                self._merge_trees(next_node, curr)
                curr = next_node
            next_node = curr.sibling

    def _merge_root_lists(self, h1, h2):
        """Сливает два упорядоченных списка корней"""
        if not h1:
            return h2
        if not h2:
            return h1
            
        if h1.degree <= h2.degree:
            h1.sibling = self._merge_root_lists(h1.sibling, h2)
            return h1
        else:
            h2.sibling = self._merge_root_lists(h1, h2.sibling)
            return h2

    def insert(self, key):
        """Добавляет элемент"""
        new_heap = BinomialHeap()
        node = BinomialNode(key)
        new_heap.head = node
        self.merge(new_heap)

    def find_min(self):
        """Находит минимальный ключ"""
        if not self.head:
            return None
        min_node = self.head
        curr = self.head.sibling
        while curr:
            if curr.key < min_node.key:
                min_node = curr
            curr = curr.sibling
        return min_node.key

    def __str__(self):
        def tree_str(node, level=0):
            if not node:
                return ""
            s = "  " * level + f"{node.key} (deg={node.degree})\n"
            s += tree_str(node.child, level + 1)
            s += tree_str(node.sibling, level)
            return s
        return tree_str(self.head)
if __name__ == "__main__":
    heap = BinomialHeap()
    heap.insert(10)
    heap.insert(5)
    heap.insert(15)
    heap.insert(1)
    print("Куча:")
    print(heap)
    print("Минимум:", heap.find_min())

3. Куча Фибоначчи 
class FibonacciNode:
    def __init__(self, key):
        self.key = key
        self.parent = None
        self.child = None
        self.left = self  # двусвязный список братьев
        self.right = self
        self.degree = 0
        self.marked = False  # флаг маркирования

class FibonacciHeap:
    def __init__(self):
        self.min_node = None
        self.root_count = 0

    def _add_to_root_list(self, node):
        """Добавляет узел в список корней"""
        if self.min_node is None:
            self.min_node = node
        else:
            # Вставляем node слева от min_node
            node.left = self.min_node.left
            node.right = self.min_node
            self.min_node.left.right = node
            self.min_node.left = node

    def _remove_from_root_list(self, node):
        """Удаляет узел из списка корней"""
        if node.right == node:  # единственный узел
            self.min_node = None
        else:
            node.left.right = node.right
            node.right.left = node.left
            if node == self.min_node:
                self.min_node = node.right

    def insert(self, key):
        node = FibonacciNode(key)
        self._add_to_root_list(node)
        if self.min_node is None or node.key < self.min_node.key:
            self.min_node = node
        self.root_count += 1
        return node

    def find_min(self):
        if self.min_node is None:
            return None
        return self.min_node.key

    def merge(self, other):
        """Сливает две кучи (O(1))"""
        if other.min_node is None:
            return
        if self.min_node is None:
            self.min_node = other.min_node
        else:
            # Склеиваем списки корней
            self.min_node.right.left = other.min_node.left
            other.min_node.left.right = self.min_node.right
            self.min_node.right = other.min_node
            other.min_node.left = self.min_node
            if other.min_node.key < self.min_node.key:
                self.min_node = other.min_node
        self.root_count += other.root_count
        other.min_node = None
        other.root_count = 0

    def _consolidate(self):
        """Консолидация: объединяет деревья одинаковой степени"""
        if self.root_count == 0:
            return

        # Массив для хранения деревьев по степени (макс. степень ~ log n)
        max_degree = int(self.root_count.bit_length()) + 1
        trees = [None] * max_degree

        current = self.min_node
        roots = []
        # Собираем все корни
        while True:
            roots.append(current)
            current = current.right
            if current == self.min_node:
                break

        for root in roots:
            d = root.degree
            while trees[d] is not None:
                t = trees[d]
                if root.key > t.key:
                    root, t = t, root  # root становится родителем
                # Сливаем t в root
                t.left.right = t.right
                t.right.left = t.left
                t.parent = root
                t.child = root.child
                if root.child is not None:
                    t.right = root.child.right
                    t.left = root.child
                    root.child.right.left = t
                    root.child.right = t
                else:
                    t.right = t
                    t.left = t
                root.child = t
                t.marked = False
                root.degree += 1
                trees[d] = None
                d += 1
            trees[d] = root

        # Формируем новый список корней
        self.min_node = None
        self.root_count = 0
        for tree in trees:
            if tree is not None:
                self._add_to_root_list(tree)
                if self.min_node is None or tree.key < self.min_node.key:
                    self.min_node = tree
                self.root_count += 1

    def extract_min(self):
        if self.min_node is None:
            return None

        z = self.min_node
        # Добавляем детей z в список корней
        if z.child is not None:
            child = z.child
            while True:
                child.parent = None
                next_child = child.right
                self._add_to_root_list(child)
                self.root_count += 1
                child = next_child
                if child == z.child:
                    break

        # Удаляем z из списка корней
        self._remove_from_root_list(z)
        self.root_count -= 1

        if self.root_count == 0:
            self.min_node = None
        else:
            self.min_node = z.right  # временно
            self._consolidate()

        return z.key
        
if __name__ == "__main__":
    heap = FibonacciHeap()
    heap.insert(10)
    heap.insert(5)
    heap.insert(20)
    print("Минимум:", heap.find_min())  # 5
    print("Извлечён минимум:", heap.extract_min())  # 5
    print("Новый минимум:", heap.find_min())  # 10

4. Хэш‑таблица
class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [[] for _ in range(self.size)]  # списки для цепочек

    def _hash(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash(key)
        bucket = self.table[index]
        for i, (k, v) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)  # обновление
                return
        bucket.append((key, value))  # новое значение

    def get(self, key):
        index = self._hash(key)
        bucket = self.table[index]
        for k, v in bucket:
            if k == key:
                return v
        raise KeyError(key)

    def remove(self, key):
        index = self._hash(key)
        bucket = self.table[index]
        for i, (k, v) in enumerate(bucket):
            if k == key:
                del bucket[i]
                return
        raise KeyError(key)

    def contains(self, key):
        try:
            self.get(key)
            return True
        except KeyError:
            return False

    def __str__(self):
        items = []
        for bucket in self.table:
            for k, v in bucket:
                items.append(f"{k}: {v}")
        return "{" + ", ".join(items) + "}"



if __name__ == "__main__":
    ht = HashTable(5)
    ht.insert("name", "Alice")
    ht.insert("age", 30)
    ht.insert("city", "Moscow")

    print(ht)  # {name: Alice, age: 30, city: Moscow}
    print(ht.get("name"))  # Alice
    print(ht.contains("age"))  # True

    ht.remove("city")
    print(ht)  # {name: Alice, age: 30}
