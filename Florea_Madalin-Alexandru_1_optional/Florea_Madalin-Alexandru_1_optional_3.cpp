// Se utilizeaza parcurgerea bfs incepand din nodurile x, respectiv y, retinand lungimile drumurilor de la acestea
// la celelalte noduri. Verificam nodurile ale caror distanta pana la x si pana la y insumeaza chiar distanta de la
// x la y, iar cand se respecta aceasta conditie, crestem frecventa distantei de la nodul curent pana la nodul x.
// Distantele care au frecventa mai mare ca 1 nu corespund varfurilor dorite in problema, deoarece nodurile respective
// se afla pe acelasi nivel in parcurgerea bfs. Nodurile dorite sunt cele care sunt singure pe nivel (luand in
// considerare numai nodurile care respecta suma de mai sus) pentru ca "obliga" toate lanturile optime sa treaca prin ele.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

ifstream fin ("graf.in");
ofstream fout ("graf.out");

int n, m, x, y, nrVfComune;

list <int> *listaAdiacenta;
vector <int> distantaX;
vector <int> distantaY;
vector <int> frecvDistante;

void bfs (int &start, vector <int> &distanta) {
    vector <bool> vizitat(n + 1, false);
    queue <int> coada;

    coada.push(start);
    vizitat[start] = true;

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();

        for (auto const &vecin : listaAdiacenta[nod])
            if (!vizitat[vecin]) {
                coada.push(vecin);
                distanta[vecin] = distanta[nod] + 1;
                vizitat[vecin] = true;
            }
    }
}


int main() {
    fin >> n >> m >> x >> y;

    listaAdiacenta = new list <int> [n + 1];
    distantaX.resize(n + 1);
    distantaY.resize(n + 1);
    frecvDistante.resize(n);

    int a, b;
    for (int i = 1; i <= m; ++i) {
        fin >> a >> b;
        listaAdiacenta[a].push_back(b);
        listaAdiacenta[b].push_back(a);
    }

    bfs(x, distantaX);
    bfs(y, distantaY);

//    for (auto &i: distantaX)
//        cout << i << ' ';
//    cout << '\n';
//    for (auto &i: distantaY)
//        cout << i << ' ';

    int distantaXY = distantaX[y];
    vector <int> indici;

    for (int i = 1; i <= n; ++i)
        if (distantaX[i] + distantaY[i] == distantaXY) {
            ++frecvDistante[distantaX[i]];
            indici.push_back(i);
        }

    for (auto &i : indici)
        if (frecvDistante[distantaX[i]] == 1)
            ++nrVfComune;

    fout << nrVfComune << '\n';

    for (auto &i : indici)
        if (frecvDistante[distantaX[i]] == 1)
            fout << i << ' ';

    fin.close();
    fout.close();
    return 0;
}