// Se salveaza listele de adiacenta cu probabilitatile corespunzatoare pentru fiecare muchie
// si se foloseste algoritmul lui Dijkstra pentru determinarea drumului cu probabilitate maxima.
// Vom stoca nodurile vizitate intr-un max-heap pentru ca varful extras sa fie mereu cel mai
// apropiat de start.

// Complexitate: O (n + m * log(n)) , unde m = nr. muchii, n = nr. noduri


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector <vector <int>> &edges, vector<double> &succProb, int start, int end) {
        list <pair <double, int>> *listaAdiacenta = new list <pair <double, int>> [n];

        for (int i = 0; i < edges.size(); ++i) {
            listaAdiacenta[edges[i][0]].push_back({succProb[i], edges[i][1]});
            listaAdiacenta[edges[i][1]].push_back({succProb[i], edges[i][0]});
        }

        // Dijkstra Algorithm
        vector <double> distanta (n, -1);
        priority_queue <pair <double, int>> heap;
        vector <bool> inHeap (n, false);

        distanta[start] = 1;
        heap.push({1, start});
        inHeap[start] = true;

        while (!heap.empty()) {
            pair <double, int> nod = heap.top();
            heap.pop();
            inHeap[nod.second] = false;

            for (auto const &vecin : listaAdiacenta[nod.second]) {
                double distanta = distanta[nod.second] * vecin.first;

                if (distanta > distanta[vecin.second]) {
                    distanta[vecin.second] = distanta;

                    if (!inHeap[vecin.second]) {
                        inHeap[vecin.second] = true;
                        heap.push({distanta[vecin.second], vecin.second});
                    }
                }
            }
        }

        if (distanta[end] == -1)
            return 0;
        else
            return distanta[end];
    }
};