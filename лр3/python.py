1. Бинарная куча
import heapq
heap = []
heapq.heappush(heap, 10)
heapq.heappush(heap, 5)
min_val = heapq.heappop(heap)  # 5

2. Биномиальная куча
class BinomialNode:
    def __init__(self, key):
        self.key = key
        self.children = []
        self.parent = None

class BinomialHeap:
    def __init__(self):
        self.trees = []

3. Куча Фибоначчи 
class FibNode:
    def __init__(self, key):
        self.key = key
        self.degree = 0
        self.parent = self.child = None
        self.mark = False
        self.next = self.prev = self
class FibonacciHeap:
    def __init__(self):
        self.min_node = None
        self.total_nodes = 0

4. Хэш‑таблица
# dict — встроенная хэш‑таблица
hash_table = {}
hash_table["key1"] = "value1"
value = hash_table["key1"]
del hash_table["key1"]
