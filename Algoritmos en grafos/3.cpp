#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Enlace {
    int a;
    int b;
    int d;
    int r;

    Enlace(int a, int b, int d, int r) {
        this->a=a;
        this->b=b;
        this->d=d;
        this->r=r;
    }

};

struct DSU {
    vector<int> padre;
    vector<int> rank;

    DSU(int n) {
        padre = vector<int>(n);
        rank = vector<int>(n, 0);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v) {
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }
};

bool sortPorPrim(const pair<double, Enlace>& a, const pair<double, Enlace>& b) {
    return (a.first < b.first);
}

double power(double base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    } else if (exponent < 0) {
        return 1.0 / power(base, -exponent);
    } else {
        return base * power(base, exponent - 1);
    }
}

pair<double, pair<double, double>> kruskal(vector<pair<double, Enlace>>& E, int n) {
    sort(E.begin(), E.end(), sortPorPrim);

    double suma = 0;
    double suma_d = 0;
    double suma_r = 0;

    DSU dsu(n);

    for (int i = 0; i < E.size(); i++) {
        int u = (E[i]).second.a;
        int v = (E[i]).second.b;
        int r = (E[i]).second.r;
        int d = (E[i]).second.d;

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            suma += (E[i]).first;
            suma_d+=d;
            suma_r+=r;
        }
    }

    return make_pair(suma, make_pair(suma_d, suma_r));
}

int main() {
    int tests;
    cin >> tests;

    for(int t = 1; t <= tests; t++) {
        int n,m;
        cin >> n;
        cin >> m;

        vector<Enlace> conexiones(m, Enlace(0,0,0,0));

        for(int i = 0; i < m; i++) {
            int u, v, d, r;
            cin >> u;
            cin >> v;
            cin >> d;
            cin >> r;

            conexiones[i] = Enlace(u-1, v-1, d, r);
        }

        int suma_d = 0;
        int suma_r = 0;

        double min = 0;
        double max = power(10,6)+1;

        double C = (max + min) / 2;

        double tol = 1/((n-1)*power(10,6));

        while(max-min >= tol) {
            vector<pair<double, Enlace>> enlaces(conexiones.size(), make_pair(0, Enlace(0,0,0,0)));

            for(int i = 0; i < conexiones.size(); i++) {
                Enlace e = conexiones[i];
                enlaces[i] = make_pair(C*e.r-e.d, e);
            }

            pair<double, pair<double, double>> agmin = kruskal(enlaces, n);

            double costo = agmin.first;

            if (costo <= 0) {
                suma_d = agmin.second.first;
                suma_r = agmin.second.second;

                min = C;
            } else {
                max = C;
            }

            C = (max + min) / 2;
        }

        cout << suma_d << " " << suma_r << endl;
    }

    return 0;
}