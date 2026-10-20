// DSU: otimização 2 do slide; SOMENTE união por tamanho.
// Join liga a árvore menor à maior; find NÃO comprime caminhos.
// O(log V) por operação; inicialização/memória O(V).
// Entrada: n q; q comandos tipo u v, 1-based: 1=join, 2=same.
// Saída: SIM/NAO nas consultas. DSU não remove arestas.
// Kruskal usa as DUAS otimizações: O(alpha(V)) amortizado.
#include <bits/stdc++.h>
using namespace std;

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
        return find(pai[u]); // sem salvar: NÃO comprime caminhos
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    DSU dsu(n);

    while (q--) {
        int tipo, u, v;
        cin >> tipo >> u >> v;

        if (tipo == 1) {
            dsu.join(u, v);
        } else {
            bool conectados = dsu.same(u, v);
            if (conectados) {
                cout << "SIM\n";
            } else {
                cout << "NAO\n";
            }
        }
    }
}
