// Initial conectam fiecare bloc la cea mai apropiata centrala, apoi cautam
// cel mai apropiat bloc de acesta si il marcam ca vizitat pentru a nu-l
// considera de mai multe ori si modificam corespunzator distanta

// Complexitate: O(m^2), unde m = nr. blocuri


#include <bits/stdc++.h>
using namespace std;

ifstream fin ("retea2.in");
ofstream fout ("retea2.out");

int n, m, x, y;

vector <pair <int, int>> blocuri;
vector <pair <int, int>> centrale;
vector <double> distanta;
vector <bool> vizitat;
double total;


double distantaEuclidiana(pair <int, int> &a, pair <int, int> &b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}


int main() {
    fin >> n >> m;
    distanta.resize(m, INT_MAX);
    vizitat.resize(m, false);

    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        centrale.emplace_back(make_pair(x, y));
    }

    for (int i = 0; i < m; ++i) {
        fin >> x >> y;
        blocuri.emplace_back(make_pair(x, y));

        for (int j = 0; j < n; ++j)
            distanta[i] = min(distanta[i], distantaEuclidiana(blocuri[i], centrale[j]));
    }

    for (int i = 0; i < m; ++i) {
        double minDist = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < m; ++j) {
            if (distanta[j] < minDist && !vizitat[j]) {
                minDist = distanta[j];
                minIndex = j;
            }
        }

        vizitat[minIndex] = true;
        total += minDist;

        for (int j = 0; j < m; ++j)
            distanta[j] = min(distanta[j], distantaEuclidiana(blocuri[j], blocuri[minIndex]));
    }

    fout << fixed << setprecision(6) << total;

    fin.close();
    fout.close();
    return 0;
}