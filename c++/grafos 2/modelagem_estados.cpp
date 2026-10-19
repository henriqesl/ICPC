// ESTADOS: mesmo vértice, situações diferentes -> dist[v][estado].
// Exemplo: caminho mínimo com ATÉ um cupom de 50% (w/2, piso).
// (u,usado)->(v,usado): custo w; (u,0)->(v,1): custo w/2.
// Dijkstra: O(V + E log(E+1)) tempo, O(V+E) memória, para 2 camadas.
// Entrada: n m s t; m arestas u v w, direcionadas, 1-based; w >= 0.
// Saída: menor custo ou INF. Pesos/distâncias finitas < INF.
// Outros estados: combustível, obstáculos, máscara de chaves, dia/noite.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s;
    --t;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        adj[u].push_back({v, w});
    }

    vector<array<ll, 2>> dist(n, {INF, INF});
    using State = tuple<ll, int, int>; // {distância,vértice,usado}
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[s][0] = 0;
    pq.push({0, s, 0});
    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d != dist[u][used]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][used]) {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }
            if (!used && d + w / 2 < dist[v][1]) {
                dist[v][1] = d + w / 2;
                pq.push({dist[v][1], v, 1});
            }
        }
    }
    ll answer = min(dist[t][0], dist[t][1]); // obrigatório: só dist[t][1]
    if (answer == INF) cout << "INF\n";
    else cout << answer << '\n';
}
