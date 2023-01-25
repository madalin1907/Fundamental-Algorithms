// Calculam distanta Levenshtein intre oricare 2 cuvinte si le ordonam crescator dupa aceasta.
// Cuvintele cele mai apropiate care fac parte din clustere diferite se unesc pana cand ramanem
// cu k clustere, apoi calculam gradul de separare minim.

// Complexitate: n^2, unde n = nr. cuvinte


#include <bits/stdc++.h>
using namespace std;

ifstream fin("cuvinte.in");
ofstream fout("cuvinte.out");


int n, k;
string cuvant;
vector <string> cuvinte;
unordered_map <string, int> cluster;
vector <tuple <string, string, int>> perechiCuvinte;


int distantaLevenshtein(const string &cuvant1, const string &cuvant2, int lungime1, int lungime2) {
    if (lungime1 == 0)
        return lungime2;
    if (lungime2 == 0)
        return lungime1;
    if (cuvant1[lungime1 - 1] == cuvant2[lungime2 - 1])
        return distantaLevenshtein(cuvant1, cuvant2, lungime1 - 1, lungime2 -1);

    return 1 + min(distantaLevenshtein(cuvant1, cuvant2, lungime1 - 1, lungime2 - 1),
               min(distantaLevenshtein(cuvant1, cuvant2, lungime1 - 1, lungime2),
                   distantaLevenshtein(cuvant1, cuvant2, lungime1, lungime2 - 1)));
}


bool comp (const tuple <string, string, int> &a, const tuple <string, string, int > &b) {
    return get <2> (a) < get <2> (b);
}


int main() {
    cin >> k;
    while (fin >> cuvant) {
        cuvinte.push_back(cuvant);
        cluster[cuvant] = n++;
    }

    // calculare distanta Levenshtein intre fiecare 2 cuvinte
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            int distanta = distantaLevenshtein(cuvinte[i], cuvinte[j], cuvinte[i].length(), cuvinte[j].length());
            perechiCuvinte.emplace_back(make_tuple(cuvinte[i], cuvinte[j], distanta));
        }

    sort(perechiCuvinte.begin(), perechiCuvinte.end(), comp);

    // impartire clustere
    for (int i = 0; i < n - k; ++i) {
        int j = 0;
        while (cluster[get <0> (perechiCuvinte[j])] == cluster[get <1> (perechiCuvinte[j])])
            ++j;

        int cluster1 = cluster[get < 0 > (perechiCuvinte[j])];
        int cluster2 = cluster[get < 1 > (perechiCuvinte[j])];
        int minCluster = min(cluster1, cluster2);
        for (auto &cuvant : cluster) {
            if (cuvant.second == cluster1 || cuvant.second == cluster2) {
                cuvant.second = minCluster;
            }
        }
    }

    // calculare grad de separare
    int gradSeparare = INT_MAX;
    for (auto const &cluster1 : cluster) {
        for (auto const &cluster2 : cluster)
            if (cluster1.second != cluster2.second) {
                int distanta = distantaLevenshtein(cluster1.first, cluster2.first, cluster1.first.length(),
                                               cluster2.first.length());
                if (distanta < gradSeparare)
                    gradSeparare = distanta;
            }
    }

    // afisare
    for (int i = 0; i < n; ++i) {
        bool areCuvant = false;
        for (auto const &cuvant : cluster) {
            if (cuvant.second == i) {
                fout << cuvant.first << " ";
                areCuvant = true;
            }
        }
        if (areCuvant)
            fout << '\n';
    }
    fout << gradSeparare;


    fin.close();
    fout.close();
    return 0;
}