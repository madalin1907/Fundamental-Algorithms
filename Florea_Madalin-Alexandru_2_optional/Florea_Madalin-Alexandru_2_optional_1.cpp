// Se foloseste algoritmul lui Prim pentru a gasi arborele partial de cost minim care
// uneste toate punctele. Pornim din primul nod si adaugam distantele pana la toate
// celelalte noduri intr-un min-heap. Luam prima muchie din heap si, daca ajunge intr-un
// nod nevizitat, o adaugam in arborele partial de cost minim. Procesul se repeta pana
// cand nu mai raman noduri de vizitat.


// Complexitate: O(m * log(n)), unde m = nr. muchii, n = nr. noduri


#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int manhattanDistance(vector <int> node1, vector <int> node2) {
        return abs(node1[0] - node2[0]) + abs(node1[1] - node2[1]);
    }

    int minCostConnectPoints(vector <vector <int>> &points) {
        int minCost = 0;

        int n = points.size();
        int leftToVisit = n;
        vector <bool> visited(n, false);

        priority_queue <pair <int, int>, vector <pair <int, int>>, greater <>> heap;
                    // <distance from currentNode, index of node>

        vector <int> currentNode = points[0];
        visited[0] = true;
        --leftToVisit;

        for (int i = 1; i < n; ++i) {
            int distance = manhattanDistance(currentNode, points[i]);
            heap.push(make_pair(distance, i));
        }

        while (leftToVisit && !heap.empty()) {
            pair <int, int> heapTopNode= heap.top();
            heap.pop();

            int index = heapTopNode.second;

            if (!visited[index]) {
                visited[index] = true;
                --leftToVisit;

                minCost += heapTopNode.first;

                currentNode = points[index];

                for (int i = 0; i < n; ++i) {
                    if (i != index && !visited[i]) {
                        int distance = manhattanDistance(currentNode, points[i]);
                        heap.push(make_pair(distance, i));
                    }
                }
            }
        }

        return minCost;
    }
};