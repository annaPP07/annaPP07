Сортировка выбором

#include <iostream> // Подключаем библиотеку ввода-вывода

// Функция для вывода массива на экран
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {   // Проходим по каждому элементу массива
        std::cout << arr[i] << " ";     // Выводим значение элемента
    }
    std::cout << "\n";                 // Переход на новую строку после печати всех элементов
}

// Основная функция сортировки выбором
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {          // Внешний цикл проходит по массиву, уменьшая область несортированных элементов
        int minIndex = i;                      // Запоминаем индекс текущего минимального элемента
        
        // Внутренний цикл ищет минимальный элемент среди оставшихся несортированных элементов
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {      // Если найден меньший элемент, обновляем индекс минимального элемента
                minIndex = j;
            }
        }
        
        // Меняем местами текущий элемент с минимальным элементом
        if (minIndex != i) {                   // Проверяем, действительно ли нашли новый минимум
            std::swap(arr[i], arr[minIndex]);  // Обмен значений
        }
    }
}

// Главная функция программы
int main() {
    int array[] = {64, 25, 12, 22, 11};       // Пример исходного массива
    int size = sizeof(array)/sizeof(array[0]); // Вычисление размера массива (количество элементов)
    
    std::cout << "Исходный массив:\n";
    printArray(array, size);                  // Печать исходного массива
    
    selectionSort(array, size);               // Выполняем сортировку
    
    std::cout << "Отсортированный массив:\n";
    printArray(array, size);                  // Печать отсортированного массива
    
    return 0;                                 // Завершаем программу успешно
}
Исходный массив:
64 25 12 22 11 
Отсортированный массив:
11 12 22 25 64 

Сортировка слиянием

#include <iostream>
using namespace std;

// Вспомогательная функция для объединения двух отсортированных подмассивов
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;        // Размер левого подмассива
    int n2 = right - mid;           // Размер правого подмассива

    // Создание временных массивов для хранения разделённых частей
    int L[n1], R[n2];

    // Копирование данных в временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];        // Левая половина
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];    // Правая половина

    // Индексы для левой и правой половин
    int i = 0, j = 0;
    int k = left;                   // Текущий индекс результирующего массива

    // Объединение двух подмассивов обратно в исходный массив
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {          // Если левый элемент меньше или равен правому
            arr[k++] = L[i++];       // Добавляем левый элемент и двигаем указатель вперед
        } else {
            arr[k++] = R[j++];       // Иначе добавляем правый элемент
        }
    }

    // Остаточные элементы из левой половины
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Остаточные элементы из правой половины
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Рекурсивная функция сортировки слиянием
void mergeSort(int arr[], int left, int right) {
    if (left < right) {                           // Если есть что сортировать
        int mid = left + (right - left) / 2;      // Нахождение середины подмассива
        mergeSort(arr, left, mid);                // Рекурсивно сортируем левую половину
        mergeSort(arr, mid + 1, right);           // Рекурсивно сортируем правую половину
        merge(arr, left, mid, right);             // Объединяем обе половины
    }
}

// Основная функция для запуска сортировки
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};     // Исходный массив
    int n = sizeof(arr) / sizeof(arr[0]);         // Получаем размер массива

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    mergeSort(arr, 0, n - 1);                    // Вызов рекурсивной сортировки

    cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
Исходный массив: 38 27 43 3 9 82 10 
Отсортированный массив: 3 9 10 27 38 43 82 

    
Пирамидальная сортировка

#include <iostream>
using namespace std;

// Функция для поддержания свойства кучи (heapify)
void heapify(int arr[], int n, int root) {
    int largest = root;         // Предполагаемый наибольший элемент
    int left_child = 2*root + 1;// Левый потомок узла
    int right_child = 2*root + 2;// Правый потомок узла

    // Если левый дочерний узел больше корня
    if (left_child < n && arr[left_child] > arr[largest])
        largest = left_child;

    // Если правый дочерний узел больше наибольшего на данный момент
    if (right_child < n && arr[right_child] > arr[largest])
        largest = right_child;

    // Если наибольший элемент изменился
    if (largest != root) {
        swap(arr[root], arr[largest]); // Меняем корень с наибольшим элементом
        heapify(arr, n, largest);      // Рекурсивно восстанавливаем кучу снизу вверх
    }
}

// Функция для построения max-кучи из массива
void build_heap(int arr[], int n) {
    // Начиная с последнего родительского узла (n/2 - 1), строим max-кучу
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
}

// Основная функция пирамидальной сортировки
void heap_sort(int arr[], int n) {
    // Строим max-кучу из массива
    build_heap(arr, n);

    // Извлекаем элементы из кучи один за другим
    for (int i = n - 1; i > 0; --i) {
        // Меняем корневой элемент с последним элементом
        swap(arr[0], arr[i]);
        // Восстанавливаем структуру кучи
        heapify(arr, i, 0);
    }
}

// Вывод массива на экран
void print_array(const int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// Основная точка входа
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    print_array(arr, n);

    heap_sort(arr, n); // Вызов функции сортировки

    cout << "Отсортированный массив: ";
    print_array(arr, n);

    return 0;
}
Исходный массив: 12 11 13 5 6 7 
Отсортированный массив: 5 6 7 11 12 13
    
БИНАРНЫЙ (ДВОИЧНЫЙ, ДИХОТОМИЧЕСКИЙ) ПОИСК

#include <iostream>
using namespace std;

// Функция бинарного поиска
int binarySearch(int arr[], int low, int high, int target) {
    /*
    arr[] - отсортированный массив
    low - нижняя граница поиска
    high - верхняя граница поиска
    target - искомое значение
    */

    while (low <= high) {                              // Пока нижняя граница не превысила верхнюю границу
        int mid = low + (high - low) / 2;              // Вычисляем середину отрезка

        if (arr[mid] == target) {                      // Если центральный элемент равен искомому
            return mid;                                // Возвращаем индекс центрального элемента
        }

        if (arr[mid] < target) {                       // Если центральный элемент меньше искомого
            low = mid + 1;                             // Искать в правой половине
        } else {                                       // Если центральный элемент больше искомого
            high = mid - 1;                            // Искать в левой половине
        }
    }

    return -1;                                        // Если элемент не найден, вернуть -1
}

// Основная функция
int main() {
    int arr[] = {2, 3, 4, 10, 40};                   // Отсортированный массив
    int n = sizeof(arr) / sizeof(arr[0]);              // Определим размер массива
    int target = 10;                                  // Искомое значение
    int result = binarySearch(arr, 0, n - 1, target); // Вызываем функцию бинарного поиска

    if (result != -1) {
        cout << "Элемент найден на позиции " << result << endl;
    } else {
        cout << "Элемент не найден." << endl;
    }

    return 0;
}
Элемент найден на позиции 3

Интерполирующий поиск

#include <iostream>
using namespace std;

// Функция для интерполирующего поиска
int interpolationSearch(int arr[], int low, int high, int target) {
    // Проверка условий окончания поиска
    if ((low <= high) && (target >= arr[low]) && (target <= arr[high])) {
        // Вычисляем пробную позицию (формула интерполяционного поиска)
        int pos = low + (((double)(high - low) /
                         (arr[high] - arr[low])) *
                        (target - arr[low]));

        // Три случая возникают при поиске:
        if (arr[pos] == target) {
            return pos;  // Совпадение найдено, возвращаем индекс
        }

        if (arr[pos] < target) {
            return interpolationSearch(arr, pos + 1, high, target);  // Продолжаем поиск в правой части
        }

        if (arr[pos] > target) {
            return interpolationSearch(arr, low, pos - 1, target);  // Продолжаем поиск в левой части
        }
    }

    return -1;  // Элемент не найден
}

// Основная функция
int main() {
    int arr[] = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int n = sizeof(arr) / sizeof(arr[0]);  // Вычисляем размер массива
    int target = 18;  // Искомое значение

    int index = interpolationSearch(arr, 0, n - 1, target);  // Вызов функции поиска

    if (index != -1) {
        cout << "Элемент найден на позиции " << index << endl;
    } else {
        cout << "Элемент не найден." << endl;
    }

    return 0;
}
Элемент найден на позиции 4
