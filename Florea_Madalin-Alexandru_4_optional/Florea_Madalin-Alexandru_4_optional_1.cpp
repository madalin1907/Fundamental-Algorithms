// Algoritmii folositi pentru rezolvarea acestei probleme sunt cautarea binara si BFS.

// Folosind notiuni de grafuri, problema imi cere sa gasesc costul maxim al unui un care pleaca
// din nodul 1 si ajunge in nodul n.

// Ideea rezolvarii este urmatoarea: pe masura ce construiesc listele de adiacenta ale nodurilor,
// mi-am salvat separat intr-o variabila greutatea maxima admisa pe drumurile citite, aceasta
// urmand sa fie capatul din dreapta la cautarea binara. Binar, eu caut cea mai mare greutate
// care permite sa ajungem din nodul 1 in nodul n folosind BFS-ul. Pentru acest lucru,algoritmul de
// BFS are o mica modificare, aceea ca pe langa conditia ca nodul vecin sa nu fie vizitat, acesta
// sa aiba si o greutate admisa mai mare sau egala cu greutatea transmisa ca parametru la apelare.



#include <bits/stdc++.h>
using namespace std;

ifstream fin("transport2.in");
ofstream fout("transport2.out");

vector <pair <int, int >> *adjList;
int n, m, maxWeight = INT_MIN;



bool bfs (int currentMaxWeight) {
    vector <bool> visited(n + 1, false);
    queue <int> q;

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto &neighbor : adjList[node]) {
            if (!visited[neighbor.first] && neighbor.second >= currentMaxWeight) {
                if (neighbor.first == n) {
                    return true;
                }

                visited[neighbor.first] = true;
                q.push(neighbor.first);
            }
        }
    }

    return false;
}



int main()
{
    fin >> n >> m;
    adjList = new vector <pair <int, int>> [n + 1];

    for (int i = 1; i <= m; i++) {
        int x, y, weight;
        fin >> x >> y >> weight;
        adjList[x].emplace_back(make_pair(y, weight));
        adjList[y].emplace_back(make_pair(x, weight));
        maxWeight = max(maxWeight, weight);
    }

    int left = 0, right = maxWeight, mid, ans;
    while (left <= right) {
        mid = (left + right) / 2;
        if (bfs(mid)) {
            ans = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    fout << ans;

    fin.close();
    fout.close();
    return 0;
}