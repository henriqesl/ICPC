// MST: conecta todos com menor soma; N-1 arestas. Não é shortest path.
// KRUSKAL = sort das arestas + DSU; pula arestas que fechariam ciclo.
// O(E log E + E*alpha(V) + V) tempo, O(V+E) memória.
// Entrada: n m; m arestas u v w, NÃO direcionadas, 1-based.
// Saída: custo ou IMPOSSIVEL se desconectado. Aceita pesos negativos.
// Toda soma parcial do custo precisa caber em long long.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent, sz;
    explicit DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    bool same(int u, int v) { return find(u) == find(v); }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
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
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll cost = 0;
    int used = 0;
    for (auto [w, u, v] : edges) {
        if (!dsu.unite(u, v)) continue; // fecharia ciclo
        cost += w;
        if (++used == n - 1) break;
    }
    if (used != n - 1) cout << "IMPOSSIVEL\n";
    else cout << cost << '\n';
}
