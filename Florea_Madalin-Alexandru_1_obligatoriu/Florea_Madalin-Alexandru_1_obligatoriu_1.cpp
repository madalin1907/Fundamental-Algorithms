// a)
// Se utilizează parcurgerea BFS pornind din fiecare nod ce nu a fost inca vizitat
// (am considerat un nod ca fiind nevizitat daca nu i-a fost setat deja un grup).
// Daca doua noduri adiacente au setat acelasi grup, inseamna ca graful nu este bipartit.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool bfs (int n, int node, list <int> *listaAdiacenta, vector <int> &grup) {
        queue <int> coada;

        grup[node] = 1;
        coada.push(node);

        while (!coada.empty()) {
            int nod = coada.front();
            coada.pop();

            for (auto &i : listaAdiacenta[nod]) {
                if (grup[i] == 0) {
                    grup[i] = grup[nod] == 1 ? 2 : 1;
                    coada.push(i);
                }
                else if (grup[i] == grup[nod])
                    return false;
            }
        }
        return true;
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        list <int> *listaAdiacenta = new list <int> [n + 1];
        vector <bool> vizitat(n + 1, false);
        vector <int> grup (n + 1, 0);

        for (auto &dislike: dislikes) {
            listaAdiacenta[dislike[0]].push_back(dislike[1]);
            listaAdiacenta[dislike[1]].push_back(dislike[0]);
        }

        for (int i = 1; i < n; ++i)
            if (grup[i] == 0) {
                bool ok = bfs(n, i, listaAdiacenta, grup);
                if (!ok)
                    return false;
            }
        return true;
    }
};






// b)
// Se utilizeaza algoritmul de la punctul a) si, in plus, de fiecare data cand se
// seteaza grupul unui nod, acesta se adauga in vectorul de solutii corespunzator.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

class Solution {
public:
    bool bfs (int n, int node, list <int> *listaAdiacenta, vector <int> &grup, vector <int> *solution) {
        queue <int> coada;

        grup[node] = 1;
        coada.push(node);

        while (!coada.empty()) {
            int nod = coada.front();
            coada.pop();

            for (auto &i : listaAdiacenta[nod]) {
                if (grup[i] == 0) {
                    grup[i] = grup[nod] == 1 ? 2 : 1;
                    solution[grup[i]].push_back(i);
                    coada.push(i);
                }
                else if (grup[i] == grup[nod])
                    return false;
            }
        }
        return true;
    }

    vector <vector <int> > possibleBipartition(int n, vector <vector <int> > &dislikes) {
        list <int> *listaAdiacenta = new list <int> [n + 1];
        vector <bool> vizitat(n + 1, false);
        vector <int> grup (n + 1, 0);
        vector <int> solution[2];

        for (auto &dislike: dislikes) {
            listaAdiacenta[dislike[0]].push_back(dislike[1]);
            listaAdiacenta[dislike[1]].push_back(dislike[0]);
        }

        for (int i = 1; i < n; ++i)
            if (grup[i] == 0) {
                bool ok = bfs(n, i, listaAdiacenta, grup, solution);
                if (!ok)
                    return {};
            }

        return {solution[1], solution[2]};
    }
};