// BFS: menor distância sem peso; dist == -1: não alcançado.
// O(V + E) tempo/memória. Não serve para pesos diferentes.
// Entrada: n m (n >= 1); m arestas u v; start. Vértices 1-based.
// Saída: distâncias de start; não direcionado (retire a volta para directed).
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start;
    cin >> start;
    --start;

    queue<int> q;
    vector<int> dist(n, -1);
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1; // marca ao enfileirar
            q.push(v);
        }
    }
    for (int d : dist) cout << d << ' ';
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. adj[u] lista os vizinhos; --u/--v convertem a entrada para base 0.
2. dist=-1 significa não visitado; a origem começa em 0 e entra na fila.
3. front lê o primeiro da fila; pop o remove. A fila visita por camadas.
4. Um vizinho novo recebe dist[u]+1 e já fica marcado antes de entrar.
   Assim cada vértice entra uma vez e a primeira distância é a menor.
Exemplo: 1-2-3, origem 1, produz 0 1 2; um nó isolado fica com -1.
Cada aresta deve ter o mesmo custo. Pesos diferentes exigem outra técnica.
*/
