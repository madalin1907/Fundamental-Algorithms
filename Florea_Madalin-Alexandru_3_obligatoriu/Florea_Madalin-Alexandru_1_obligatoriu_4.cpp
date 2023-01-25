// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector <vector <int>> validArrangement (vector <vector <int>>& pairs) {
        int m = pairs.size();

        // The adjacency list is implemented as a stack, because the Euler tour algorithm requires
        // that the edges be processed in a specific order. Specifically, the algorithm needs to
        // process the last edge added to the adjacency list before it processes the earlier edges.

        unordered_map <int, stack <int>> adjList; // Map to store adjacency lists as stacks
        unordered_map <int, int> indegree; // Map to store indegrees of nodes
        unordered_map <int, int> outdegree; // Map to store outdegrees of nodes
        vector <vector <int>> answer; // Vector to store answer

        // Reserve space in maps to avoid rehashing
        adjList.reserve(m);
        indegree.reserve(m);
        outdegree.reserve(m);

        // Populate maps with input data
        for (int i = 0; i < m; i++) {
            int x = pairs[i][0];
            int y = pairs[i][1];
            
            outdegree[x]++; // Increment outdegree of x
            indegree[y]++; // Increment indegree of y
            
            adjList[x].push(y); // Add y to adjacency list of x
        }

        // Find the node with an outdegree of 1 more than its indegree.
        // If no such node will be found, the start node will be the first element in the adjacency map.
        int start = adjList.begin()->first;

        for (auto const& pair : adjList) {
            int node = pair.first;
            if (outdegree[node] - indegree[node] == 1) {
                start = node;
            }
        }

        // Recursively compute the Euler tour and store the result in the answer vector
        euler(adjList, answer, start);

        reverse(answer.begin(), answer.end()); // Reverse the answer vector

        return answer;
    }

    
    
    // Recursive function to compute the Euler tour
    void euler(unordered_map <int, stack <int>>& adjList, vector <vector <int>>& answer, int current) {
        // Get the current node's adjacency list as a stack
        auto& currentStack = adjList[current];

        while (!currentStack.empty()) {
            int topItem = currentStack.top();
            currentStack.pop();

            // Recursively compute the Euler tour for the top element in the currentStack
            euler(adjList, answer, topItem);
            // Add the edge between the current node and the top element to the answer vector
            answer.push_back({current, topItem});
        }
    }
};