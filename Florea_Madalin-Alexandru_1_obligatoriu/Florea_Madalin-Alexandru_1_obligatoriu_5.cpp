// Se utilizează algoritmul BFS pornind din fiecare punct de control, iar distanta minima
// pentru un nod este actualizată la prima vizitare a acestuia din fiecare parcurgere

// Complexitate: O(k * (n + m)), unde k = nr. puncte control, n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

ifstream fin ("graf.in");
ofstream fout ("graf.out");

int nrNoduri, nrMuchii;
list <int> *listaAdiacenta;
vector <int> puncteControl;
vector <int> distanta;

void bfs (int node) {
    vector <bool> vizitat(nrNoduri + 1, false);
    vector <int> distantaLocala(nrNoduri + 1, 0);
    queue <int> coada;

    vizitat[node] = true;
    coada.push(node);

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();

        for (auto &i : listaAdiacenta[nod]) {
            if (!vizitat[i]) {
                vizitat[i] = true;
                coada.push(i);
                distantaLocala[i] = distantaLocala[nod] + 1;

                if (distanta[i] == -1)
                    distanta[i] = distantaLocala[i];
                else
                    distanta[i] = min(distanta[i], distantaLocala[i]);
            }
        }
    }
}

int main() {
    fin >> nrNoduri >> nrMuchii;
    listaAdiacenta = new list <int> [nrNoduri + 1];
    distanta.resize(nrNoduri, -1);

    int x, y;

    for (int i = 1; i <= nrMuchii; ++i) {
        fin >> x >> y;
        listaAdiacenta[x].push_back(y);
        listaAdiacenta[y].push_back(x);
    }

    while (fin >> x)
        puncteControl.push_back(x);

//    for (int i = 1; i <= nrNoduri; ++i) {
//        for (auto &j: listaAdiacenta[i])
//            cout << j << " ";
//        cout << "\n";
//    }

    for (auto &punct : puncteControl) {
        distanta[punct] = 0;
        bfs(punct);
    }

    for (int i = 1; i <= nrNoduri; ++i)
        fout << distanta[i] << " ";

    fin.close();
    fout.close();
    return 0;
}