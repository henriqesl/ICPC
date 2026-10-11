// Bipartido = 2-coloring; vizinhos não podem ter mesma cor.
// O(V + E) tempo/memória; percorre TODAS as componentes.
// Entrada: n m; m arestas u v, 1-based, não direcionadas.
// Saída: SIM / NAO. Self-loop impede bipartição.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
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
                    color[v] = color[u] ^ 1;
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
