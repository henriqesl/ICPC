# Grafos 2

[Índice de grafos](../../README.md#grafos)

V = vértices; E = arestas; N = V. Entradas 1-based, código 0-based; N >= 1.
Blocos independentes; DSU é uma estrutura reutilizável, os demais são programas completos.
Distâncias em `long long`; `INF = LLONG_MAX/4`. Nunca some INF.

## 1. Mapa mental de escolha de algoritmo

- Sem peso → [BFS](bfs.cpp).
- Menor caminho de uma origem, pesos não negativos → [Dijkstra](#2-dijkstra).
- Menor caminho de uma origem, pesos podem ser negativos → [Bellman-Ford](#4-bellman-ford).
- Todos os pares / muitas origens e N pequeno → [Floyd-Warshall](#3-floyd-warshall).
- Conectar todos com menor custo total → [MST](#7-mst).
- MST processando arestas → [Kruskal + DSU](#8-kruskal).
- Unir componentes / testar conectividade → [DSU](#6-dsu).
- Mesmo vértice em situações que mudam o futuro → [modelagem por estados](#5-modelagem-por-estados).

## 2. Dijkstra

- **Use:** menor caminho de uma origem; pesos >= 0, inclusive zero.
- **Não use:** pesos negativos. **Dijkstra não funciona com pesos negativos.**
- **Ideia:** min-heap escolhe a menor distância pendente; descarte entradas antigas.
- **Relaxamento:** `dist[v] = min(dist[v], dist[u] + w)`.
- **Custo:** heap lazy deste código: O(V + E log(E+1)); memória O(V+E). Em grafo simples, a forma usual é O((V+E) log V).
- **Limite numérico:** 0 <= peso < INF e toda distância finita relevante < INF.

Entrada: `n m s`, depois m arestas `u v w`. Saída: distâncias; INF = inalcançável.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v, w}); // direcionado
        // adj[v].push_back({u, w}); // não direcionado
    }
    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue; // entrada antiga
        for (auto [v, w] : adj[u]) {
            ll nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    for (ll d : dist) {
        if (d == INF) cout << "INF ";
        else cout << d << ' ';
    }
    cout << '\n';
}
```

## 3. Floyd-Warshall

- **Use:** todos para todos, N pequeno e muitas consultas de distância.
- **Padrão:** **N ~ 500 + muitas queries → forte candidato**; confira o tempo para ~125 milhões de transições.
- **Matriz:** diagonal 0; arestas = menor peso entre repetidas; restante INF.
- **Transição:** `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.
- **Ordem obrigatória:** **k, i, j**.
- **Custo:** O(N³) cálculo, O(1) por consulta; memória O(N²). Programa total O(N³+E+Q).
- Aceita pesos negativos; **template pressupõe ausência de ciclos negativos** e `N·max|peso| < INF`.
- `dist[k][k] < 0` denuncia ciclo negativo: pares que conseguem passar por ele não têm distância mínima finita.

Entrada: `n m q`, m arestas direcionadas `u v w`, q consultas `u v`. Saída: distância ou INF.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (int e = 0; e < m; e++) {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        dist[u][v] = min(dist[u][v], w);
        // dist[v][u] = min(dist[v][u], w); // não direcionado
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    while (q--) {
        int u, v;
        cin >> u >> v; --u; --v;
        if (dist[u][v] == INF) cout << "INF\n";
        else cout << dist[u][v] << '\n';
    }
}
```

## 4. Bellman-Ford

- **Use:** uma origem; aceita pesos negativos.
- Relaxe **todas as arestas N-1 vezes**; pare cedo se nada mudar.
- Uma iteração extra ainda melhora alguma distância → ciclo negativo **alcançável da origem**.
- **Custo:** O(VE) relaxamentos; com inicialização, O(V+VE). Memória O(V+E).
- Dijkstra é mais rápido, mas exige pesos não negativos; Bellman-Ford aceita negativos e detecta ciclo.
- **Limite numérico suficiente:** `V·E·max|peso| < INF`; inclui relaxamentos com ciclos negativos. Não calcule esse produto em tipo que possa estourar.

Entrada: `n m s`, m arestas direcionadas `u v w`. Saída: distâncias/INF ou CICLO NEGATIVO.
O aviso refere-se a algum ciclo alcançável; um destino só perde seu mínimo se também for alcançável a partir desse ciclo.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    int n, m, s;
    cin >> n >> m >> s; --s;
    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        edges.push_back({u, v, w}); // direcionado
    }
    vector<ll> dist(n, INF);
    dist[s] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool changed = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) break;
    }
    for (auto [u, v, w] : edges) { // iteração extra
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "CICLO NEGATIVO\n";
            return 0;
        }
    }
    for (ll d : dist) {
        if (d == INF) cout << "INF ";
        else cout << d << ' ';
    }
    cout << '\n';
}
```

## 5. Modelagem por estados

Se chegar ao mesmo vértice em situações diferentes muda as próximas escolhas, use **(vértice, estado)**.

- Cupom: `dist[v][0/1]` = ainda disponível / já usado; início `(s,0)`.
- Aresta normal: `(u,c) → (v,c)`, custo w.
- Usar cupom: `(u,0) → (v,1)`, custo com desconto; não existe segunda utilização.
- Cupom opcional: resposta `min(dist[t][0], dist[t][1])`; obrigatório: `dist[t][1]`.
- Outros estados: combustível, obstáculos quebrados, máscara de chaves, modo/dia/noite.

Pense em **camadas**: transições mantêm ou mudam a camada. Depois aplique BFS se cada transição custa 1; Dijkstra se todos os custos são não negativos.
Conte o grafo expandido: S estados por vértice → até V·S vértices; o custo depende também das transições geradas. Máscaras de K chaves podem gerar 2^K estados.

## 6. DSU

- **Use:** componentes sendo unidas; conectividade incremental (**só adições**).
- `parent[u]`: pai; `find(u)`: representante, com **path compression**.
- `unite(u,v)`: une por tamanho (**union by size**); retorna false se já estavam juntos.
- `same(u,v)`: mesma componente? Em grafo não direcionado, adicionar aresta entre eles cria ciclo.
- **Custo:** O(α(V)) amortizado por operação, praticamente O(1); inicialização/memória O(V).
- Não remove arestas; não calcula caminhos nem distâncias. Reinicialize entre casos.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    explicit DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    bool same(int u, int v) { return find(u) == find(v); }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        return true;
    }
};
```

## 7. MST

- **Spanning tree:** árvore geradora; conecta todos os vértices de um grafo **não direcionado**, sem ciclos.
- **MST:** árvore geradora de menor **soma dos pesos**; possui **N-1 arestas**.
- **Shortest path:** minimiza distância entre origem/destino; **MST não garante menores caminhos**.
- Pesos negativos são permitidos. Desconectado → não existe MST; é possível obter floresta geradora mínima.

## 8. Kruskal

**Kruskal = sort das arestas + DSU.**

1. Ordene por peso crescente.
2. Endpoints em componentes diferentes? Adicione a aresta e una.
3. Já estão juntos? Pule: fecharia ciclo.
4. N-1 escolhidas → MST; menos → grafo desconectado.

**Custo:** O(E log E + E·α(V) + V); memória O(V+E).
Entrada: `n m`, m arestas **não direcionadas** `u v w`. Saída: custo ou IMPOSSIVEL.
Toda soma parcial do custo precisa caber em `long long`. DSU repetida abaixo para copiar o programa isoladamente.

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent, sz;
    explicit DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    bool same(int u, int v) { return find(u) == find(v); }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<ll, int, int>> edges; // {peso,u,v}
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll cost = 0;
    int used = 0;
    for (auto [w, u, v] : edges) {
        if (!dsu.unite(u, v)) continue; // fecharia ciclo
        cost += w;
        if (++used == n - 1) break;
    }
    if (used != n - 1) cout << "IMPOSSIVEL\n";
    else cout << cost << '\n';
}
```

## 9. Comparação rápida

| Algoritmo | Uso | Pesos negativos? | Complexidade de tempo |
|---|---|---|---|
| BFS | Uma origem, sem peso | Não; cada aresta conta 1 | O(V+E) |
| Dijkstra | Uma origem, ponderado | **Não** | O(V + E log(E+1)), heap lazy |
| Bellman-Ford | Uma origem; detectar ciclo alcançável | Sim; ciclo pode impedir mínimo | O(V+VE) |
| Floyd-Warshall | Todos os pares | Sim, sem ciclo negativo afetando o par | O(V³); consulta O(1) |
| Kruskal + DSU | MST não direcionada | Sim | O(E log E + E·α(V) + V) |
| DSU | Unir/testar componentes | Não depende de pesos | O(α(V)) amortizado; inicialização O(V) |

## 10. Erros comuns

- Dijkstra com peso negativo, mesmo sem ciclo negativo.
- Muitas origens + N pequeno: ignorar Floyd e repetir Dijkstra sem comparar custos.
- Muitas queries da **mesma origem**: recalcular em vez de reutilizar distâncias.
- Floyd sem diagonal zero, sem min nas arestas repetidas ou com k fora do loop externo.
- Somar INF, usar int para distâncias ou ignorar limites dos intermediários.
- Bellman-Ford detectando ciclo inalcançável por esquecer `dist[u] != INF`.
- Confundir MST com shortest path; aceitar Kruskal desconectado ou sem evitar ciclos.
- Tratar MST como direcionada ou DSU como estrutura com remoção de arestas.
- Guardar só `dist[v]` quando cupom/combustível/chave muda o futuro.

## 11. Checklist de contest

- [ ] Há pesos?
- [ ] Há pesos negativos?
- [ ] Uma origem ou todos os pares?
- [ ] Quantas queries e quantas origens diferentes?
- [ ] N é pequeno?
- [ ] Menor caminho ou conectar tudo?
- [ ] Preciso saber componentes?
- [ ] Existe estado extra?
