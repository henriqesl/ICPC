// DFS: componentes / alcance; não calcula menor distância.
// O(V + E) tempo/memória; pilha explícita para grafos profundos.
// Entrada: n m; m arestas u v, 1-based, não direcionadas.
// Saída: número de componentes (inclui isolados).
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

void dfs(int u) {
    stack<int> pending;
    vis[u] = true;
    pending.push(u);

    while (!pending.empty()) {
        u = pending.top();
        pending.pop();

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                pending.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
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
