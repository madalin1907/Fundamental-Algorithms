// Folosim algoritmul lui Dijkstra cu ajutorul unui min heap si retinem pentru fiecare catun
// cea mai apropiata fortareata. Cand distanta de la un nod x + distanta de la un nod x la un nod
// y este mai mica decat distanta pana la y, updatam vectorul de distante si cea mai apropiata
// fortareata.


// Complexitate: O(m * log(n)), unde m = nr. de muchii, n = nr. de noduri


#include <bits/stdc++.h>
using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

vector <int> fortareata;
vector <int> distanta;
vector <pair <int, int >> *listaAdiacenta;
priority_queue <pair <int, int>, vector <pair <int, int>>, greater<>> heap;

int n, m, k, x, y, z;


int main() {
    fin >> n >> m >> k;
    fortareata.resize(n + 1);
    distanta.resize(n + 1, INT_MAX);
    listaAdiacenta = new vector <pair <int, int>> [n + 1];

    for(int i = 0; i < k; ++i) {
        fin >> x;
        fortareata[x] = x;
        heap.push({0, x});
        distanta[x] = 0;
    }

    for(int i = 0; i < m; ++i) {
        fin >> x >> y >> z;
        listaAdiacenta[x].emplace_back(make_pair(y, z));
        listaAdiacenta[y].emplace_back(make_pair(x, z));
    }

    // Dijkstra Algorithm
    while(!heap.empty()){
        int nod = heap.top().second;
        heap.pop();

        for (auto const& vecin : listaAdiacenta[nod]) {
            if (distanta[nod] + vecin.second < distanta[vecin.first]) {
                distanta[vecin.first] = distanta[nod] + vecin.second;
                heap.push({distanta[vecin.first], vecin.first});
                fortareata[vecin.first] = fortareata[nod];
            }
            else if (distanta[nod] + vecin.second == distanta[vecin.first]) {
                fortareata[vecin.first] = min(fortareata[vecin.first], fortareata[nod]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (fortareata[i] == i)
            fout << 0 << ' ';
        else
            fout << fortareata[i] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}