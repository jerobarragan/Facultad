#include <iostream>
#include <list>
#include <queue>

using namespace std;

vector<int> bfs(vector<list<pair<int,int>>>& ady, int desde) {
    vector<int> visitado(ady.size(), 0);
    vector<int> dists(ady.size(), -1);
    visitado[desde] = 1;
    dists[desde] = 0;
    queue<int> cola;
    cola.push(desde);
    while(!cola.empty()) {
        int u = cola.front();
        for(pair<int,int> v : ady[u]) {
            if(visitado[v.first] == 0) {
                visitado[v.first] = 1;
                dists[v.first] = dists[u] + 1;
                cola.push(v.first);
            }
        }
        cola.pop();
    }
    return dists;
}

int main() {
    int tests;
    cin >> tests;

    for(int i = 1; i <= tests; i++) {
        int n;
        cin >> n;

        vector<vector<int>> latencias(n, vector<int>(n, 0));

        for(int j = 1; j <= n-1; j++) {
            for(int k = 0; k < j; k++) {
                int val;
                cin >> val;
                latencias[j][k] = val;
                latencias[k][j] = val;
            }
        }

        vector<list<pair<int, int>>> ady(n, list<pair<int,int>>());

        bool posible = true;

        for(int j = 0; j < n; j++) {
            for(int k = 0; k < j; k++) {
                bool agrego_eje = true;

                for(int l = 0; l < n; l++) {
                    if(l != j && l != k) {
                        agrego_eje = agrego_eje && (latencias[j][k] < latencias[j][l] + latencias[l][k]);
                        if(latencias[j][k] > latencias[j][l] + latencias[l][k]) {
                            posible = false;
                        }
                    }
                }

                if(agrego_eje) {
                    ady[j].push_back(make_pair(k, latencias[j][k]));
                    ady[k].push_back(make_pair(j, latencias[k][j]));
                }
            }
        }

        cout << (posible ? "POSIBLE" : "IMPOSIBLE") << endl;

        if(posible) {
            for(int j = 0; j < n; j++) {
                vector<int> dists = bfs(ady, j);
                for(int k = 0; k < dists.size(); k++) {
                    cout << dists[k] << " ";
                }
                cout << endl;
            }
        }

    }

    return 0;
}
