// Complexitate: O(n * m^2), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

int sizeLeft; // nr. de noduri din partea stanga a grafului bipartit
int sizeRight; // nr. de noduri din partea dreapta a grafului bipartit
int edges; // nr. total de muchii
int source, sink; // nodurile sursa si destinatie

vector <pair <int, int>> parent; // perechi de tip <nod, indexul muchiei> care retin nodul din care s-a ajuns la nodul curent si indexul muchiei care a fost folosita
vector <pair <int, int >> sinkEdges; // perechi de tip <nod, indexul muchiei> care reprezinta muchiile care conecteaza nodurile din dreapta grafului cu nodul destinatie
vector <vector <pair <int, pair <int, int> >>> adjList; // perechi de tip <nod, <capacitate, indexul muchiei catre nodul vecin>> care reprezinta muchiile grafului
vector <bool> rightNodes; // vector pentru a retine nodurile din dreapta grafului bipartit conectate la cel putin un nod din partea stanga


void createEdge(int x, int y) {
    // muchie de la nodul x la nodul y cu capacitate 1 si indexul muchiei
    adjList[x].push_back({y, {1,adjList[y].size()}});

    // muchie de la nodul y la nodul x cu capacitate 0 si indexul muchiei
    adjList[y].push_back({x, {0,adjList[x].size() - 1}});

    // daca nodul y este nodul destinatie, adaugam muchia la lista de muchii care conecteaza nodurile din partea dreapta a grafului bipartit la nodul destinatie
    if (y == sink) {
        sinkEdges.emplace_back(x, adjList[x].size() - 1);
    }
}



// Functie care face BFS pe graf si returneaza true / false daca exista sau nu drum de la sursa la destinatie
bool bfs() {
    vector <bool> visited(sink + 1);
    queue <int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = {-1, -1};

    while (!q.empty()) {
        int firstInQueue = q.front();
        q.pop();

        if (firstInQueue == sink) {
            return true;
        }

        int edgeIndex = 0;

        for (auto const& neighbor : adjList[firstInQueue]) {
            int node = neighbor.first; // nodul vecin
            int capacity = neighbor.second.first; // capacitatea muchiei


            if (!visited[node] && capacity) {
                parent[node] = {firstInQueue, edgeIndex};
                visited[node] = true;
                q.push(node);
            } // daca vecinul n-a fost vizitat si exista capacitate pe muchie, se seteaza parintele nodului vecin si indexul muchiei curente, apoi acesta se adauga in coada

            ++edgeIndex;
        }
    }

    return false;
}



int Edmonds_Karp() {
    int maxFlow = 0;

    while (bfs()) {
        for (auto const& neighbor : sinkEdges) {  // se parcurge lista de muchii care conecteaza nodurile din partea dreapta a grafului bipartit la nodul destinatie
            int currentFlow = 1;
            parent[sink] = neighbor; // se seteaza parintele nodului destinatie la nodul curent

            int y = sink;
            while (parent[y].first != -1) { // se parcurge invers drumul de la nodul destinatie la sursa folosindu-ne de parintele fiecarui nod

                int x = parent[y].first;
                int i = parent[y].second;

                currentFlow = min(currentFlow, adjList[x][i].second.first); // se calculeaza fluxul curent ca fiind minimul dintre fluxul curent si capacitatea muchiei
                y = x;
            }

            // se actualizeaza fluxul pe muchii, parcurgand din nou drumul de la nodul destinatie la sursa
            y = sink;
            while (parent[y].first != -1) {
                int a = parent[y].first;
                int b = parent[y].second;
                int c = adjList[a][b].second.second;

                adjList[a][b].second.first -= currentFlow;
                adjList[y][c].second.first += currentFlow;

                y = a;
            }

            maxFlow += currentFlow;
        }
    }

    return maxFlow;
}



int main() {
    fin >> sizeLeft >> sizeRight >> edges;

    // source = 0;
    sink = sizeLeft + sizeRight + 1;

    parent.resize(sink + 1);
    adjList.resize(sink + 1);
    rightNodes.resize(sizeRight + 1);

    for (int i = 1; i <= sizeLeft; ++i) {
        createEdge(source, i); // legam nodul sursa 0 de toate nodurile din partea stanga a grafului bipartit
    }

    for (int i = 1; i <= edges; ++i) {
        int x, y;
        fin >> x >> y;
        createEdge(x, sizeLeft + y); // legam nodurile din partea stanga a grafului bipartit cu nodurile din partea dreapta a grafului bipartit
        rightNodes[y] = true;
    }

    for (int i = 1; i <= sizeRight; ++i) {
        if (rightNodes[i]) {
            createEdge(sizeLeft + i, sink); // legam nodurile din partea dreapta a grafului bipartit cu nodul destinatie
        }
    }


    fout << Edmonds_Karp();

    // pentru fiecare nod din partea stanga a grafului bipartit cautam nodul din dreapta la care este conectat
    for (int node = 1; node <= sizeLeft; ++node) {
        for (auto const &neighbor : adjList[node]) {
            int vertex = neighbor.first;
            int capacity = neighbor.second.first;

            if (vertex && capacity == 0 && vertex != sink) { // daca nodul vecin nu este nodul sursa / destinatie si capacitatea muchiei este 0, inseamna ca nodul curent este conectat la nodul vecin
                fout << '\n' << node << " " << vertex - sizeLeft;
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}