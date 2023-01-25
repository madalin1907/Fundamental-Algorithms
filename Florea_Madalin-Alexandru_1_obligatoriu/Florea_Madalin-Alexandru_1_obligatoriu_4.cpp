// Se foloseste algoritmul lui Kosaraju, care presupune urmatorii pasi: se salveaza
// listele de adiacenta pentru graful citit si pentru graful transpus, se efectueaza
// parcurgerea DFS in graful normal si se adauga intr-o stiva fiecare varf in momentul
// in care este finalizat, apoi se parcurg DFS varfurile in graful transpus in ordinea
// in care acestea sunt extrase din stiva.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii
// 2 parcurgeri dfs -> O(n + m) + constructia grafurilor -> O(m)

#include <bits/stdc++.h>
using namespace std;

ifstream fin ("ctc.in");
ofstream fout ("ctc.out");

int nrNoduri, nrMuchii;

list <int> *listaGraf;
list <int> *listaGrafTranspus;
vector <int> vizitat;
stack <int> stiva;

vector <vector <int>> componente;
vector <int> componenta;



void dfsGraf (int nod) {
    vizitat[nod] = 1;
    for (auto &nodAdiacent : listaGraf[nod]) {
        if (!vizitat[nodAdiacent])
            dfsGraf(nodAdiacent);
    }
    stiva.push(nod);
}


void dfsGrafTranspus (int nod) {
    componenta.push_back(nod);
    vizitat[nod] = 1;
    for (auto &nodAdiacent : listaGrafTranspus[nod]) {
        if (!vizitat[nodAdiacent])
            dfsGrafTranspus(nodAdiacent);
    }
}


int main() {
    fin >> nrNoduri >> nrMuchii;

    listaGraf = new list <int> [nrNoduri + 1];
    listaGrafTranspus = new list <int> [nrNoduri + 1];
    vizitat.resize(nrNoduri);

    int x, y;
    for (int i = 0; i < nrMuchii; ++i) {
        fin >> x >> y;
        listaGraf[x].push_back(y);
        listaGrafTranspus[y].push_back(x);
    }

//    for (int i = 1; i <= nrNoduri; ++i) {
//        for (auto &j: listaGrafTranspus[i])
//            cout << j << " ";
//        cout << "\n";
//    }


    for (int i = 1; i <= nrNoduri; ++i)
        if (!vizitat[i])
            dfsGraf(i);

    for (int i = 1; i <= nrNoduri; ++i)
        vizitat[i] = 0;

    while (!stiva.empty()) {
        int nod = stiva.top();
        stiva.pop();

        if (!vizitat[nod]) {
            dfsGrafTranspus(nod);
            componente.push_back(componenta);
            componenta.clear();
        }
    }

    for (int i = 1; i <= nrNoduri; ++i) {
        if (!vizitat[i]) {
            dfsGrafTranspus(i);
            componente.push_back(componenta);
            componenta.clear();
        }
    }


    fout << componente.size();
    for (auto &comp : componente) {
        fout << '\n';
        for (auto &i : comp)
            fout << i << ' ';
    }


    fin.close();
    fout.close();
    return 0;
}