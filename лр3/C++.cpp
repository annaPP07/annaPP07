1. Бинарная куча 
#include <queue>
#include <vector>
std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
heap.push(10);
heap.push(5);
int min_val = heap.top();  // 5
heap.pop();

2. Биномиальная куча
#include <vector>
struct BinomialNode {
    int key;
    std::vector<BinomialNode*> children;
    BinomialNode* parent;
    BinomialNode(int k) : key(k), parent(nullptr) {}
};
struct BinomialHeap {
    std::vector<BinomialNode*> trees;
};

3. Куча Фибоначчи
struct FibNode {
    int key;
    int degree;
    FibNode *parent, *child, *next, *prev;
    bool mark;
    FibNode(int k) : key(k), degree(0), mark(false),
                     parent(nullptr), child(nullptr) {
        next = prev = this;
    }
};
struct FibonacciHeap {
    FibNode* minNode;
    int totalNodes;
};

4.Хэш‑таблица
#include <unordered_map>
std::unordered_map<std::string, std::string> hashTable;
hashTable["key1"] = "value1";
std::string value = hashTable["key1"];
hashTable.erase("key1");
