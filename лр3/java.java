1. Бинарная куча
import java.util.PriorityQueue;

public class HeapJava {
    private PriorityQueue<Integer> heap;
    
    public HeapJava() {
        this.heap = new PriorityQueue<>();
    }
    
    public void push(int item) {
        heap.add(item);
    }
    
    public int pop() {
        return heap.poll();
    }
    
    public Integer peek() {
        return heap.peek();
    }
    
    public int size() {
        return heap.size();
    }
    
    // Пример использования
    public static void main(String[] args) {
        HeapJava h = new HeapJava();
        h.push(5);
        h.push(3);
        h.push(8);
        System.out.println(h.pop());  // 3
        System.out.println(h.peek()); // 5
    }
}


2. Биномиальная куча
import java.util.*;

/**
 * BinomialHeap
 *
 * An implementation of binomial heap over non-negative integers.
 * Based on exercise from previous semester.
 */
public class BinomialHeap
{
    public int size;
    public HeapNode last = null;
    public HeapNode min = null;
    
    /**
     *
     * pre: key > 0
     *
     * Insert (key,info) into the heap and return the newly generated HeapItem.
     * Complexity: O(log(n))
     *
     */
    public HeapItem insert(int key, String info)
    {
        //Initialize
        HeapItem new_item= new HeapItem();
        HeapNode inserting_node = new HeapNode();
        new_item.setKey(key);
        new_item.setInfo(info);
        new_item.setNode(inserting_node);
        inserting_node.setItem(new_item);
        inserting_node.setChild(null);
        inserting_node.setNext(inserting_node);
        inserting_node.setParent(null);
        inserting_node.setRank(0);
        BinomialHeap insertingHeap = new BinomialHeap();
        insertingHeap.min = inserting_node;
        insertingHeap.last = inserting_node;
        insertingHeap.size=1;
        if(size==0){
            this.min = insertingHeap.min;
            this.last = insertingHeap.last;
            this.size = insertingHeap.size;
        }
        else {
            inserting_node.setNext(this.last.next);
            this.last.setNext(inserting_node);
            this.size += 1;
            if (inserting_node.item.key < this.min.item.key) {
                this.min = inserting_node;
            }
            HeapNode currentNode = inserting_node;
            HeapNode nextNode = inserting_node.next;
            while (currentNode.rank == nextNode.rank) {
                boolean flag = nextNode == this.last;
                nextNode = nextNode.next;
                HeapItem tmp = link(currentNode, currentNode.next);
                currentNode = tmp.node;
                currentNode.rank += 1;
                if (flag) {
                    currentNode.setNext(currentNode);
                    this.last = currentNode;
                    break;
                } else {
                    this.last.setNext(currentNode);
                    currentNode.setNext(nextNode);
                }
            }
        }
        this.min = findNewMin().node;
        return new_item;
    }
    
    /**
     *
     * Delete the minimal item
     * Complexity: O(log(n))
     *
     */
    public void deleteMin()
    {
        if(this.size==1){
            this.min=null;
            this.last=null;
            this.size=0;
        }
        else {
            HeapNode minNode = this.min;
            HeapNode prevminNode = findPrevious(minNode);
            if (minNode == this.last) {
                this.last = prevminNode;
            }
            prevminNode.setNext(minNode.next);
            this.size = this.size - (int) Math.pow(2, minNode.rank);
            this.min = findNewMin().node;
            BinomialHeap minChildHeap = new BinomialHeap();
            if (minNode.child!=null){
                minChildHeap.last = minNode.child;
                minChildHeap.size = (int) Math.pow(2, minNode.rank) - 1;
                minChildHeap.min = minChildHeap.findNewMin().node;
            }
            meld(minChildHeap);
        }
    }
    
    /**
     *
     * Return the previous Node of the given node
     * Complexity: O(log(n))
     *
     */
    private HeapNode findPrevious(HeapNode node){
        HeapNode currNode = node.next;
        while (currNode.next!= node){
            currNode = currNode.next;
        }
        return currNode;
    }
    
    /**
     *
     * Return the minimal HeapItem
     * Complexity: O(1)
     *
     */
    public HeapItem findMin(){
        if(min==null){
            return null;
        }
        return this.min.item;
    }
    
    /**
     *
     * search and Return the minimal HeapItem
     * Complexity: O(log(n))
     *
     */
    public HeapItem findNewMin()
    {
        HeapItem minItem = this.last.next.item;
        HeapNode currNode = this.last.next;
        while (currNode != this.last){
            if(currNode.item.key<minItem.key){
                minItem = currNode.item;
            }
            currNode = currNode.next;
        }
        if(currNode.item.key<minItem.key){
            minItem = currNode.item;
        }
        return minItem;
    }
    
    /**
     *
     * pre: 0<diff<item.key
     *
     * Decrease the key of item by diff and fix the heap.
     * Complexity: O(log(n))
     *
     */
    public void decreaseKey(HeapItem item, int diff)
    {
        item.key -= diff;
        HeapNode currNode = item.node;
        while (currNode.parent!=null && currNode.item.key<currNode.parent.item.key){
            int tmpKey = currNode.item.key;
            String tmpInfo = currNode.item.info;
            currNode.item.setKey(currNode.parent.item.key);
            currNode.item.setInfo(currNode.parent.item.info);
            currNode.parent.item.setKey(tmpKey);
            currNode.parent.item.setInfo(tmpInfo);
            currNode = currNode.parent;
        }
        this.min = findNewMin().node;
    }
    
    /**
     *
     * Delete the item from the heap.
     * Complexity: O(log(n))
     *
     */
    public void delete(HeapItem item)
    {
        decreaseKey(item,1+item.key);
        deleteMin();
    }
    
    /**
     *
     * Meld the heap with heap2
     * Complexity: O(log(n))
     *
     */
    public void meld(BinomialHeap heap2) {
        if(heap2.size!=0) {
            this.merge(heap2);
            HeapNode prevNode = null;
            HeapNode currentNode = this.last.next;
            HeapNode nextNode = currentNode.next;
            int treenumber = numTrees();
            for (int i = 0; i < treenumber - 1; i++) {
                if (currentNode.rank == currentNode.next.rank) {
                    if (treenumber - i >= 3 && currentNode.next.rank == currentNode.next.next.rank) {
                        prevNode = currentNode;
                        currentNode = currentNode.next;
                        nextNode = currentNode.next;
                        continue;
                    }
                    boolean flag = nextNode == this.last;
                    nextNode = nextNode.next;
                    HeapItem tmp = link(currentNode, currentNode.next);
                    currentNode = tmp.node;
                    currentNode.rank += 1;
                    if (flag && prevNode == null) {
                        currentNode.setNext(currentNode);
                    } else {
                        if (prevNode != null) {
                            prevNode.setNext(currentNode);
                        }
                        else {
                            this.last.setNext(currentNode);
                        }
                        currentNode.setNext(nextNode);
                    }
                } else {
                    prevNode = currentNode;
                    currentNode = currentNode.next;
                    nextNode = currentNode.next;
                }
            }
            this.last = currentNode;
            this.min = this.findNewMin().node;
        }
    }
    
    /**
     *
     * linking two heapnode with same rank to one
     * Complexity: O(1)
     *
     *
     */
    private HeapItem link(HeapNode x, HeapNode y){
        if(x.item.key>y.item.key){
            HeapNode tmp = y;
            y=x;
            x=tmp;
        }
        if(x.child == null){
            x.setNext(null);
            y.setNext(null);
            x.setChild(y);
            y.setNext(y);
            y.setParent(x);
        }
        else {
            HeapItem tmp = x.child.next.item;
            x.setNext(null);
            y.setNext(null);
            x.child.setNext(y);
            x.setChild(y);
            y.setNext(tmp.node);
            y.setParent(x);
        }
        return x.item;
    }
    
    /**
     *
     * merging two BinomialHeap into one without linking node with same rank
     * Complexity: O(log(n))
     *
     *
     */
    private void merge(BinomialHeap heap2){
        HeapNode[] arr1 = HeapToArray(this);
        HeapNode[] arr2 = HeapToArray(heap2);
        int size = arr1.length + arr2.length;
        HeapNode[] mergedarr = new HeapNode[size];
        int index1=0;
        int index2=0;
        for(int i=0;i<size;i++){
            if(index1 == arr1.length){
                arr2[index2].setParent(null);
                mergedarr[i] = arr2[index2];
                index2+=1;
            }
            else if(index2 == arr2.length){
                arr1[index1].setParent(null);
                mergedarr[i] = arr1[index1];
                index1+=1;
            }
            else if (arr1[index1].rank<=arr2[index2].rank){
                arr1[index1].setParent(null);
                mergedarr[i] = arr1[index1];
                index1+=1;
            }
            else{
                arr2[index2].setParent(null);
                mergedarr[i] = arr2[index2];
                index2+=1;
            }
        }
        BinomialHeap heap = ArrayToHeap(mergedarr);
        this.last = heap.last;
        this.min = heap.findNewMin().node;
        this.size = heap.size;
    }
    
    /**
     *
     * convert BinomialHeap to Array
     * Complexity: O(log(n))
     *
     *
     */
    private HeapNode[] HeapToArray(BinomialHeap heap){
        if(heap.empty()){
            return new HeapNode[0];
        }
        int treenumber = heap.numTrees();
        HeapNode[] arr = new HeapNode[treenumber];
        HeapNode currnode = heap.last.next;
        for(int i=0;i<treenumber;i++) {
            arr[i]=currnode;
            currnode = currnode.next;
        }
        return arr;
    }
    
    /**
     *
     * convert Array to BinomialHeap
     * Complexity: O(log(n))
     *
     *
     */
    private BinomialHeap ArrayToHeap(HeapNode[] arr){
        BinomialHeap heap = new BinomialHeap();
        int size = 0;
        for(int i=0;i<arr.length-1;i++){
            arr[i].next=arr[i+1];
            size += (int)Math.pow(2,arr[i].rank);
        }
        arr[arr.length-1].next = arr[0];
        size += (int)Math.pow(2,arr[arr.length-1].rank);
        heap.last = arr[arr.length-1];
        heap.min = heap.findNewMin().node;
        heap.size = size;
        return heap;
    }
    
    /**
     *
     * Return the number of elements in the heap
     * Complexity: O(1)
     *
     */
    public int size()
    {
        return size;
    }
    
    /**
     *
     * The method returns true if and only if the heap
     * is empty.
     * Complexity: O(1)
     *
     *
     */
    public boolean empty()
    {
        return (size==0);
    }
    
    /**
     *
     * Return the number of trees in the heap.
     * Complexity: O(log(n))
     *
     */
    public int numTrees()
    {
        if(this.empty()){
            return 0;
        }
        int numtrees = 1;
        HeapNode current = last.next;
        while (current != last){
            numtrees+=1;
            current = current.next;
        }
        return numtrees;
    }
    
    /**
     * Class implementing a node in a Binomial Heap.
     *
     */
    public class HeapNode{
        public HeapItem item;
        public HeapNode child;
        public HeapNode next;
        public HeapNode parent;
        public int rank;
        
        public void setItem(HeapItem item){
            this.item = item;
        }
        public void setChild(HeapNode child){
            this.child = child;
        }
        public void setNext(HeapNode next){
            this.next = next;
        }
        public void setParent(HeapNode parent){
            this.parent = parent;
        }
        public void setRank(int rank){
            this.rank = rank;
        }
    }
    
    /**
     * Class implementing an item in a Binomial Heap.
     *
     */
    public class HeapItem{
        public HeapNode node;
        public int key;
        public String info;
        
        public void setNode(HeapNode node){
            this.node = node;
        }
        public void setKey(int key){
            this.key=key;
        }
        public void setInfo(String info){
            this.info = info;
        }
    }
}

3. Куча Фибоначчи
public class FibonacciHeap {
    private static class Node {
        int key;
        Object value;  // Опционально
        int degree;
        boolean mark;
        Node parent;
        Node child;
        Node left;
        Node right;

        Node(int key) {
            this.key = key;
            this.value = null;
            this.degree = 0;
            this.mark = false;
            this.parent = null;
            this.child = null;
            this.left = this;
            this.right = this;
        }
    }

    private Node minNode;
    private Node rootList;
    private int size;

    public FibonacciHeap() {
        this.minNode = null;
        this.rootList = null;
        this.size = 0;
    }

    public Node insert(int key, Object value) {
        Node node = new Node(key);
        node.value = value;

        if (minNode == null) {
            minNode = node;
            rootList = node;
        } else {
            addToRootList(node);
            if (node.key < minNode.key) {
                minNode = node;
            }
        }
        size++;
        return node;
    }

    private void addToRootList(Node node) {
        if (rootList == null) {
            rootList = node;
        } else {
            node.right = rootList;
            node.left = rootList.left;
            rootList.left.right = node;
            rootList.left = node;
        }
    }

    // Остальные методы реализуются аналогично
}

4. Хэш‑таблица 
import java.util.LinkedList;
import java.util.List;

public class HashTable<K, V> {
    private int size;
    private List<List<Entry<K, V>>> table;

    public HashTable(int size) {
        this.size = size;
        this.table = new LinkedList<>();
        for (int i = 0; i < size; i++) {
            table.add(new LinkedList<>());
        }
    }

    private int hash(K key) {
        return Math.abs(key.hashCode()) % size;
    }

    public void insert(K key, V value) {
        int index = hash(key);
        List<Entry<K, V>> bucket = table.get(index);
        for (Entry<K, V> entry : bucket) {
            if (entry.key.equals(key)) {
                entry.value = value;  // обновление
                return;
            }
        }
        bucket.add(new Entry<>(key, value));  // новое значение
    }

    public V get(K key) {
        int index = hash(key);
        List<Entry<K, V>> bucket = table.get(index);
        for (Entry<K, V> entry : bucket) {
            if (entry.key.equals(key)) {
                return entry.value;
            }
        }
        throw new IllegalArgumentException("Key not found: " + key);
    }

    public void remove(K key) {
        int index = hash(key);
        List<Entry<K, V>> bucket = table.get(index);
        for (int i = 0; i < bucket.size(); i++) {
            Entry<K, V> entry = bucket.get(i);
            if (entry.key.equals(key)) {
                bucket.remove(i);
                return;
            }
        }
        throw new IllegalArgumentException("Key not found: " + key);
    }

    public boolean contains(K key) {
        try {
            get(key);
            return true;
        } catch (IllegalArgumentException e) {
            return false;
        }
    }

    // Вспомогательный класс для пары «ключ‑значение»
    private static class Entry<K, V> {
        K key;
        V value;

        Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("{");
        for (List<Entry<K, V>> bucket : table) {
            for (Entry<K, V> entry : bucket) {
                sb.append(entry.key).append(": ").append(entry.value).append(", ");
            }
        }
        if (sb.length() > 1) sb.setLength(sb.length() - 2);  // убираем последнюю запятую
        sb.append("}");
        return sb.toString();
    }

    // Пример использования
    public static void main(String[] args) {
        HashTable<String, Integer> ht = new HashTable<>(5);
        ht.insert("x", 10);
        ht.insert("y", 20);
        ht.insert("z", 30);

        System.out.println(ht);  // {x: 10, y: 20, z: 30}
        System.out.println(ht.get("y"));  // 20
        System.out.println(ht.contains("x"));  // true

        ht.remove("z");
        System.out.println(ht);  // {x: 10, y: 20}
    }
}

