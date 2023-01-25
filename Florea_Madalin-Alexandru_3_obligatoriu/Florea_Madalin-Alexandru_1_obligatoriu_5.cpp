// Complexitate: O((m * 2^m) * n), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPathLength(vector <vector <int>>& graph) {
        int n = graph.size(); // Number of nodes in the graph

        // If the graph has only one node, the shortest path is 0
        if (n == 1) {
            return 0;
        }

        queue <tuple <int, int, int>> q; // Queue to store nodes, distance, and bitmask
        set <pair <int, int>> visited; // Set to store visited nodes and their bitmasks

        int all = (1 << n) - 1; // Bitmask representing all nodes visited

        for (int i = 0; i < n; ++i) {
            int bitMask = 1 << i; // Bitmask representing the current node visited
            q.push({i, 0, bitMask}); // Push the current node, distance (0), and bitmask onto the queue
            visited.insert({i, bitMask}); // Mark the current node as visited and add its bitmask to the set
        }


        while (!q.empty()) {
            tuple <int, int, int> firstInQueue = q.front();
            q.pop();

            // Destructure the tuple into individual variables
            auto [currentNode, distance, bitMask] = firstInQueue;

            // For each adjacent node to the current node
            for (auto const& adjNode : graph[currentNode]) {
                int newMask = bitMask | (1 << adjNode); // Update the bitmask to include the adjacent node

                // If the new bitmask represents all nodes visited return the distance + 1
                if (newMask == all) {
                    return distance + 1;
                }

                // If the adjacent node and new bitmask have already been visited, skip it
                if (visited.find({adjNode, newMask}) != visited.end()) {
                    continue;
                }

                // Push the adjacent node, distance + 1, and new bitmask onto the queue and mark it as visited
                q.push({adjNode, distance + 1, newMask});
                visited.insert({adjNode, newMask});
            }
        }

        // If the queue is empty and no solution is found, return 0
        return 0;
    }
};
