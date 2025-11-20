import java.util.*;

public class MaxIndependentSet {

    public static Set<Integer> maxIndependentSet(int[][] adjMatrix) {
        int n = adjMatrix.length;
        boolean[] deleted = new boolean[n];
        Set<Integer> result = new HashSet<>();

        while (true) {
            int v = -1;
            int minDegree = n + 1;

            // Найти вершину с минимальной степенью среди неудалённых
            for (int i = 0; i < n; i++) {
                if (deleted[i]) continue;

                int degree = 0;
                for (int j = 0; j < n; j++) {
                    if (adjMatrix[i][j] == 1) degree++;
                }

                if (degree < minDegree) {
                    minDegree = degree;
                    v = i;
                }
            }

            // Если не нашли ни одной вершины — выходим
            if (v == -1) break;

            // Добавляем вершину в независимое множество
            result.add(v);
            deleted[v] = true;

            // Удаляем всех соседей v
            for (int u = 0; u < n; u++) {
                if (adjMatrix[v][u] == 1) {
                    deleted[u] = true;
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите количество вершин в графе: ");
        int n = scanner.nextInt();

        int[][] adjMatrix = new int[n][n];

        System.out.println("Введите матрицу смежности (0 — нет ребра, 1 — есть ребро):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = scanner.nextInt();
            }
        }

        Set<Integer> mis = maxIndependentSet(adjMatrix);

        System.out.println("Максимальное независимое множество вершин: " + mis);
        scanner.close();
    }
}


Введите количество вершин в графе: 4
Введите матрицу смежности (0 — нет ребра, 1 — есть ребро):
Ввод
0 1 1 0
1 0 0 1
1 0 0 1
0 1 1 0
Вывод
Максимальное независимое множество вершин: [0, 3]
