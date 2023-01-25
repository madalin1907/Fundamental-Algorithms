// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

ifstream fin("harta.in");
ofstream fout("harta.out");

int n, source, sink;

vector <int> parent;
vector <vector <int>> capacity;
vector <vector <int>> adjNodeList;



// Functie care face BFS pe graf si returneaza true / false daca exista sau nu drum de la sursa la destinatie
bool bfs() {
    vector <bool> visited(sink + 1);
    queue <int> q;

    parent[source] = -1;
    visited[source] = true;

    q.push(source);


    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // daca vecinul n-a fost vizitat si exista capacitate pe muchie, se seteaza nodul curent ca fiind parintele nodului vecin si se adauga nodul vecin in coada
        for (auto const& neighbor: adjNodeList[node]) {
            if (!visited[neighbor] && capacity[node][neighbor]) {
                parent[neighbor] = node;

                if (neighbor == sink) {
                    return true;
                } // daca nodul vecin este nodul destinatie, se returneaza true

                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false; // daca nu s-a gasit drum de la sursa la destinatie, se returneaza false
}



int Edmonds_Karp() {
    int maxFlow = 0;

    while (bfs()) {
        int currentFlow = INT_MAX;

        // se parcurge invers drumul de la destinatie la sursa si se calculeaza fluxul minim pe drum
        int x = sink;
        while (parent[x] != -1) {
            int y = parent[x];

            if (capacity[y][x] < currentFlow) {
                currentFlow = capacity[y][x];
            }

            x = y;
        }

        // se parcurge invers drumul de la nodul destinatie la sursa folosindu-ne de parintele fiecarui nod si se actualizeaza capacitatea muchiilor
        x = sink;
        while (parent[x] != -1) {
            int y = parent[x];

            capacity[y][x] -= currentFlow;
            capacity[x][y] += currentFlow;

            x = y;
        }

        maxFlow += currentFlow;
    }

    return maxFlow;
}


int main() {
    fin >> n;
    sink = 2 * n + 1;

    adjNodeList.resize(sink + 1);
    parent.resize(sink + 1);
    capacity.resize(sink + 1, vector <int>(sink + 1));

    for (int i = 1; i <= n; ++i) {
        int x, y;
        fin >> x >> y;

        // se adauga muchie de la sursa la nodul curent cu capacitatea x (gradul de iesire al nodului curent)
        adjNodeList[source].push_back(i);
        capacity[source][i] = x;
        // se adauga muchie de la nodul curent la sursa (capacitatea muchiei este 0)
        adjNodeList[i].push_back(source);

        // se adauga muchie de la nodul curent la nodul destinatie cu capacitatea y (gradul de intrare al nodului curent)
        adjNodeList[n + i].push_back(sink);
        capacity[n + i][sink] = y;
        // se adauga muchie de la nodul destinatie la nodul curent (capacitatea muchiei este 0)
        adjNodeList[sink].push_back(n + i);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) { // pentru a nu adauga muchie de la un nod la el insusi
                adjNodeList[i].push_back(n + j); // se adauga muchie de la nodul i la nodul j cu capacitate 1
                capacity[i][n + j] = 1; // Set the capacity of the edge from node i to node j to 1

                adjNodeList[n + j].push_back(i); // se adauga muchie de la nodul j la nodul i cu capacitate 0
            }
        }
    }

    fout << Edmonds_Karp();

    for (int node = 1; node <= n; ++node) {
        for (auto const& neighbor : adjNodeList[node]) {
            // daca nodul vecin nu este nodul sursa sau destinatie si nu exista capacitate pe muchie intre nodul curent si nodul vecin, se afiseaza muchia
            if (neighbor != source && !capacity[node][neighbor] && neighbor != sink) {
                fout << '\n' << node << " " << neighbor - n;
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}