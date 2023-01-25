// a)
// Se salveaza listele de adiacenta si gradul intern al fiecarui nod. Folosind algoritmul
// de sortare topologica, se adauga in coada nodurile care au gradul intern 0 si se repeta
// procedeul urmator: se extrage un nod din coada, se scad gradele interne ale vecinilor
// sai si se adauga in coada nodurile care raman cu gradul intern 0.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii


#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        list <int> *listaAdiacenta = new list <int> [numCourses];
        vector <int> grad (numCourses);
        vector <int> sortareTopologica;
        queue <int> coada;

        for (auto &arc : prerequisites) {
            listaAdiacenta[arc[1]].push_back(arc[0]);
            grad[arc[0]] += 1;
        }


        for (int i = 0; i < numCourses; ++i)
            if (!grad[i])
                coada.push(i);

        if (coada.empty())
            return {};

        while (!coada.empty()) {
            int nod = coada.front();
            coada.pop();
            sortareTopologica.push_back(nod);

            for (auto &vecin : listaAdiacenta[nod]) {
                --grad[vecin];
                if (!grad[vecin])
                    coada.push(vecin);
            }
        }

        if (sortareTopologica.size() == numCourses)
            return sortareTopologica;
        return {};
    }
};





// b)
// Se foloseste algoritmul de la punctul a), iar in cazul in care nu este gasita o sortare
// topologica, inseamana ca graful contine cel putin un ciclu care va fi cautat folosind
// parcurgerea DFS pana in momentul in care se gaseste un nod deja vizitat. Cand acesta a
// fost gasit, se adauga nodurile parcurse pana la nodul respectiv (ajutandu-ne de un vector
// de parinti) intr-un vector care la final va fi rasturnat, obtinand solutia.

// Complexitate: O(n + m), unde n = nr. noduri, m = nr. muchii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector < int > sortareTopologica(int &numCourses, list <int> *listaAdiacenta, vector <int> grad) {
        queue <int> coada;
        vector <int> sortareTopologica;

        for (int i = 0; i < numCourses; ++i)
            if (!grad[i])
                coada.push(i);

        if (coada.empty())
            return {};

        while (!coada.empty()) {
            int nod = coada.front();
            coada.pop();
            sortareTopologica.push_back(nod);

            for (auto &vecin : listaAdiacenta[nod]) {
                --grad[vecin];
                if (!grad[vecin])
                    coada.push(vecin);
            }
        }

        if (sortareTopologica.size() == numCourses)
            return sortareTopologica;
        return {};
    }


    void cautareCircuitDFS (int nod, list <int> *listaAdiacenta, vector <bool> &vizitat, vector <bool> &final, vector <int> &parinte, vector <int> &circuit) {
        vizitat[nod] = true;
        for (auto &vecin : listaAdiacenta[nod]) {
            if (!vizitat[vecin]) {
                parinte[vecin] = nod;
                cautareCircuitDFS(vecin, listaAdiacenta, vizitat, final, parinte, circuit);
            }
            else {
                if (!final[vecin]) {
                    while (nod != vecin) {
                        circuit.push_back(nod);
                        nod = parinte[nod];
                    }

                    circuit.push_back(vecin);
                    reverse(circuit.begin(), circuit.end());
                    return;
                }
            }
        }
    }


    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        list <int> *listaAdiacenta = new list <int> [numCourses];
        vector <int> grad (numCourses);

        for (auto &arc : prerequisites) {
            listaAdiacenta[arc[1]].push_back(arc[0]);
            grad[arc[0]] += 1;
        }

        if (sortareTopologica(numCourses, listaAdiacenta, grad).empty()) {
            vector <bool> vizitat(numCourses, 0);
            vector <bool> final(numCourses, 0);
            vector <int> parinte(numCourses, 0);
            vector <int> circuit;

            cautareCircuitDFS(1, listaAdiacenta, vizitat, final, parinte, circuit);
            return circuit;
        }

        return {};
    }
};