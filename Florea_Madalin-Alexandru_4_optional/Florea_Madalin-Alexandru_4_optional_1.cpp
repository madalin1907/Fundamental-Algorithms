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