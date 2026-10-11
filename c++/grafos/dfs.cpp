// DFS: componentes / alcance; não calcula menor distância.
// O(V + E) tempo/memória. Recursão profunda pode estourar a pilha.
// Entrada: n m; m arestas u v, 1-based, não direcionadas.
// Saída: número de componentes (inclui isolados).
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            components++;
        }
    }
    cout << components << '\n';
}
