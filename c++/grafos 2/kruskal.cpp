// MST: conecta todos com menor soma; N-1 arestas. Não é shortest path.
// KRUSKAL = sort + DSU (compressão + tamanho); pula ciclos.
// O(E log E + E*alpha(V) + V) tempo, O(V+E) memória.
// Entrada: n m; m arestas u v w, NÃO direcionadas, 1-based.
// Saída: custo ou IMPOSSIVEL se desconectado. Aceita pesos negativos.
// Toda soma parcial do custo precisa caber em long long.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> pai, sz;

    DSU(int n) {
        pai.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            pai[i] = i;
        }
    }

    int find(int u) {
        if (pai[u] == u) {
            return u;
        }
        pai[u] = find(pai[u]);
        return pai[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return false;
        }
        if (sz[u] < sz[v]) {
            swap(u, v);
        }
        pai[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<tuple<ll, int, int>> edges; // {peso,u,v}
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w; // mantém 1-based, como DSU no slide
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll cost = 0;
    int used = 0;
    for (auto [w, u, v] : edges) {
        if (!dsu.join(u, v)) continue; // fecharia ciclo
        cost += w;
        if (++used == n - 1) break;
    }
    if (used != n - 1) {
        cout << "IMPOSSIVEL\n";
    } else {
        cout << cost << '\n';
    }
}
