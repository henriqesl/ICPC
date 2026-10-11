// Ciclo em grafo não direcionado; aceita self-loops e arestas paralelas.
// O(V + E) tempo/memória. Recursão profunda pode estourar a pilha.
// Entrada: n m; m arestas u v, 1-based. Saída: SIM / NAO.
// Pula ID da aresta do pai, não o vértice: paralelas formam ciclo.
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj; // {vizinho, id da aresta}
vector<bool> vis;

bool dfs(int u, int parent_edge) {
    vis[u] = true;
    for (auto [v, id] : adj[u]) {
        if (id == parent_edge) continue;
        if (vis[v]) return true;
        if (dfs(v, id)) return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    for (int u = 0; u < n; u++) {
        if (!vis[u] && dfs(u, -1)) {
            cout << "SIM\n";
            return 0;
        }
    }
    cout << "NAO\n";
}
