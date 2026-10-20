// BELLMAN-FORD: uma origem; aceita pesos negativos.
// O(V+VE) tempo, O(V+E) memória; N-1 passagens + teste extra.
// Entrada: n m s; m arestas u v w, direcionadas, 1-based.
// Saída: distâncias/INF ou CICLO NEGATIVO alcançável da origem.
// Limite suficiente: V*E*max|w| < INF; nunca some INF.
// Ciclo alcançável só afeta destinos alcançáveis a partir dele.
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
    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        edges.push_back({u, v, w}); // direcionado
    }
    vector<ll> dist(n, INF);
    dist[s] = 0;
    for (int rep = 0; rep < n - 1; rep++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) {
                continue; // não propague de um vértice inalcançável
            }
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    bool cicloNegativo = false;
    for (auto [u, v, w] : edges) { // iteração extra
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cicloNegativo = true;
        }
    }

    if (cicloNegativo) {
        cout << "CICLO NEGATIVO\n";
        return 0;
    }

    for (ll d : dist) {
        if (d == INF) {
            cout << "INF ";
        } else {
            cout << d << ' ';
        }
    }
    cout << '\n';
}
