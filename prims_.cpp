#include <iostream>
using namespace std;

#define V 5

int main() {

    int G[V][V] = {
        {0, 4, 0, 5, 2},
        {4, 0, 1, 3, 0},
        {0, 1, 0, 8, 0},
        {5, 3, 8, 0, 2},
        {2, 0, 0, 2, 0},
    };

    bool v_array[V] = {false};
    v_array[0]      = true;

    cout << "edges = Wt\n";

    int no_edges = 0;

    while (no_edges < V - 1) {

        int min = 999;
        int r   = 0;
        int c   = 0;

        for (int i = 0; i < V; i++) {
            if (v_array[i]) {
                for (int j = 0; j < V; j++) {
                    if (!v_array[j] && G[i][j] != 0) {
                        if (G[i][j] < min) {
                            min = G[i][j];
                            r   = i;
                            c   = j;
                        }
                    }
                }
            }
        }

        cout << r << " - " << c << " : " << min << endl;
        v_array[c] = true;
        no_edges++;
    }

    cout << "Total no of edges in MST: " << no_edges << endl;

    return 0;
}