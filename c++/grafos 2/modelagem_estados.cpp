// ESTADOS: mesmo vértice, situações diferentes -> dist[v][estado].
// Como no slide: ATÉ 10 cupons de 50% (custo/2, piso); um por travessia.
// (cur,cupons)->(viz,cupons): custo; usar cupom leva a cupons+1.
// K cupons = K+1 camadas (inclui zero). Aqui, K=10; altere MAX_CUPONS.
// V'=(K+1)V, E'=O((K+1)E); Dijkstra O(V'+E' log(E'+1)), memória O(V'+E').
// Entrada: n m s t; m arestas u v w, direcionadas, 1-based; w >= 0.
// Saída: menor custo ou INF. Pesos/distâncias finitas < INF.
// Outros estados: combustível, obstáculos, máscara de chaves, dia/noite.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;
constexpr int MAX_CUPONS = 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<vector<ll>> dist(n + 1, vector<ll>(MAX_CUPONS + 1, INF));
    priority_queue<tuple<ll, int, int>> pq; // {-distância,vértice,cupons usados}
    dist[s][0] = 0;
    pq.push({0, s, 0});
    while (!pq.empty()) {
        auto [total, cur, cupons] = pq.top();
        pq.pop();
        total = -total;

        if (total > dist[cur][cupons]) {
            continue;
        }

        for (auto [viz, custo] : adj[cur]) {
            // Sem cupom: permanece na mesma camada.
            if (dist[viz][cupons] > total + custo) {
                dist[viz][cupons] = total + custo;
                pq.push({-dist[viz][cupons], viz, cupons});
            }

            // Com cupom: avança uma camada.
            if (cupons < MAX_CUPONS && dist[viz][cupons + 1] > total + custo / 2) {
                dist[viz][cupons + 1] = total + custo / 2;
                pq.push({-dist[viz][cupons + 1], viz, cupons + 1});
            }
        }
    }

    ll resp = INF;
    for (int cupons = 0; cupons <= MAX_CUPONS; cupons++) {
        resp = min(resp, dist[t][cupons]); // ATÉ K: melhor entre as camadas
    }
    // Exatamente K cupons: use somente dist[t][MAX_CUPONS].
    if (resp == INF) {
        cout << "INF\n";
    } else {
        cout << resp << '\n';
    }
}
