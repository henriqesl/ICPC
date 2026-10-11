// Várias origens simultâneas; menor distância até qualquer source.
// O(V + E + K) tempo/memória; sem peso.
// Entrada: n m; m arestas u v; k; k fontes. Vértices 1-based.
// Saída: distâncias; -1 se inalcançável. Não direcionado.
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
    int k;
    cin >> k;
    vector<int> sources(k);
    for (int &source : sources) {
        cin >> source;
        --source;
    }

    vector<int> dist(n, -1);
    queue<int> q;
    for (int source : sources) {
        if (dist[source] != -1) continue; // fonte repetida
        dist[source] = 0;
        q.push(source);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    for (int d : dist) cout << d << ' ';
    cout << '\n';
}
