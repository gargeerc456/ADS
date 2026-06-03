// =====================================================
// DIJKSTRA'S ALGORITHM 
// =====================================================
//
// Imagine you have a map of cities connected by roads 🗺️.
// Each road has a travel TIME (weight) on it.
// You're sitting in city A and want to know:
//   "What is the FASTEST way to reach every other city?"
//
// Dijkstra's answer:
//   1. Start at your city. Your distance to yourself = 0.
//      Your distance to everyone else = ♾️ (you don't know yet).
//   2. Pick the unvisited city with the SMALLEST known distance.
//   3. Look at all its neighbours. If going THROUGH this city
//      gives a shorter trip to a neighbour, UPDATE that neighbour's distance.
//   4. Mark this city as "done" (visited).
//   5. Repeat until all cities are done!
//
// It's like water flowing downhill 💧 — always takes the easiest path first.
//
// =====================================================

#include <iostream>
using namespace std;

// How many cities (vertices) in our map
#define V 5

// INF means "we haven't found a path here yet — distance is unknown / huge"
// Must be larger than any possible real distance in the graph!
#define INF 99999

// -------------------------------------------------------
// "Which unvisited city is CLOSEST to the source right now?"
// We scan all cities and return the one with the smallest
// distance that we haven't finalised yet.
// -------------------------------------------------------
int minDistance(int dist[], bool visited[]) {
    int min       = INF;    // Start with a huge number — any real distance beats this
    int min_index = -1;     // We haven't found a candidate yet

    for (int i = 0; i < V; i++) {
        // Only consider cities we haven't locked in yet
        // AND whose current known distance is smaller than our best so far
        if (!visited[i] && dist[i] <= min) {
            min       = dist[i];   // New closest distance found!
            min_index = i;         // Remember which city this is
        }
    }

    return min_index;   // Hand back the index of the closest unvisited city
}

// -------------------------------------------------------
// "Print the final answer: how far is each city from the source?"
// We label cities A, B, C, D, E by adding 65 to the index
// (65 = ASCII code for 'A'), so 0→A, 1→B, 2→C, etc.
// -------------------------------------------------------
void output(int dist[]) {
    cout << "Vertex \t Distance from the Source\n";
    for (int i = 0; i < V; i++) {
        char ver = 65 + i;                             // 0→'A', 1→'B', etc.
        cout << ver << " \t\t " << dist[i] << endl;   // Print "A    7" style
    }
}

// -------------------------------------------------------
// THE MAIN DIJKSTRA FUNCTION
// src = the starting city (source)
// -------------------------------------------------------
void dijkstraAlgorithm(int graph[V][V], int src) {

    int  dist[V];        // dist[i] = shortest known distance from src to city i
    bool visited[V];     // visited[i] = true once city i's shortest path is finalised

    // --- STEP 1: Set everything to "unknown" at the start ---
    for (int i = 0; i < V; i++) {
        dist[i]    = INF;    // We don't know the distance to anyone yet — treat as ♾️
        visited[i] = false;  // No city is finalised yet
    }

    dist[src] = 0;   // The distance from the source to ITSELF is always 0! 🏠

    // --- STEP 2: Repeat V-1 times (once per city, excluding source) ---
    for (int i = 0; i < V - 1; i++) {

        // Pick the unvisited city with the SMALLEST known distance right now
        int d = minDistance(dist, visited);

        // If minDistance returned -1, all remaining cities are unreachable — stop early
        if (d == -1) break;

        visited[d] = true;   // Lock in city d — its shortest path is now finalised ✅

        // --- STEP 3: Update distances of city d's neighbours ---
        for (int j = 0; j < V; j++) {

            // Only update if ALL of these are true:
            // 1. City j hasn't been finalised yet
            // 2. There IS a road from d to j (weight > 0)
            // 3. City d is actually reachable (dist[d] != INF)
            // 4. Going THROUGH d to reach j is shorter than the current best path to j
            if (!visited[j]
                && graph[d][j] != 0
                && dist[d] != INF
                && dist[d] + graph[d][j] < dist[j])
            {
                dist[j] = dist[d] + graph[d][j];
                // "Hey city j! I found a shorter route: go through city d!"
            }
        }
    }

    // --- STEP 4: Print the results ---
    output(dist);
}

// -------------------------------------------------------
// MAIN — set up the map and run Dijkstra from city A (index 0)
// -------------------------------------------------------
int main() {

    // -------------------------------------------------------
    // THE MAP: road weights between cities.
    // graph[i][j] = travel cost from city i to city j.
    // 0 means no direct road between them.
    //
    //         A   B   C   D   E
    //   A:  [ 0,  1,  2,  0,  0 ]
    //   B:  [ 1,  0,  1,  0,  3 ]
    //   C:  [ 2,  1,  0,  2,  2 ]
    //   D:  [ 0,  0,  2,  0,  1 ]
    //   E:  [ 0,  3,  2,  1,  0 ]
    // -------------------------------------------------------
    int graph[V][V] = {
        {0, 1, 2, 0, 0},
        {1, 0, 1, 0, 3},
        {2, 1, 0, 2, 2},
        {0, 0, 2, 0, 1},
        {0, 3, 2, 1, 0}
    };

    // Run Dijkstra starting from city 0 (city A)
    dijkstraAlgorithm(graph, 0);

    return 0;
}