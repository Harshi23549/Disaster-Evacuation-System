// output.h  —  Tanisha's Header
// Include this in main.cpp to use display functions

#pragma once
#include <vector>
#include <string>
using namespace std;

// Shows welcome banner when program starts
void displayWelcome();

// Prints the full evacuation path and distance
// nodeNames is optional — pass empty vector if not using names
void displayPath(
    const vector<int>& path,
    int distance,
    const vector<string>& nodeNames
);

// Called when ALL routes are blocked — no path found
void displayNoPath();

// Final summary shown at end — good for examiner demo
void displaySummary(
    int totalNodes,
    int totalEdges,
    int blockedRoads,
    int pathLength,
    int distance
);