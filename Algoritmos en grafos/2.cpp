#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

pair<int, bool> bfs(vector<list<int>>& ady, vector<int>& tiempos, int t0, int desde, int hasta) {
    if(desde == hasta) return make_pair(0, true);
    vector<int> visitado(ady.size(), 0);
    vector<int> tiempo(ady.size(), -1);
    visitado[desde] = 1;
    tiempo[desde] = t0;
    queue<int> cola;
    cola.push(desde);
    bool camino = false;
    while(!cola.empty() && !camino) {
        int u = cola.front();
        for(int v : ady[u]) {
            if(visitado[v] == 0 && (tiempos[v] == 0 || tiempos[v] > tiempo[u]+1)) {
                visitado[v] = 1;
                tiempo[v] = tiempo[u]+1;
                cola.push(v);
                if(v == hasta) {
                    camino = true;
                }
            }
        }
        cola.pop();
    }
    return make_pair(tiempo[hasta], camino);
}

int main() {
    int tests;
    cin >> tests;

    for(int t = 1; t <= tests; t++) {
        int n, m;

        cin >> n;
        cin >> m;

        vector<list<int>> ady(n*m, list<int>());
        vector<int> tiempos(n*m, 0);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int tij;
                cin >> tij;
                tiempos[m*i+j] = tij;

                if(0 <= m*i+j-m && m*i+j-m < n*m) {
                    ady[m*i+j].push_back(m*i+j-m);
                }

                if(0 <= m*i+j+m && m*i+j+m < n*m) {
                    ady[m*i+j].push_back(m*i+j+m);
                }

                if(0 <= m*i+j-1 && m*i+j-1 < n*m && j > 0) {
                    ady[m*i+j].push_back(m*i+j-1);
                }

                if(0 <= m*i+j+1 && m*i+j+1 < n*m && j < m-1) {
                    ady[m*i+j].push_back(m*i+j+1);
                }

            }
        }

        int x1, y1, x2, y2;

        cin >> x1;
        cin >> y1;
        cin >> x2;
        cin >> y2;

        pair<int, bool> ida = bfs(ady, tiempos, 0, x1*m+y1, x2*m+y2);
        pair<int, bool> vuelta = bfs(ady, tiempos, ida.first, x2*m+y2, x1*m+y1);

        if(ida.second && vuelta.second) {
            cout << ida.first << " " << vuelta.first << endl;
        } else {
            cout << "IMPOSIBLE" << endl;
        }

    }

    return 0;
}