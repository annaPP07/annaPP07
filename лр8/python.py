import random

def generate_random_graph(n, p=0.3):
    """Генерирует случайный граф из n вершин с вероятностью ребра p."""
    graph = {i: [] for i in range(n)}
    for i in range(n):
        for j in range(i + 1, n):
            if random.random() < p:
                graph[i].append(j)
                graph[j].append(i)
    return graph

def count_conflicts(graph, coloring):
    """Считает число конфликтующих рёбер."""
    conflicts = 0
    for u in graph:
        for v in graph[u]:
            if coloring[u] == coloring[v]:
                conflicts += 1
    return conflicts

def get_valid_colors(graph, coloring, vertex, max_color):
    """Возвращает список цветов, не конфликтующих с соседями."""
    used = {coloring[neighbor] for neighbor in graph[vertex]}
    return [c for c in range(max_color) if c not in used]

def tabu_search_graph_coloring(graph, max_iterations=500, tabu_size=10):
    n = len(graph)
    # Начальная раскраска: случайная
    coloring = [random.randint(0, n - 1) for _ in range(n)]
    best_coloring = coloring[:]
    best_conflicts = count_conflicts(graph, coloring)
    
    tabu_list = []  # Список пар (вершина, старый_цвет)
    
    for iteration in range(max_iterations):
        if best_conflicts == 0:
            break  # Оптимальное решение найдено
        
        # Ищем лучший ход
        best_move = None
        best_delta = float('inf')
        
        for vertex in range(n):
            current_color = coloring[vertex]
            valid_colors = get_valid_colors(graph, coloring, vertex, n)
            
            for new_color in valid_colors:
                if new_color == current_color:
                    continue
                
                # Проверяем, не в табу ли этот ход
                if (vertex, current_color) in tabu_list:
                    continue
                
                # Считаем изменение числа конфликтов
                delta = 0
                for neighbor in graph[vertex]:
                    if coloring[neighbor] == current_color:
                        delta -= 1  # Убираем конфликт
                    if coloring[neighbor] == new_color:
                        delta += 1  # Добавляем конфликт
                
                
                if delta < best_delta:
                    best_delta = delta
                    best_move = (vertex, new_color, current_color)
        
        if best_move is None:
            # Нет допустимых ходов — прерываем
            break
        
        # Применяем ход
        vertex, new_color, old_color = best_move
        coloring[vertex] = new_color
        
        # Обновляем лучшее решение
        current_conflicts = count_conflicts(graph, coloring)
        if current_conflicts < best_conflicts:
            best_conflicts = current_conflicts
            best_coloring = coloring[:]
        
        # Добавляем в табу‑список
        tabu_list.append((vertex, old_color))
        if len(tabu_list) > tabu_size:
            tabu_list.pop(0)  # Удаляем старейший элемент
    
    return best_coloring, best_conflicts

def print_result(coloring):
    """Выводит результат: число цветов и распределение."""
    colors_used = max(coloring) + 1
    print(f"Количество цветов: {colors_used}")
    print("Распределение:")
    for vertex, color in enumerate(coloring):
        print(f"Вершина {vertex}: цвет {color}")

# Пример использования
if __name__ == "__main__":
    # Генерируем граф из 12 вершин
    graph = generate_random_graph(12, p=0.4)
    
    # Запускаем табу‑поиск
    final_coloring, final_conflicts = tabu_search_graph_coloring(
        graph, max_iterations=500, tabu_size=10
    )
    
    # Выводим результат
    print_result(final_coloring)
    print(f"Число конфликтов: {final_conflicts}")


Количество цветов: 12
Распределение:
Вершина 0: цвет 1
Вершина 1: цвет 3
Вершина 2: цвет 5
Вершина 3: цвет 0
Вершина 4: цвет 4
Вершина 5: цвет 2
Вершина 6: цвет 11
Вершина 7: цвет 8
Вершина 8: цвет 2
Вершина 9: цвет 0
Вершина 10: цвет 1
Вершина 11: цвет 7
Число конфликтов: 0
