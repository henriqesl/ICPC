// DIJKSTRA: menor caminho de uma origem; pesos >= 0. Não aceita negativos.
// O(V + E log(E+1)) tempo, O(V+E) memória.
// Como no slide: priority_queue padrão + distância negativa simula min-heap.
// Entrada: n m s; m arestas u v w, direcionadas; vértices 1-based.
// Saída: distâncias ou INF. Peso e distâncias finitas < INF.
// Negativos: bellman_ford.cpp. Todos os pares, N pequeno: floyd_warshall.cpp.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

vector<vector<pair<int, ll>>> adj;
vector<ll> dist;

void dijkstra(int start) {
    dist.assign(adj.size(), INF);
    dist[start] = 0;
    priority_queue<pair<ll, int>> pq; // {-distância, vértice}
    pq.push({0, start});

    while (!pq.empty()) {
        auto [total, cur] = pq.top();
        pq.pop();
        total = -total; // volta à distância real

        if (dist[cur] < total) {
            continue; // já encontramos um caminho melhor
        }

        for (auto [viz, custo] : adj[cur]) {
            if (dist[viz] > total + custo) {
                dist[viz] = total + custo;
                pq.push({-dist[viz], viz});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // direcionado
        // adj[v].push_back({u, w}); // não direcionado
    }

    dijkstra(s);

    for (int u = 1; u <= n; u++) {
        if (dist[u] == INF) {
            cout << "INF ";
        } else {
            cout << dist[u] << ' ';
        }
    }
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. main só lê o grafo, chama dijkstra(s) e imprime as distâncias.
   adj[u] guarda pares {vizinho, peso}; auto [viz, custo] separa esse par.
2. dist[u] é o menor custo encontrado da origem até u. Começa em INF;
   só a origem começa em 0. assign reinicia as distâncias a cada chamada.
3. priority_queue tira o MAIOR valor. Guardamos -distância para tirar
   primeiro o menor custo: entre -3 e -8, sai -3 (distância real 3).
4. top lê o próximo par; pop o remove. cur é o vértice retirado;
   total = -total recupera o custo real guardado na fila.
5. Se dist[cur] < total, esse registro ficou antigo: continue o ignora.
6. Para cada vizinho, total + custo é o caminho passando por cur.
   Se melhorar dist[viz], atualizamos e colocamos o novo custo na fila.
Exemplo: 1->2 custa 8, 1->3 custa 3, 3->2 custa 2. Partindo de 1,
visitamos 3 antes de 2 e melhoramos dist[2] de 8 para 3+2=5.
INF no final = não existe caminho. Pesos negativos exigem outro algoritmo.
*/
