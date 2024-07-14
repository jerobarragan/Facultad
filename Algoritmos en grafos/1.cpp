#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> ady(0);
vector<int> visitado(0);
vector<int> nivel(0);
vector<int> minNiv(0);
bool puentes;
int x, y;

void dfs(int v, int p, int a) {
    if(puentes) return;

    visitado[v] = 1;
    minNiv[v] = a;
    nivel[v] = a;

    for(int h : ady[v]) {
        if(h != p && (!((v == x && h == y) || (v == y && h == x)))) {
            if(visitado[h] == 1) {
                minNiv[v] = min(nivel[h], minNiv[v]);
            } else {
                dfs(h, v, a+1);
                minNiv[v] = min(minNiv[h], minNiv[v]);
                if(minNiv[h] > nivel[v]) {
                    puentes = true;
                }
            }
        }
    }
}

int main() {
    int tests;
    cin >> tests;

    for(int t = 1; t <= tests; t++) {
        int n, m;

        cin >> n;
        cin >> m;

        ady = vector<vector<int>>(n);

        vector<pair<int, int>> aristas;

        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u;
            cin >> v;

            ady[u].push_back(v);
            ady[v].push_back(u);

            aristas.push_back(u < v ? make_pair(u, v) : make_pair(v, u));
        }

        vector<pair<int, int>> res(0);

        for(int i = 0; i < aristas.size(); i++) {
            x = aristas[i].first;
            y = aristas[i].second;

            visitado = vector<int>(n, 0);
            nivel = vector<int>(n, -1);
            minNiv = vector<int>(n, -1);
            puentes = false;

            dfs(0, -1, 0);

            if(puentes) {
                res.push_back(aristas[i]);
            }

            puentes = false;
        }

        sort(res.begin(), res.end());

        cout << res.size() << endl;
        for(pair<int, int> a : res) {
            cout << a.first << " " << a.second << endl;
        }

    }

    return 0;
}
