#include <iostream>
#include <list>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

class Arista {
public:
    Arista(int u, int v) {
        this->u = u;
        this->v = v;
    }
    int desde();
    int hasta();

private:
    int u;
    int v;
};

int Arista::desde() {
    return u;
}

int Arista::hasta() {
    return v;
}

vector<vector<int>> capacity;

int bfs(int s, int t, vector<int>& parent, vector<list<Arista>>& ady) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (Arista a : ady[cur]) {
            int next = a.hasta();
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(vector<list<Arista>>& ady, int n, int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, ady)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    int tests;
    cin >> tests;

    for(int i = 1; i <= tests; i++) {
        int tam;
        cin >> tam;

        vector<vector<int>> tablero(tam, vector<int>(tam));
        vector<list<tuple<int, int, int>>> filas(tam, list<tuple<int, int, int>>());
        vector<list<tuple<int, int, int>>> columnas(tam, list<tuple<int, int, int>>());

        for(int j = 0; j < tam; j++) {
            for(int k = 0; k < tam; k++) {
                int valor;
                cin >> valor;

                tablero[j][k] = valor;
            }
        }
        //arista 0: fuente
        //arista 1: sumidero
        int nodosTotales = 2;

        for(int j = 0; j < tam; j++) {
            bool rojito = true;

            int inicio = -1;
            int fin = 0;

            while (fin < tam) {
                if (fin == tam - 1 && tablero[j][fin] == 0) {
                    filas[j].push_back(make_tuple(inicio == -1 ? fin : inicio, fin, nodosTotales));
                    nodosTotales++;
                    fin++;
                } else {
                    if (tablero[j][fin] == 1) {
                        rojito = true;
                        if (inicio > -1) {
                            filas[j].push_back(make_tuple(inicio, fin-1, nodosTotales));
                            nodosTotales++;
                            inicio = fin+1;
                        }
                    } else {
                        if (rojito) {
                            rojito = false;
                            inicio = fin;
                        }
                    }
                    fin++;
                }
            }

            rojito = true;
            inicio = -1;
            fin = 0;

            while (fin < tam) {
                if (fin == tam - 1 && tablero[fin][j] == 0) {
                    columnas[j].push_back(make_tuple(inicio == -1 ? fin : inicio, fin, nodosTotales));
                    nodosTotales++;
                    fin++;
                } else {
                    if (tablero[fin][j] == 1) {
                        rojito = true;
                        if (inicio > -1) {
                            columnas[j].push_back(make_tuple(inicio, fin-1, nodosTotales));
                            nodosTotales++;
                            inicio = fin+1;
                        }
                    } else {
                        if (rojito) {
                            rojito = false;
                            inicio = fin;
                        }
                    }
                    fin++;
                }
            }
        }

        capacity = vector<vector<int>>(nodosTotales, vector<int>(nodosTotales, 0));
        vector<list<Arista>> ady(nodosTotales, list<Arista>());

        for(int j = 0; j < tam; j++) {
            for(tuple<int, int, int> fila : filas[j]) {
                int desde = get<0>(fila);
                int hasta = get<1>(fila);
                int nodo = get<2>(fila);
                ady[0].push_back(Arista(0, nodo));
                capacity[0][nodo] = 1;
                ady[nodo].push_back(Arista(nodo, 0));
                capacity[nodo][0] = 0;
                for(int k = desde; k <= hasta; k++) {
                    for(tuple<int, int, int> columna : columnas[k]) {
                        if(get<0>(columna) <= j && get<1>(columna) >= j) {
                            //encontre dos fragmentos que tengo que unir en el grafo
                            ady[nodo].push_back(Arista(nodo, get<2>(columna)));
                            capacity[nodo][get<2>(columna)] = 1;
                            ady[get<2>(columna)].push_back(Arista(get<2>(columna), nodo));
                            capacity[get<2>(columna)][nodo] = 0;
                        }
                    }
                }
            }
        }

        for(int j = 0; j < tam; j++) {
            for(tuple<int, int, int> columna : columnas[j]) {
                ady[get<2>(columna)].push_back(Arista(get<2>(columna), 1));
                capacity[get<2>(columna)][1] = 1;
                ady[1].push_back(Arista(1, get<2>(columna)));
                capacity[1][get<2>(columna)] = 0;
            }
        }

        int flow = maxflow(ady, nodosTotales+1, 0, 1);

        cout << flow << endl;
    }

    return 0;
}
