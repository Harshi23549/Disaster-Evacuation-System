// graph_input.h  —  Sakshi's Header
// Include this wherever you need the graph structure

#pragma once
#include <vector>
#include <utility>
#include <string>
using namespace std;

typedef pair<int,int> pii;

// Reads graph from user input (keyboard)
void buildGraphFromInput(vector<vector<pii>>& graph, int& n, int& edges);

// Reads graph from input.txt file
void buildGraphFromFile(vector<vector<pii>>& graph, int& n, int& edges, const string& filename);

// Prints adjacency list (for debugging)
void printGraph(const vector<vector<pii>>& graph, int n);

// Returns list of safe zone node numbers
vector<int> getSafeZones(int n);