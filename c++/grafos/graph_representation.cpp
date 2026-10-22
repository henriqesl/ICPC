// LISTA DE ADJACÊNCIA: copie só a representação necessária.
// O(V + E) tempo/memória; vértices 1-based -> 0-based.
// Demo: n m; m linhas u v w (peso long long). Só constrói, sem saída.
// Problema sem peso: leia apenas u v e retire weighted.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n), directed(n);
    vector<vector<pair<int, long long>>> weighted(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
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

/*
COMO LER ESTE CÓDIGO
1. Cada posição do vetor externo representa um vértice; o vetor interno
   contém seus vizinhos. push_back acrescenta uma ligação nessa lista.
2. adj guarda ida e volta, pois o grafo é não direcionado.
   directed guarda só u->v: ter essa aresta não permite voltar de v para u.
3. weighted guarda pares {vizinho, peso}; auto [v,w] pode separar o par.
4. --u e --v transformam rótulos 1..n em índices 0..n-1.
Exemplo: entrada 1 2 7 cria weighted[0] com o par {1,7}.
O exemplo constrói três representações, sem imprimir; copie só a necessária.
*/
