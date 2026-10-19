// Ciclo em grafo não direcionado; aceita self-loops e arestas paralelas.
// O(V + E) tempo/memória; pilha explícita para grafos profundos.
// Entrada: n m; m arestas u v, 1-based. Saída: SIM / NAO.
// Pula ID da aresta do pai, não o vértice: paralelas formam ciclo.
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj; // {vizinho, id da aresta}
vector<bool> vis;

bool has_cycle(int start) {
    stack<pair<int, int>> pending; // {vértice,aresta do pai}
    pending.push({start, -1});
    vis[start] = true;

    while (!pending.empty()) {
        auto [u, parent_edge] = pending.top();
        pending.pop();

        for (auto [v, id] : adj[u]) {
            if (id == parent_edge) continue;
            if (vis[v]) return true;
            vis[v] = true;
            pending.push({v, id});
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    for (int u = 0; u < n; u++) {
        if (!vis[u] && has_cycle(u)) {
            cout << "SIM\n";
            return 0;
        }
    }
    cout << "NAO\n";
}
