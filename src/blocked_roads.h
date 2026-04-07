// blocked_roads.h  —  Disha's Header
// Include this in main.cpp to use road blocking functions

#pragma once
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

// Removes road between u and v from graph (both directions)
// Returns true if road was found and removed
bool blockRoad(vector<vector<pii>>& graph, int u, int v);

// Asks user which roads are blocked, removes them,
// then recalculates and returns new {distance, path}
pair<int, vector<int>> handleBlockedRoads(
    vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
);

// Returns true if any path still exists from src to a safe zone
bool isPathPossible(
    const vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
);