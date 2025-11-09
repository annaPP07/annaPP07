#Мультисписок (вложенный список)
struct Node {
    int data;
    Node* prev;   // предыдущий в строке
    Node* next;   // следующий в строке
    Node* up;     // предыдущий в столбце
    Node* down;   // следующий в столбце

#Очередь/дек (двунаправленная очередь)
#Пример кода:
#include <iostream>
#include <queue>
int main() {
    std::queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    std::cout << "Front: " << q.front() << std::endl;  
    std::cout << "Back: " << q.back() << std::endl;    
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
// Вывод: 10 20 30
  
#Приоритетная очередь
#Пример кода:
#include <iostream>
#include <queue>
int main() {
    std::priority_queue<int> pq;
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    while (!pq.empty()) {
        std::cout << pq.top() << " ";  
        pq.pop();
    }   
    return 0;
}
// Вывод: 50 30 20 10
