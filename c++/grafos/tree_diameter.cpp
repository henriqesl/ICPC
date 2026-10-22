// Diâmetro de árvore CONEXA, sem peso; resultado em arestas.
// Duas BFS: qualquer nó -> mais distante A -> mais distante B.
// O(V) tempo/memória; não use em grafo geral ou floresta.
// Entrada: n >= 1; n-1 arestas u v, 1-based. Saída: diâmetro.
#include <bits/stdc++.h>
using namespace std;

pair<int, int> bfs(int start, const vector<vector<int>> &adj) {
    vector<int> dist(adj.size(), -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    int far = start;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
            if (dist[v] > dist[far]) far = v;
        }
    }
    return {far, dist[far]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int a = bfs(0, adj).first;
    int diameter = bfs(a, adj).second;
    cout << diameter << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. bfs(start,adj) retorna um par {vértice mais distante,distância até ele}.
   far é atualizado quando aparece um vértice com distância maior.
2. A primeira BFS parte de um nó qualquer e encontra um extremo a.
3. A segunda parte de a; a maior distância encontrada é o diâmetro.
   .first lê o vértice do par; .second lê sua distância.
Exemplo: caminho 1-2-3-4 -> diâmetro 3 arestas; árvore de um nó -> 0.
A propriedade das duas BFS exige árvore conexa sem peso neste template.
Em grafo geral, duas BFS não garantem o maior caminho/distância.
*/
