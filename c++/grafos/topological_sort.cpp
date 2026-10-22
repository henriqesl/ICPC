// Kahn: dependências em DAG (grafo direcionado sem ciclo).
// O(V + E) tempo/memória; indegree 0 entra na fila.
// Entrada: n m; m arestas u v, 1-based (u antes de v).
// Saída: uma ordem válida, 1-based; IMPOSSIVEL se houver ciclo.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v); // apenas u -> v
        indegree[v]++;
    }

    queue<int> q;
    for (int u = 0; u < n; u++) {
        if (indegree[u] == 0) q.push(u);
    }
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }

    if (int(order.size()) != n) cout << "IMPOSSIVEL\n";
    else {
        for (int u : order) cout << u + 1 << ' ';
        cout << '\n';
    }
}

/*
COMO LER ESTE CÓDIGO
1. Uma aresta u->v significa que u precisa vir antes de v.
   indegree[v] conta quantas dependências de v ainda não foram removidas.
2. Todos com indegree zero entram na fila: já podem ser processados.
3. Retiramos u, colocamos em order e descontamos uma dependência de cada
   vizinho. --indegree[v] decrementa antes de comparar com zero.
4. Se order tem menos de n vértices, sobrou um ciclo e não há ordem válida.
Exemplo: 1->3 e 2->3 permitem 1,2,3 ou 2,1,3.
u+1 na saída volta à numeração da entrada. Não garante ordem lexicográfica.
*/
