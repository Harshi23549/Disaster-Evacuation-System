// ============================================================
//  graph_input.cpp  —  Sakshi (Input Module)
//  Reads city map → builds adjacency list for Dijkstra
//  FOUNDATION: if this breaks, whole system breaks
// ============================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include "graph_input.h"

using namespace std;

// ── buildGraphFromInput() ────────────────────────────────────
// Takes manual input from user on terminal
// Format:
//   Line 1: n (nodes)  e (edges)
//   Next e lines: u v w  (road from u to v with weight w)
// ────────────────────────────────────────────────────────────
void buildGraphFromInput(vector<vector<pii>>& graph, int& n, int& edges) {
    cout << "Enter number of locations (nodes) and roads (edges): ";
    cin >> n >> edges;

    // Validate input
    if (n <= 0 || edges < 0) {
        cout << "ERROR: Invalid graph size.\n";
        return;
    }

    graph.assign(n, vector<pii>());

    cout << "Enter each road as: location1 location2 distance\n";
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        // Validate node range
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "ERROR: Node out of range. Skipping road " << i+1 << "\n";
            continue;
        }

        // Validate weight
        if (w < 0) {
            cout << "ERROR: Negative distance. Skipping road " << i+1 << "\n";
            continue;
        }

        // IMPORTANT: always {weight, node} order — matches dijkstra.cpp
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});  // undirected road
    }

    cout << "Graph built successfully with " << n << " locations.\n";
}

// ── buildGraphFromFile() ─────────────────────────────────────
// Reads graph from data/input.txt
// Same format as manual input
// ────────────────────────────────────────────────────────────
void buildGraphFromFile(vector<vector<pii>>& graph, int& n, int& edges, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "ERROR: Cannot open file " << filename << "\n";
        cout << "Switching to manual input...\n";
        buildGraphFromInput(graph, n, edges);
        return;
    }

    file >> n >> edges;

    if (n <= 0 || edges < 0) {
        cout << "ERROR: Invalid graph in file.\n";
        return;
    }

    graph.assign(n, vector<pii>());

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        file >> u >> v >> w;

        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "ERROR: Node out of range in file at road " << i+1 << "\n";
            continue;
        }

        if (w < 0) {
            cout << "ERROR: Negative weight in file at road " << i+1 << "\n";
            continue;
        }

        // IMPORTANT: always {weight, node} order
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }

    file.close();
    cout << "Graph loaded from file: " << filename << "\n";
    cout << n << " locations, " << edges << " roads loaded.\n";
}

// ── printGraph() ─────────────────────────────────────────────
// Debug function — prints adjacency list
// ────────────────────────────────────────────────────────────
void printGraph(const vector<vector<pii>>& graph, int n) {
    cout << "\n--- Adjacency List ---\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " → ";
        for (auto [w, v] : graph[i]) {
            cout << "(Node " << v << ", dist=" << w << ") ";
        }
        cout << "\n";
    }
    cout << "----------------------\n";
}

// ── getSafeZones() ───────────────────────────────────────────
// Asks user which nodes are safe evacuation zones
// ────────────────────────────────────────────────────────────
vector<int> getSafeZones(int n) {
    vector<int> safeNodes;
    int k;
    cout << "\nHow many safe zones are there? ";
    cin >> k;

    cout << "Enter safe zone node numbers (0 to " << n-1 << "):\n";
    for (int i = 0; i < k; i++) {
        int s;
        cin >> s;
        if (s >= 0 && s < n) {
            safeNodes.push_back(s);
        } else {
            cout << "ERROR: Node " << s << " out of range. Skipping.\n";
        }
    }

    return safeNodes;
}