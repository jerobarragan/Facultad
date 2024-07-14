#include <iostream>
#include <list>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

class Arista {
public:
    Arista(int u, int v, bool original, int c) {
        this->u = u;
        this->v = v;
        this->original = original;
        this->c = c;
        this->tope = 1;
    }
    int desde();
    int hasta();
    bool estaEnLaRed();
    int capacidad();
    void setTope(int t);
    int personas();
    
private:
    int u;
    int v;
    bool original;
    int c;
    int tope;
};

int Arista::desde() {
    return u;
}

int Arista::hasta() {
    return v;
}

bool Arista::estaEnLaRed() {
    return original;
}

int Arista::capacidad() {
    return c;
}

void Arista::setTope(int t) {
    tope = t;
}

int Arista::personas() {
    return c/tope;
}

vector<vector<int>> capacity;
vector<list<Arista>> ady;

double power(double base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    } else if (exponent < 0) {
        return 1.0 / power(base, -exponent);
    } else {
        return base * power(base, exponent - 1);
    }
}

int bfs(int s, int t, vector<int>& parent) {
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

int maxflow(int n, int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
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
        int n;
        int m;
        int x;
        cin >> n;
        cin >> m;
        cin >> x;

        ady = vector<list<Arista>>(n, list<Arista>());
        capacity = vector<vector<int>>(n, vector<int>(n, 0));

        int maxC = 0;

        for(int j = 1; j <= m; j++) {
            int u;
            int v;
            int c;
            cin >> u;
            cin >> v;
            cin >> c;
            u--;
            v--;
            if(maxC < c) maxC = c;
            ady[u].push_back(Arista(u, v, true, c));
        }

        for(int j = 0; j < ady.size(); j++) {
            for(Arista a : ady[j]) {
                bool vuelve = false;
                for(Arista b : ady[a.hasta()]) {
                    if(b.hasta() == a.desde() && b.estaEnLaRed()) {
                        vuelve = true;
                        break;
                    }
                }
                if(!vuelve) {
                    ady[j].push_back(Arista(a.hasta(), a.desde(), false, 0));
                }
            }
        }

        int min = 0;
        int max = maxC+1;

        int f = 0;

        int M = (min+max)/2;
        while(min+1!=max) {
            for(int j = 0; j < ady.size(); j++) {
                for(Arista a : ady[j]) {
                    a.setTope(M);
                    capacity[a.desde()][a.hasta()] = (a.estaEnLaRed()) ? a.personas() : 0;
                }
            }

            f = maxflow(n, 0, n-1);

            if(f >= x) {
                min = M;
            } else {
                max = M;
            }

            M = (min+max) / 2;
        }

        cout << min*x << endl;
    }

    return 0;
}