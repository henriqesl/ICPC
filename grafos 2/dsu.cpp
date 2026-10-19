// DSU: unir componentes / testar conectividade; somente adições.
// Find com path compression; união por tamanho: O(alpha(V)) amortizado.
// Inicialização/memória O(V). Não remove arestas nem calcula distâncias.
// Entrada: n q; q comandos tipo u v (1-based): 1=unite, 2=same.
// Saída: SIM/NAO nas consultas. Unite retorna false se fecharia ciclo.
#include <bits/stdc++.h>
using namespace std;

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
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int type, u, v;
        cin >> type >> u >> v; --u; --v;
        if (type == 1) dsu.unite(u, v);
        else cout << (dsu.same(u, v) ? "SIM" : "NAO") << '\n';
    }
}
