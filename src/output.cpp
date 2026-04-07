// ============================================================
//  output.cpp  —  Tanisha (Output Module)
//  Displays evacuation path, distance, and safe location
//  Makes the demo readable for examiner
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include "dijkstra.h"

using namespace std;

// ── displayPath() ────────────────────────────────────────────
// Prints the evacuation path in a clean readable format
//
// Parameters:
//   path      : vector of nodes from src → safe zone
//   distance  : total distance of the path
//   nodeNames : optional map of node number → location name
// ────────────────────────────────────────────────────────────
void displayPath(
    const vector<int>& path,
    int distance,
    const vector<string>& nodeNames
) {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║     EVACUATION ROUTE FOUND           ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    if (path.empty()) {
        cout << "❌ ERROR: No safe path found!\n";
        cout << "   All routes to safe zones are blocked.\n";
        cout << "   Please contact emergency services.\n";
        return;
    }

    cout << "\n📍 Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        int node = path[i];

        // Show name if available, else show node number
        if (!nodeNames.empty() && node < (int)nodeNames.size()) {
            cout << nodeNames[node];
        } else {
            cout << "Node " << node;
        }

        if (i + 1 < (int)path.size()) cout << " → ";
    }

    cout << "\n\n📏 Total distance : " << distance << " units";
    cout << "\n🏁 Safe location  : ";

    int dest = path.back();
    if (!nodeNames.empty() && dest < (int)nodeNames.size()) {
        cout << nodeNames[dest];
    } else {
        cout << "Node " << dest;
    }

    cout << "\n\n✅ Follow this route to reach safety.\n";
    cout << "==========================================\n";
}

// ── displayNoPath() ──────────────────────────────────────────
// Called when ALL routes are blocked
// ────────────────────────────────────────────────────────────
void displayNoPath() {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║     ⚠️  WARNING: NO ROUTE FOUND      ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "All roads to safe zones are blocked.\n";
    cout << "Contact emergency services immediately.\n";
    cout << "==========================================\n";
}

// ── displayWelcome() ─────────────────────────────────────────
// Opening message shown when program starts
// ────────────────────────────────────────────────────────────
void displayWelcome() {
    cout << "\n==========================================\n";
    cout << "   DISASTER EVACUATION PLANNING SYSTEM   \n";
    cout << "==========================================\n";
    cout << "  Finding your safest evacuation route...\n";
    cout << "==========================================\n\n";
}

// ── displaySummary() ─────────────────────────────────────────
// Shows a final summary after path is found
// Good for demo / examiner presentation
// ────────────────────────────────────────────────────────────
void displaySummary(
    int totalNodes,
    int totalEdges,
    int blockedRoads,
    int pathLength,
    int distance
) {
    cout << "\n--- System Summary ---\n";
    cout << "Total locations  : " << totalNodes  << "\n";
    cout << "Total roads      : " << totalEdges  << "\n";
    cout << "Blocked roads    : " << blockedRoads << "\n";
    cout << "Path length      : " << pathLength   << " stops\n";
    cout << "Total distance   : " << distance     << " units\n";
    cout << "Algorithm used   : Dijkstra's (Priority Queue)\n";
    cout << "----------------------\n";
}