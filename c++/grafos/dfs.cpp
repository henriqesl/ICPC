// DFS: componentes / alcance; não calcula menor distância.
// O(V + E) tempo/memória. Recursão profunda pode estourar a pilha.
// Entrada: n m; m arestas u v, 1-based, não direcionadas.
// Saída: número de componentes (inclui isolados).
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            components++;
        }
    }
    cout << components << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. vis[u] informa se u já foi descoberto; adj guarda as ligações.
2. dfs(u) marca u e chama dfs(v) para cada vizinho ainda não visitado.
3. A chamada explora o vizinho e depois volta para continuar o for de u.
   Marcar antes de explorar impede voltar infinitamente pelos ciclos.
4. Uma chamada alcança toda a componente. No main, cada nó ainda não
   visitado inicia outra chamada e aumenta components, incluindo isolados.
Exemplo: aresta 1-2 e vértice 3 isolado -> duas componentes.
DFS não garante menor distância. Um caminho muito profundo exige cuidado
com o limite de recursão do ambiente; aqui mantemos a versão recursiva curta.
*/
