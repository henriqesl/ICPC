// LISTA DE ADJACÊNCIA: copie só a representação necessária.
// O(V + E) tempo/memória; vértices 1-based -> 0-based.
// Demo: n m; m linhas u v w (peso int). Só constrói, sem saída.
// Problema sem peso: leia apenas u v e retire weighted.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n), directed(n);
    vector<vector<pair<int, int>>> weighted(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;

        adj[u].push_back(v); // sem peso, não direcionado
        adj[v].push_back(u);

        directed[u].push_back(v); // sem peso, direcionado: só u -> v

        weighted[u].push_back({v, w}); // {vizinho, peso}, direcionado
        // weighted[v].push_back({u, w}); // acrescente para não direcionado
    }
}
