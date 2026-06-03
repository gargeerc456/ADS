// DFS & BFS

#include <iostream>
#include <stack>
using namespace std;

#define V 5

int main() {

    int graph[V][V] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };

    bool visited[V] = {false};
    stack<int> st;

    int start = 0;

    st.push(start);

    cout << "DFS Traversal: ";

    while (!st.empty()) {

        int node = st.top();
        st.pop();

        if (!visited[node]) {
            cout << node << " ";
            visited[node] = true;

            for (int i = V - 1; i >= 0; i--) {
                if (graph[node][i] == 1 && !visited[i]) {
                    st.push(i);
                }
            }
        }
    }

    cout << "\nBFS Traversal: ";

    bool visited2[V] = {false};
    int  queue[V];
    int  front = 0, rear = 0;

    queue[rear++]   = start;
    visited2[start] = true;

    while (front < rear) {

        int node = queue[front++];
        cout << node << " ";

        for (int i = 0; i < V; i++) {
            if (graph[node][i] == 1 && !visited2[i]) {
                queue[rear++]  = i;
                visited2[i]    = true;
            }
        }
    }

    cout << endl;
    return 0;
}