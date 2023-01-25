// Se parcurge matricea, iar pentru fiecare element nenul si nevizitat se va calcula
// aria insulei din care face parte astfel: se adauga elementul in stiva, apoi cat timp
// aceasta va fi nevida, pentru fiecare element se va incrementa aria si se vor adauga
// vecinii acestuia (sus, jos, stanga, dreapta) pe stiva, daca sunt nenuli si nevizitati.

// Complexitate: O(n * m), unde n si m sunt dimensiunile matricei

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector <vector <int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector <vector <int>> visited(n, vector <int>(m));

        vector <vector <int>> adjacents ({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});

        int maxArea = 0;

        for (int row = 0; row < n; ++row) {
            for (int column = 0; column < m; ++column) {
                if (grid[row][column] && !visited[row][column]) {
                    stack <vector <int>> stack;
                    int area = 0;

                    stack.push({row, column});
                    visited[row][column] = 1;

                    while (!stack.empty()) {
                        ++area;

                        vector <int> node = stack.top();
                        stack.pop();

                        for (auto const &adj : adjacents) {
                            int r = node[0] + adj[0];
                            int c = node[1] + adj[1];

                            if (r >= 0 && r < n && c >= 0 && c < m)
                                if (grid[r][c] && !visited[r][c]) {
                                    stack.push({r, c});
                                    visited[r][c] = 1;
                                }
                        }
                    }

                    maxArea = max(maxArea, area);
                }
            }
        }

        return maxArea;
    }
};