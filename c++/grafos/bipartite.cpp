// Bipartido = 2-coloring; vizinhos não podem ter mesma cor.
// O(V + E) tempo/memória; percorre TODAS as componentes.
// Entrada: n m; m arestas u v, 1-based, não direcionadas.
// Saída: SIM / NAO. Self-loop impede bipartição.
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

    vector<int> color(n, -1);
    queue<int> q;
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue;
        color[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u]; // alterna 0 e 1
                    q.push(v);
                } else if (color[v] == color[u]) {
                    cout << "NAO\n";
                    return 0;
                }
            }
        }
    }
    cout << "SIM\n";
}

/*
COMO LER ESTE CÓDIGO
1. color=-1 significa sem cor; cada nova componente começa com cor 0.
2. A BFS tenta pintar cada vizinho com 1-color[u]: alterna entre 0 e 1.
3. Vizinho já pintado com a mesma cor de u revela um conflito: imprime NAO.
4. O for externo começa buscas nas componentes ainda não visitadas;
   testar só a primeira componente poderia esconder um conflito em outra.
Exemplo: caminho 1-2-3 aceita cores 0,1,0; um triângulo não aceita duas cores.
SIM significa que todo o grafo pode ser separado em dois grupos sem
arestas internas a um grupo. Uma aresta de um nó para si impede isso.
*/
