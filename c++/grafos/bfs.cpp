// BFS: menor distância sem peso; dist == -1: não alcançado.
// O(V + E) tempo/memória. Não serve para pesos diferentes.
// Entrada: n m (n >= 1); m arestas u v; start. Vértices 1-based.
// Saída: distâncias de start; não direcionado (retire a volta para directed).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start;
    cin >> start;
    --start;

    queue<int> q;
    vector<int> dist(n, -1);
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1; // marca ao enfileirar
            q.push(v);
        }
    }
    for (int d : dist) cout << d << ' ';
    cout << '\n';
}
