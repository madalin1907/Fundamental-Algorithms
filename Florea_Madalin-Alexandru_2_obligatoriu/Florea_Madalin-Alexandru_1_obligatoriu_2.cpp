// Reprezentam fiecare multime ca pe un arbore cu radacina. Pentru o operatie de tip 2
// legam radacina arborelui cu inaltime mai mica de radacina nodului cu inaltime mai mare
// (considerand arborii din care fac parte (x si y). De asemenea, pentru fiecare interogare
// a unei radacini, legam de radacina fiecare nod parcurs (compresia drumurilor). Pentru o
// operatie de tip 1, verificam daca arborii din care fac parte x si y au aceeasi radacina.

// Complexitate: O(1) pentru o operatie de tip 1 si O(log*n) pentru o operatie de tip 2,
// unde n este numarul de noduri din graf


#include <bits/stdc++.h>
using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

int n, m, nrMultimi;
vector <int> tata;
vector <int> inaltime;


int radacina(int nod) {
    if(tata[nod] == 0) // daca este radacina
        return nod;

    tata[nod] = radacina(tata[nod]); // compresia drumurilor (legam fiecare nod de radacina)
    return tata[nod];
}


void unire(int x, int y) {
    int tataX = radacina(x);
    int tataY = radacina(y);
    int inaltimeX = inaltime[tataX];
    int inaltimeY = inaltime[tataY];

    // Legam arborele cu inaltime mai mica de cel cu inaltimea mai mare
    if (inaltimeX > inaltimeY) {
        tata[tataY] = tataX;
    }
    else if(inaltimeX < inaltimeY) {
        tata[tataX] = tataY;
    }
    else {
        tata[tataY] = tataX; // Daca au aceeasi inaltime, legam arborele din care face parte y de cel al lui x
        inaltime[tataX]++; // Dar si incrementam inaltimea arborelui din care face parte x
    }
}


int main()
{
    fin >> n >> m;
    nrMultimi = n;

    tata.resize(n + 1, 0);
    inaltime.resize(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        fin >> op >> x >> y;

        if (op == 1) {
            unire(x, y);
            fout << "Multimi ramase: " << --nrMultimi << "\n";
        }
        else if (op == 2) {
            if (radacina(x) == radacina(y))
                fout << "DA\n";
            else
                fout << "NU\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}