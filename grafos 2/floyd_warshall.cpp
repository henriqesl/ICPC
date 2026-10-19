// FLOYD-WARSHALL: todos os pares; N ~ 500 + muitas queries.
// O(V^3+E+Q) tempo, O(V^2) memória; consulta O(1).
// Entrada: n m q; m arestas u v w; q pares u v. Direcionado, 1-based.
// Saída: distância ou INF. Aceita negativos, SEM ciclos negativos.
// Diagonal 0; arestas repetidas: min; loops k,i,j.
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
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (int e = 0; e < m; e++) {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        dist[u][v] = min(dist[u][v], w);
        // dist[v][u] = min(dist[v][u], w); // não direcionado
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    while (q--) {
        int u, v;
        cin >> u >> v; --u; --v;
        if (dist[u][v] == INF) cout << "INF\n";
        else cout << dist[u][v] << '\n';
    }
}
