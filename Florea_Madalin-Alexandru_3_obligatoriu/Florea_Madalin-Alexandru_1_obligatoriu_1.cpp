// Complexitate: O(n * m^2), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

ifstream fin ("maxflow.in");
ofstream fout ("maxflow.out");

int n, m, maxFlow;
list <int> *adjList;
vector <vector <int>> capacity;
vector <int> parent;


// Functie care face BFS pe graf si returneaza true / false daca exista sau nu drum de la sursa la destinatie
bool bfs() {
    parent.assign(n + 1, 0);
    queue <int> q;

    q.push(1);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == n) { // daca s-a ajuns la nodul destinatie
            return true;
        }

        for (auto const& neighbor : adjList[node]) {
            int currentCapacity = capacity[node][neighbor];

            // nodul se ia in considerare daca nu a fost inca vizitat si daca exista capacitate pentru a ajunge in el
            if (currentCapacity > 0 && parent[neighbor] == 0) {
                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }

    return false; // daca nu s-a ajuns la nodul destinatie
}



int main() {
    // Citirea datelor
    fin >> n >> m;
    adjList = new list <int> [n + 1];
    parent.resize(n + 1, 0);
    capacity.resize(n + 1, vector <int> (n + 1, 0));

    int x, y, z;
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> z;

        adjList[x].push_back(y);
        adjList[y].push_back(x);

        capacity[x][y] = z;
    }


    // ALGORITMUL EDMONDS-KARP
    while (bfs()) {
        for (auto const& node : adjList[n]) {
            if (parent[node]) { // daca nodului i-a fost setat un parinte (adica daca a fost luat in considerare in BFS)
                parent[n] = node; // se seteaza nodul curent ca fiind parintele nodului destinatie

                // se gaseste capacitatea minima a drumului de la sursa la destinatie generat de bfs
                int currentFlow = INT_MAX, i = n;
                while (i != 1) {
                    currentFlow = min(currentFlow, capacity[parent[i]][i]);
                    i = parent[i];
                }

                i = n; // se actualizeaza capacitatile muchiilor din drumul de la sursa la destinatie
                while (i != 1) {
                    capacity[parent[i]][i] -= currentFlow;
                    capacity[i][parent[i]] += currentFlow;
                    i = parent[i];
                }

                maxFlow += currentFlow;
            }
        }
    }

    fout << maxFlow << '\n';





    // b) Taietura minima (Min-Cut)
    fout << "\nTaietura minima:\n";

    // Mai parcurgem o data graful BFS pentru a vedea care sunt nodurile accesibile din sursa
    queue <int> q;
    vector <bool> visited(n + 1, false);

    visited[1] = true;
    q.push(1);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == n) {
            break;
        }

        for (auto const& neighbor: adjList[node]) {
            int currentCapacity = capacity[node][neighbor];

            if (currentCapacity > 0 && !visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto const& adjNode : adjList[i]) {
            if (visited[i] && !visited[adjNode]) { // daca nodul i este accesibil din sursa si nodul adiacent lui i nu este accesibil din sursa
                fout << i << " " << adjNode << '\n';
            }
        }
    }


    fin.close();
    fout.close();
    return 0;
}