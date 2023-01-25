// Se foloseste algoritmul lui Prim pentru a gasi arborele partial de cost minim, folosindu-ne
// de un min-heap. O muchie va fi adaugata la arborele partial de cost minim daca numarul maxim
// de opriri inca nu a fost atins, altfel va fi ignorata.

// Complexitate: O(m * log(n)), unde m = nr. muchii, n = nr. noduri.


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector <vector <int>>& flights, int src, int dst, int k) {
        vector <pair <int, int>> listaAdiacenta[n];
        for(auto const &flight : flights)
            listaAdiacenta[flight[0]].push_back(make_pair(flight[1],flight[2]));

        vector <int> distance(n, INT_MAX);
        priority_queue <tuple <int, int, int>> heap; // <distanta de la start, nod, opriri>

        distance[src] = 0;
        heap.push(make_tuple(0, src, 0));

        while (!heap.empty()) {
            tuple <int, int, int> firstInHeap = heap.top();
            heap.pop();

            int distanta = get <0> (firstInHeap);
            int nod = get <1> (firstInHeap);
            int opriri = get <2> (firstInHeap);

            for (auto const &vecin : listaAdiacenta[nod]) {
                if ((distanta + vecin.second) < distance[vecin.first] && opriri <= k) {
                    distance[vecin.first] = distanta + vecin.second;
                    heap.push(make_tuple(distance[vecin.first], vecin.first, opriri + 1));
                }
            }
        }

        if (distance[dst] == INT_MAX)
            return -1;
        else
            return distance[dst];
    }
};