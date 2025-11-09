1. Бинарная куча
import java.util.PriorityQueue;
PriorityQueue<Integer> heap = new PriorityQueue<>();
heap.add(10);
heap.add(5);
int min_val = heap.poll();  // 5

2. Биномиальная куча
class BinomialNode {
    int key;
    List<BinomialNode> children;
    BinomialNode parent;
    public BinomialNode(int key) {
        this.key = key;
        this.children = new ArrayList<>();
        this.parent = null;
    }
}
class BinomialHeap {
    List<BinomialNode> trees = new ArrayList<>();
}

3. Куча Фибоначчи
class FibNode {
    int key;
    int degree;
    FibNode parent, child, next, prev;
    boolean mark;
    public FibNode(int key) {
        this.key = key;
        this.degree = 0;
        this.mark = false;
        this.parent = this.child = null;
        this.next = this.prev = this;
    }
}
class FibonacciHeap {
    FibNode minNode;
    int totalNodes;
}

4. Хэш‑таблица 
import java.util.HashMap;
HashMap<String, String> hashTable = new HashMap<>();
hashTable.put("key1", "value1");
String value = hashTable.get("key1");
hashTable.remove("key1");
