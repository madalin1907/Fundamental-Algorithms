// Se sorteaza listele de adiacenta in functie de ordinea din permutarea citita,
// apoi se utilizeaza parcurgerea DFS si, la final, se compara ordinea in care
// au fost parcurse nodurile cu cea din permutare

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

int nrNoduri, nrMuchii;
vector <int> permutare;
vector <int> pozitiePermutare;
vector <int> dfsOrder;
vector <bool> vizitat;
vector <int> *listaAdiacenta;


bool compararePozitie (int &a, int &b) {
    return pozitiePermutare[a] < pozitiePermutare[b];
}


void dfs (int nod){
    dfsOrder.push_back(nod);
    vizitat[nod] = true;

    for (auto &nodAdiacent : listaAdiacenta[nod]) {
        if (!vizitat[nodAdiacent])
            dfs(nodAdiacent);
    }
}


int main() {
    cin >> nrNoduri >> nrMuchii;

    listaAdiacenta = new vector <int> [nrNoduri + 1];
    vizitat.resize(nrNoduri + 1);
    pozitiePermutare.resize(nrNoduri + 1);

    int x, y;
    for (int i = 0; i < nrNoduri; ++i) {
        cin >> x;
        permutare.push_back(x);
        pozitiePermutare[x] = i;
    }
    for (int i = 0; i < nrMuchii; ++i) {
        cin >> x >> y;
        listaAdiacenta[x].push_back(y);
        listaAdiacenta[y].push_back(x);
    }

    for (int i = 1; i <= nrNoduri; ++i)
        sort(listaAdiacenta[i].begin(), listaAdiacenta[i].end(), compararePozitie);

    dfs(1);
    cout << (permutare == dfsOrder);

    return 0;
}