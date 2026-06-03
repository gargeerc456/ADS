// Dijkstra's Algorithm

#include <iostream>
using namespace std;

#define V 5
#define INF 99999

int minDistance(int dist[], bool visited[]) {
    int min       = INF;
    int min_index = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] <= min) {
            min       = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void output(int dist[]) {
    cout << "Vertex \t Distance from the Source\n";
    for (int i = 0; i < V; i++) {
        char ver = 65 + i;
        cout << ver << " \t\t " << dist[i] << endl;
    }
}

void dijkstraAlgorithm(int graph[V][V], int src) {

    int  dist[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        dist[i]    = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {

        int d = minDistance(dist, visited);

        if (d == -1) break;

        visited[d] = true;

        for (int j = 0; j < V; j++) {
            if (!visited[j] && graph[d][j] != 0
                && dist[d] != INF
                && dist[d] + graph[d][j] < dist[j])
            {
                dist[j] = dist[d] + graph[d][j];
            }
        }
    }

    output(dist);
}

int main() {

    int graph[V][V] = {
        {0, 1, 2, 0, 0},
        {1, 0, 1, 0, 3},
        {2, 1, 0, 2, 2},
        {0, 0, 2, 0, 1},
        {0, 3, 2, 1, 0}
    };

    dijkstraAlgorithm(graph, 0);

    return 0;
}