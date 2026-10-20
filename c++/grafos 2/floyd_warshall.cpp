// FLOYD-WARSHALL: todos os pares; N ~ 500 + muitas queries.
// O(V^3+E+Q) tempo, O(V^2) memória; consulta O(1).
// Entrada: n m q; m arestas u v w; q pares u v. Direcionado, 1-based.
// Saída: distância ou INF. Aceita negativos, SEM ciclos negativos.
// Diagonal 0; arestas repetidas: min; loops k,u,v (intermediário primeiro).
// N*max|w| < INF; nunca some INF. dist[k][k] < 0 indica ciclo negativo.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    for (int e = 0; e < m; e++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        // dist[v][u] = min(dist[v][u], w); // não direcionado
    }
    // k é o intermediário; mantenha este loop por fora.
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                if (dist[u][k] == INF || dist[k][v] == INF) {
                    continue; // não some uma distância inexistente
                }
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (dist[u][v] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[u][v] << '\n';
        }
    }
}
