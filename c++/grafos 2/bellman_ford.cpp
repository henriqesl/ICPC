// BELLMAN-FORD: uma origem; aceita pesos negativos.
// O(V+VE) tempo, O(V+E) memória; N-1 passagens + teste extra.
// Entrada: n m s; m arestas u v w, direcionadas, 1-based.
// Saída: distâncias/INF ou CICLO NEGATIVO alcançável da origem.
// Limite suficiente: V*E*max|w| < INF; nunca some INF.
// Ciclo alcançável só afeta destinos alcançáveis a partir dele.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        edges.push_back({u, v, w}); // direcionado
    }
    vector<ll> dist(n, INF);
    dist[s] = 0;
    for (int rep = 0; rep < n - 1; rep++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) {
                continue; // não propague de um vértice inalcançável
            }
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    bool cicloNegativo = false;
    for (auto [u, v, w] : edges) { // iteração extra
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cicloNegativo = true;
        }
    }

    if (cicloNegativo) {
        cout << "CICLO NEGATIVO\n";
        return 0;
    }

    for (ll d : dist) {
        if (d == INF) {
            cout << "INF ";
        } else {
            cout << d << ' ';
        }
    }
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. --s, --u e --v convertem os vértices da entrada para índices 0..n-1.
   edges guarda {origem, destino, peso}; auto [u, v, w] separa esses campos.
2. dist começa em INF, exceto na origem s, onde vale zero.
3. Cada passagem percorre TODAS as arestas. Se conseguimos chegar a u,
   testamos dist[u]+w como novo custo de v e guardamos o menor com min.
4. Sem ciclo negativo alcançável, n-1 passagens bastam: um caminho mínimo
   pode ser escolhido sem repetir vértices, usando até n-1 arestas.
5. Se uma aresta ainda melhorar na verificação extra, existe ciclo negativo
   alcançável da origem. O programa avisa e não imprime as distâncias.
Exemplo: 1->2 custa 4 e 2->3 custa -7. O custo de 1 até 3 fica 4-7=-3.
O teste de INF impede que um ciclo em outra componente gere um falso aviso.
Um ciclo negativo só impede mínimo nos destinos alcançáveis a partir dele.
*/
