# Disaster Evacuation Planning System

Finds the shortest + safest evacuation path from a user's location to the nearest safe zone — even when roads are blocked.

## Algorithm
Dijkstra's algorithm with a min-heap priority queue on an adjacency list graph.

## Team
| Member | File | Role |
|--------|------|------|
| Sakshi | graph_input.cpp | Reads input, builds graph |
| You (Team Lead) | dijkstra.cpp | Core algorithm |
| Disha | blocked_roads.cpp | Road removal + recalculation |
| Tanisha | output.cpp | Display results |

## How to Compile
```bash
g++ main.cpp graph_input.cpp dijkstra.cpp blocked_roads.cpp output.cpp -o evacuation
./evacuation
```

## Input File Format (data/input.txt)
```
<nodes> <edges>
<node1> <node2> <distance>
...
```

Example:
```
6 8
0 1 4
0 2 1
2 1 2
1 3 5
2 3 8
3 4 2
4 5 3
1 5 10
```

## Git Branches
```
main          → final merged code
dijkstra-core → Team Lead
graph-input   → Sakshi
blocked-logic → Disha
ui-output     → Tanisha
```

## Viva One-Liner
"We modelled a city as a weighted graph and used Dijkstra's algorithm with a priority queue to compute the safest shortest evacuation path dynamically, even when roads are blocked, using a modular design."