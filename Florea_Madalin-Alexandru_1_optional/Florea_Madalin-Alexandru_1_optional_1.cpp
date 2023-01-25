// Se construiesc listele de adiacenta ale nodurilor, apoi folosim parcurgerea DFS incepand
// cu nodul 0, actualizand pentru fiecare nod nivelul pe care se afla, dar si nivelul minim
// al acestuia (nivelul minim la care se închide un ciclu elementar care conține vârful i
// printr-o muchie de întoarcere). O muchie este critica daca nivelul minim al unui nod x
// este mai mare decat nivelul tatalui sau (tata = nodul din care s-a ajuns in nodul x prin
// parcurgerea DFS).

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void df (int nod, list <int> *listaAdiacenta, vector <int> &nivel, vector <int> &nivelMinim, vector <vector <int>> &muchiiCritice) {
        nivelMinim[nod] = nivel[nod];

        for (auto &vecin : listaAdiacenta[nod]) {
            if (!nivel[vecin]) { // muchie de avansare
                nivel[vecin] = nivel[nod] + 1;
                df(vecin, listaAdiacenta, nivel, nivelMinim, muchiiCritice);

                // actualizare nivel minim
                nivelMinim[nod] = min(nivelMinim[nod], nivelMinim[vecin]);

                // test muchie critica
                if (nivelMinim[vecin] > nivel[nod])
                    muchiiCritice.push_back({nod, vecin});
            }
            else {
                if (nivel[vecin] < nivel[nod] - 1) // muchie de intoarcere
                    nivelMinim[nod] = min(nivelMinim[nod], nivel[vecin]);
            }
        }
    }

    vector <vector <int>> criticalConnections(int n, vector <vector <int>> &connections) {
        vector <vector <int>> muchiiCritice;

        vector <int> nivel(n);
        vector <int> nivelMinim(n);

        list <int> *listaAdiacenta = new list <int> [n];
        for (auto const &muchie : connections) {
            listaAdiacenta[muchie[0]].push_back(muchie[1]);
            listaAdiacenta[muchie[1]].push_back(muchie[0]);
        }

        nivel[0] = 1;

        df(0, listaAdiacenta, nivel, nivelMinim, muchiiCritice);

        return muchiiCritice;
    }
};