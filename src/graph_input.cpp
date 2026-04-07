#include <iostream>   // for input/output
#include <vector>     // for vector (graph storage)
#include <fstream>    // for file handling
using namespace std;

// pair to store (node, distance)
typedef pair<int,int> pii;

// adjacency list (max 100 nodes)
vector<pii> adj[100];

int N, E;  // N = nodes, E = edges

// take input from keyboard
void inputFromKeyboard() {
    cout << "Enter number of locations and roads: ";
    cin >> N >> E;   // input N and E

    cout << "Enter each road as: from  to  distance\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;   // input edge

        // check if distance is valid
        if (w < 0) {
            cout << "Error: distance cannot be negative!\n";
            i--;  // repeat this input
            continue;
        }

        // add edge both ways (undirected graph)
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

// take input from file
void inputFromFile(string filename) {
    ifstream file(filename);  // open file

    // check if file opened
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << "\n";
        return;
    }

    file >> N >> E;  // read N and E

    for (int i = 0; i < E; i++) {
        int u, v, w;
        file >> u >> v >> w;  // read edge

        // add edge both ways
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    file.close();  // close file
    cout << "Graph loaded from file successfully!\n";
}

// display graph
void displayGraph() {
    cout << "\n--- City Graph ---\n";

    for (int i = 0; i < N; i++) {
        cout << "Location " << i << " connects to: ";

        // print all neighbors
        for (pii neighbor : adj[i]) {
            cout << "(Location " << neighbor.first
                 << ", Distance " << neighbor.second << ")  ";
        }

        cout << "\n";
    }
}

// main function
int main() {
    int choice;

    cout << "1. Enter graph manually\n";
    cout << "2. Load from input.txt\n";
    cout << "Your choice: ";
    cin >> choice;   // user choice

    if (choice == 1)
        inputFromKeyboard();      // manual input
    else
        inputFromFile("data/input.txt");  // file input

    displayGraph();  // show graph

    return 0;
}