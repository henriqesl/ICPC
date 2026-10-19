// DIJKSTRA: menor caminho de uma origem; pesos >= 0. Não aceita negativos.
// O(V + E log(E+1)) tempo, O(V+E) memória; min-heap.
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
    --s;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        adj[u].push_back({v, w}); // direcionado
        // adj[v].push_back({u, w}); // não direcionado
    }
    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue; // entrada antiga
        for (auto [v, w] : adj[u]) {
            ll nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    for (ll d : dist) {
        if (d == INF) cout << "INF ";
        else cout << d << ' ';
    }
    cout << '\n';
}
