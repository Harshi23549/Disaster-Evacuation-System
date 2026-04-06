#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

// Function to print path
void printPath(vector<int>& parent, int j) {
    if (j == -1) return;
    printPath(parent, parent[j]);
    cout << j << " ";
}

// Dijkstra Algorithm
void dijkstra(int V, vector<vector<pii>>& adj, int src) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest Paths from Source " << src << ":\n";

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            cout << "To " << i << ": No path\n";
        } else {
            cout << "To " << i << " (Cost: " << dist[i] << "): Path = ";
            printPath(parent, i);
            cout << endl;
        }
    }
}

int main() {
    int V, E;

    cout << "Enter number of nodes: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pii>> adj(V);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // remove if directed graph
    }

    int source;
    cout << "Enter source node: ";
    cin >> source;

    dijkstra(V, adj, source);

    return 0;
}