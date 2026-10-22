// Ciclo em grafo não direcionado; aceita self-loops e arestas paralelas.
// O(V + E) tempo/memória. Recursão profunda pode estourar a pilha.
// Entrada: n m; m arestas u v, 1-based. Saída: SIM / NAO.
// Pula ID da aresta do pai, não o vértice: paralelas formam ciclo.
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj; // {vizinho, id da aresta}
vector<bool> vis;

bool dfs(int u, int parent_edge) {
    vis[u] = true;
    for (auto [v, id] : adj[u]) {
        if (id == parent_edge) continue;
        if (vis[v]) return true;
        if (dfs(v, id)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    for (int u = 0; u < n; u++) {
        if (!vis[u] && dfs(u, -1)) {
            cout << "SIM\n";
            return 0;
        }
    }
    cout << "NAO\n";
}

/*
COMO LER ESTE CÓDIGO
1. adj[u] guarda {vizinho,id}; ida e volta compartilham o MESMO id.
2. dfs(u,parent_edge) recebe o vértice e a aresta por onde chegou; -1 na raiz.
3. Pulamos só essa aresta do pai. Outro vizinho já visitado revela ciclo;
   um vizinho novo é explorado por dfs(v,id). Se achar ciclo, retorna true.
4. O main inicia uma busca por componente; um único true basta para SIM.
Exemplo: 1-2-3-1 tem ciclo. Duas arestas distintas entre 1 e 2 também têm;
pular o vértice pai, em vez do id da aresta, esconderia esse segundo caso.
Este teste é para grafo NÃO direcionado; não copie para detectar ciclo em DAG.
Como na DFS comum, caminhos muito profundos podem atingir o limite de recursão.
*/
