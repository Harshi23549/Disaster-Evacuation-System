// ============================================================
//  blocked_roads.cpp  —  Disha (Dynamic Update Module)
//  Handles road blockages → removes edges → recalculates path
//  HARDEST MODULE: makes system real-world ready
// ============================================================

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "graph_input.h"   // for graph type
#include "dijkstra.h"      // to call findSafestPath() after update

using namespace std;

typedef pair<int,int> pii;

// ── blockRoad() ──────────────────────────────────────────────
// Removes the road (edge) between node u and node v
// from the adjacency list — in BOTH directions (undirected)
//
// Returns true if road was found and removed
// Returns false if road didn't exist
// ────────────────────────────────────────────────────────────
bool blockRoad(vector<vector<pii>>& graph, int u, int v) {
    bool found = false;

    // Remove v from u's adjacency list
    auto& listU = graph[u];
    auto it = remove_if(listU.begin(), listU.end(), [&](pii edge) {
        return edge.second == v;
    });
    if (it != listU.end()) {
        listU.erase(it, listU.end());
        found = true;
    }

    // Remove u from v's adjacency list (undirected road)
    auto& listV = graph[v];
    auto it2 = remove_if(listV.begin(), listV.end(), [&](pii edge) {
        return edge.second == u;
    });
    if (it2 != listV.end()) {
        listV.erase(it2, listV.end());
        found = true;
    }

    return found;
}

// ── handleBlockedRoads() ─────────────────────────────────────
// Main function — asks user which roads are blocked,
// removes them, then recalculates the evacuation path
//
// Parameters:
//   graph     : the current adjacency list (will be modified)
//   src       : user's current location
//   safeNodes : list of safe zone nodes
//   n         : total number of nodes
// ────────────────────────────────────────────────────────────
pair<int, vector<int>> handleBlockedRoads(
    vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
) {
    char choice;
    cout << "\nAre any roads blocked? (y/n): ";
    cin >> choice;

    while (choice == 'y' || choice == 'Y') {
        int u, v;
        cout << "Enter blocked road (node1 node2): ";
        cin >> u >> v;

        // Validate nodes
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "ERROR: Invalid nodes. Try again.\n";
        } else {
            bool removed = blockRoad(graph, u, v);
            if (removed) {
                cout << "Road between " << u << " and " << v << " is now BLOCKED.\n";
            } else {
                cout << "WARNING: No road found between " << u << " and " << v << ".\n";
            }
        }

        cout << "Any more blocked roads? (y/n): ";
        cin >> choice;
    }

    // Recalculate path with updated graph
    cout << "\nRecalculating safest path with updated road map...\n";
    return findSafestPath(graph, src, safeNodes, n);
}

// ── isGraphConnected() ───────────────────────────────────────
// Bonus: checks if there is still ANY path from src to any safe zone
// Useful to warn user early if all routes are cut off
// ────────────────────────────────────────────────────────────
bool isPathPossible(
    const vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
) {
    auto [dist, path] = findSafestPath(graph, src, safeNodes, n);
    return dist != -1;
}