// ============================================================
//  main.cpp  —  Integration File (Team Lead manages this)
//  Connects all 4 modules together
//  This is what you compile and run
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include "graph_input.h"    // Sakshi
#include "dijkstra.h"       // You
#include "blocked_roads.h"  // Disha  (she should make this .h)
#include "output.h"         // Tanisha (she should make this .h)

using namespace std;

int main() {
    // ── Step 1: Welcome screen (Tanisha) ──
    displayWelcome();

    // ── Step 2: Build graph (Sakshi) ──
    vector<vector<pair<int,int>>> graph;
    int n = 0, edges = 0;

    char fileChoice;
    cout << "Load from file? (y/n): ";
    cin >> fileChoice;

    if (fileChoice == 'y' || fileChoice == 'Y') {
        buildGraphFromFile(graph, n, edges, "input.txt");
    } else {
        buildGraphFromInput(graph, n, edges);
    }

    // Debug: print graph
    printGraph(graph, n);

    // Get safe zones (Sakshi)
    vector<int> safeNodes = getSafeZones(n);

    // Get user location
    int src;
    cout << "\nEnter your current location (node number 0 to " << n-1 << "): ";
    cin >> src;

    if (src < 0 || src >= n) {
        cout << "ERROR: Invalid location.\n";
        return 1;
    }

    // ── Step 3: Find initial shortest path (You — dijkstra) ──
    auto [distance, path] = findSafestPath(graph, src, safeNodes, n);

    // Optional: give names to nodes for better output
    // In real project, Sakshi can fill this from input
    vector<string> nodeNames(n);
    for (int i = 0; i < n; i++) {
        nodeNames[i] = "Location-" + to_string(i);
    }
    // Mark last node as safe zone
    if (!safeNodes.empty()) {
        nodeNames[safeNodes[0]] = "SAFE ZONE";
    }

    // Show initial path (Tanisha)
    displayPath(path, distance, nodeNames);

    // ── Step 4: Handle blocked roads (Disha) ──
    auto [newDist, newPath] = handleBlockedRoads(graph, src, safeNodes, n);

    // Show updated path if roads were blocked
    if (newDist != distance || newPath != path) {
        cout << "\n--- Updated Route After Road Blockage ---\n";
        if (newPath.empty()) {
            displayNoPath();
        } else {
            displayPath(newPath, newDist, nodeNames);
        }
    }

    // ── Step 5: Final summary (Tanisha) ──
    displaySummary(n, edges, 0, (int)newPath.size(), newDist);

    return 0;
}