// Várias origens simultâneas; menor distância até qualquer source.
// O(V + E + K) tempo/memória; sem peso.
// Entrada: n m; m arestas u v; k; k fontes. Vértices 1-based.
// Saída: distâncias; -1 se inalcançável. Não direcionado.
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
    int k;
    cin >> k;
    vector<int> sources(k);
    for (int &source : sources) {
        cin >> source;
        --source;
    }

    vector<int> dist(n, -1);
    queue<int> q;
    for (int source : sources) {
        if (dist[source] != -1) continue; // fonte repetida
        dist[source] = 0;
        q.push(source);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    for (int d : dist) cout << d << ' ';
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. É a BFS comum, mas TODAS as origens entram na fila com distância zero.
   Uma origem repetida é ignorada para não duplicar trabalho.
2. A fila expande as fontes por camadas; a primeira que alcança um nó
   garante a menor distância até alguma das fontes, não até todas elas.
3. dist[v]!=-1 impede revisitar; nós inalcançáveis permanecem com -1.
Exemplo: caminho 1-2-3-4-5, fontes 1 e 5 -> distâncias 0 1 2 1 0.
Útil para distância ao hospital/inimigo/fogo mais próximo, sem pesos.
Não é necessário rodar uma BFS separada para cada origem.
*/
