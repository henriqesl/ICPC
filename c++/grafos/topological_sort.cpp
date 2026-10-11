// Kahn: dependências em DAG (grafo direcionado sem ciclo).
// O(V + E) tempo/memória; indegree 0 entra na fila.
// Entrada: n m; m arestas u v, 1-based (u antes de v).
// Saída: uma ordem válida, 1-based; IMPOSSIVEL se houver ciclo.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v); // apenas u -> v
        indegree[v]++;
    }

    queue<int> q;
    for (int u = 0; u < n; u++) {
        if (indegree[u] == 0) q.push(u);
    }
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }

    if (int(order.size()) != n) cout << "IMPOSSIVEL\n";
    else {
        for (int u : order) cout << u + 1 << ' ';
        cout << '\n';
    }
}
