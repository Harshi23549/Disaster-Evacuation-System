// ============================================================
//  dijkstra.cpp  —  Team Lead (YOU)
//  Disaster Evacuation System
//  Finds shortest + safest path from user location → safe zone
//  Even when roads are blocked (works with blocked_roads.cpp)
// ============================================================

#include <iostream>
#include <vector>
#include<algorithm>
#include <queue>
#include <climits>
#include "graph_input.h"   // Sakshi's header — provides Graph type

using namespace std;

// ── Type aliases (keep code readable) ──────────────────────
// pair<int,int> → {distance, node}
typedef pair<int,int> pii;

// ── dijkstra() ──────────────────────────────────────────────
// Parameters:
//   graph   : adjacency list built by Sakshi's graph_input.cpp
//   src     : starting node (user's current location)
//   n       : total number of nodes in the graph
//   dist    : output vector — dist[i] = shortest dist from src to i
//   parent  : output vector — used to reconstruct the full path
//
// Returns: nothing (fills dist[] and parent[] in place)
// ────────────────────────────────────────────────────────────
void dijkstra(
    const vector<vector<pii>>& graph,
    int src,
    int n,
    vector<int>& dist,
    vector<int>& parent
) {
    // Step 1 — Initialise all distances to infinity
    dist.assign(n, INT_MAX);
    parent.assign(n, -1);
    dist[src] = 0;

    // Step 2 — Min-heap priority queue: {distance, node}
    // Smallest distance node is always processed first (greedy!)
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});

    // Step 3 — Relax edges using Dijkstra's greedy approach
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Skip if we already found a shorter path to u
        if (d > dist[u]) continue;

        // Check all neighbours of u
        for (auto [weight, v] : graph[u]) {
            // If going through u gives a shorter path to v → update
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;            // remember how we got here
                pq.push({dist[v], v});
            }
        }
    }
}

// ── getPath() ───────────────────────────────────────────────
// Reconstructs the full path from src → dest using parent[]
// Returns path as a vector of nodes in order src → dest
// Returns empty vector if dest is unreachable
// ────────────────────────────────────────────────────────────
vector<int> getPath(const vector<int>& parent, int src, int dest) {
    vector<int> path;

    // If dest was never reached, return empty
    if (parent[dest] == -1 && dest != src) {
        return path;  // unreachable
    }

    // Walk backwards from dest → src using parent links
    for (int node = dest; node != -1; node = parent[node]) {
        path.push_back(node);
    }

    // Reverse to get src → dest order
    reverse(path.begin(), path.end());
    return path;
}

// ── findSafestPath() ────────────────────────────────────────
// Main function called by output.cpp (Tanisha) and
// blocked_roads.cpp (Disha) after any road update.
//
// Parameters:
//   graph      : adjacency list (from Sakshi or updated by Disha)
//   src        : user's current location node
//   safeNodes  : list of all safe zone nodes in the city
//   n          : total nodes
//
// Returns: {distance, path} to the NEAREST safe zone
// ────────────────────────────────────────────────────────────
pair<int, vector<int>> findSafestPath(
    const vector<vector<pii>>& graph,
    int src,
    const vector<int>& safeNodes,
    int n
) {
    vector<int> dist, parent;
    dijkstra(graph, src, n, dist, parent);

    int bestDist = INT_MAX;
    int bestDest = -1;

    // Among all safe zones, pick the closest one
    for (int safe : safeNodes) {
        if (dist[safe] < bestDist) {
            bestDist = dist[safe];
            bestDest = safe;
        }
    }

    // Build and return the path to best safe zone
    if (bestDest == -1 || bestDist == INT_MAX) {
        cout << "ERROR: No reachable safe zone from node " << src << "!\n";
        return {-1, {}};
    }

    vector<int> path = getPath(parent, src, bestDest);
    return {bestDist, path};
}