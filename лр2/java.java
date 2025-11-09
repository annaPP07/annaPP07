#Мультисписок (вложенный список)
import java.util.*;
public class MultiListExample {
    public static void main(String[] args) {
        List<List<Integer>> multiList = new ArrayList<>();
        List<Integer> row1 = Arrays.asList(1, 2, 3);
        List<Integer> row2 = Arrays.asList(4, 5, 6, 7);
        List<Integer> row3 = Arrays.asList(8, 9);
        multiList.add(row1);
        multiList.add(row2);
        multiList.add(row3);
        System.out.println("Мультисписок:");
        for (int i = 0; i < multiList.size(); i++) {
            System.out.println("Строка " + i + ": " + multiList.get(i));
        }
        System.out.println("Элемент [1][2]: " + multiList.get(1).get(2));
    }
}

#Очередь/дек (двунаправленная очередь)
#Пример с использованием Queue:
Queue<String> taskQueue = new LinkedList<>();
taskQueue.add("Задача 1");
taskQueue.add("Задача 2");
taskQueue.add("Задача 3");
System.out.println("Очередь после добавления элементов: " + taskQueue);

Пример с использованием Deque:
Deque<String> deque = new ArrayDeque<>();
deque.addFirst("Элемент 1"); 
deque.addLast("Элемент 2");  
deque.addFirst("Элемент 0"); 
System.out.println("Дек после добавления: " + deque);

#Приоритетная очередь
#Пример кода:
PriorityQueue<Integer> priorityQueue = new PriorityQueue<>();
priorityQueue.add(5);
priorityQueue.add(2);
priorityQueue.add(8);
priorityQueue.add(1);
priorityQueue.add(9);
System.out.println("Приоритетная очередь: " + priorityQueue);
while (!priorityQueue.isEmpty()) {
    int highestPriority = priorityQueue.poll();
    System.out.println("Извлечён элемент с высшим приоритетом: " + highestPriority);
}
