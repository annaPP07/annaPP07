#Мультисписок (вложенный список)
#Создание вложенных списков:
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

#Очередь/дек (двунаправленная очередь)
#Пример создания очереди и добавления элементов:
from collections import deque
queue = deque()
queue.append(1)  
queue.append(2)
queue.append(3)
print(queue.popleft()) 
print(queue[0])        
#Вывод:1, 2

#Пример реализации дека:
from collections import deque
tasks = deque()
tasks.append("plan_task1")
tasks.append("plan_task2")
tasks.appendleft("urgent_task1")
tasks.appendleft("urgent_task2")
while tasks:
    current_task = tasks.popleft()  
    print(f"Выполняется: {current_task}")
  
#Приоритетная очередь
#Пример кода:
from queue import PriorityQueue
pq = PriorityQueue()
pq.put((3, "высокая"))
pq.put((1, "низкая"))
pq.put((2, "средняя"))
while not pq.empty():
    priority, task = pq.get()
    print(f"{task} (приоритет: {priority})")
