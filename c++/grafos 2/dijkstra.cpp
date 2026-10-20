// DIJKSTRA: menor caminho de uma origem; pesos >= 0. Não aceita negativos.
// O(V + E log(E+1)) tempo, O(V+E) memória.
// Como no slide: priority_queue padrão + distância negativa simula min-heap.
// Entrada: n m s; m arestas u v w, direcionadas; vértices 1-based.
// Saída: distâncias ou INF. Peso e distâncias finitas < INF.
// Negativos: bellman_ford.cpp. Todos os pares, N pequeno: floyd_warshall.cpp.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // direcionado
        // adj[v].push_back({u, w}); // não direcionado
    }
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>> pq; // {-distância, vértice}
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [total, cur] = pq.top();
        pq.pop();
        total = -total; // volta à distância real

        if (dist[cur] < total) {
            continue; // já encontramos um caminho melhor
        }

        for (auto [viz, custo] : adj[cur]) {
            if (dist[viz] > total + custo) {
                dist[viz] = total + custo;
                pq.push({-dist[viz], viz});
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        if (dist[u] == INF) {
            cout << "INF ";
        } else {
            cout << dist[u] << ' ';
        }
    }
    cout << '\n';
}
