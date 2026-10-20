// MST: conecta todos com menor soma; N-1 arestas. Não é shortest path.
// KRUSKAL = sort + DSU (compressão + tamanho); pula ciclos.
// O(E log E + E*alpha(V) + V) tempo, O(V+E) memória.
// Entrada: n m; m arestas u v w, NÃO direcionadas, 1-based.
// Saída: custo ou IMPOSSIVEL se desconectado. Aceita pesos negativos.
// Toda soma parcial do custo precisa caber em long long.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> pai, sz;

    DSU(int n) {
        pai.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            pai[i] = i;
        }
    }

    int find(int u) {
        if (pai[u] == u) {
            return u;
        }
        pai[u] = find(pai[u]);
        return pai[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    // dsu.size(u): quantidade de vértices no componente de u.
    // Busca a raiz; sz.size() seria o número de posições do vetor.
    int size(int u) {
        return sz[find(u)];
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return;
        }
        if (sz[v] > sz[u]) {
            swap(u, v);
        }
        pai[v] = u;
        sz[u] += sz[v];
    }
};

struct Aresta {
    int u, v;
    ll c; // custo
};

bool compAresta(const Aresta& a, const Aresta& b) {
    return a.c < b.c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Aresta> arestas;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w; // mantém 1-based, como DSU no slide
        arestas.push_back({u, v, w});
    }

    sort(arestas.begin(), arestas.end(), compAresta);
    DSU dsu(n);
    ll resp = 0;
    int escolhidas = 0;

    for (auto a : arestas) {
        if (dsu.find(a.u) != dsu.find(a.v)) { // não forma ciclo
            resp += a.c;
            dsu.join(a.u, a.v);
            escolhidas++;
        }
    }

    if (escolhidas != n - 1) {
        cout << "IMPOSSIVEL\n";
    } else {
        cout << resp << '\n';
    }
}
