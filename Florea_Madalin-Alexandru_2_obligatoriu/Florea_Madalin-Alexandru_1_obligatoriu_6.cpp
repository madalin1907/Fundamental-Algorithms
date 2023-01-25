// Se retin listele de adiacenta, gradul intern si parintii fiecarui nod, apoi se foloseste
// algoritmul de sortare topologica. Se parcurg nodurile in ordinea din sortare si se
// actualizeaza pentru fiecare suma maxima posibila cu care se poate ajunge in nod printr-un lant.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii


#include <bits/stdc++.h>
using namespace std;

ifstream fin ("easygraph.in");
ofstream fout ("easygraph.out");

int t, n, m, x, y;

int main() {
    fin >> t;
    while (t) {
        fin >> n >> m;

        vector <long long> v (n + 1);
        vector <int> gradIntern (n + 1);
        vector <int> parinti[n + 1];
        list <int> listaAdiacenta[n + 1];

        for (int i = 1; i <= n; ++i)
            fin >> v[i];

        for (int i = 1; i <= m; ++i) {
            fin >> x >> y;
            listaAdiacenta[x].push_back(y);
            parinti[y].push_back(x);
            ++gradIntern[y];
        }


        // sortare topologica
        vector <int> sortareTopologica;
        queue <int> heap;

        for (int i = 1; i <= n; ++i)
            if (!gradIntern[i])
                heap.push(i);

        while (!heap.empty()) {
            int nod = heap.front();
            heap.pop();

            sortareTopologica.push_back(nod);

            for (auto const &vecin : listaAdiacenta[nod]) {
                --gradIntern[vecin];

                if (!gradIntern[vecin])
                    heap.push(vecin);
            }
        }

        vector <long long> suma (n + 1);
        long long sumaMaxima = LONG_LONG_MIN;

        for (auto const &nod : sortareTopologica) {
            suma[nod] = v[nod];

            for (auto const &parinte : parinti[nod])
                suma[nod] = max(suma[nod], suma[parinte] + v[nod]);

            sumaMaxima = max(sumaMaxima, suma[nod]);
        }

        fout << sumaMaxima << '\n';

        --t;
    }

    fin.close();
    fout.close();
    return 0;
}