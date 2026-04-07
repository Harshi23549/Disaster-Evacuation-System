// dijkstra.h  —  Header for dijkstra.cpp
// Include this in blocked_roads.cpp (Disha) and output.cpp (Tanisha)
// so they can call your functions.

#pragma once
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

// Run Dijkstra from src. Fills dist[] and parent[].
void dijkstra(
    const vector<vector<pii>>& graph,
    int src,
    int n,
    vector<int>& dist,
    vector<int>& parent
);

// Reconstruct path from parent[] array.
vector<int> getPath(const vector<int>& parent, int src, int dest);

// Find shortest path to nearest safe zone.
// Returns {distance, path}
pair<int, vector<int>> findSafestPath(
    const vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
);