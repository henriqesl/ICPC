// DSU: otimização 1 do slide; SOMENTE compressão de caminhos.
// Find encurta caminhos; join apenas liga as raízes, sem comparar tamanhos.
// O(log V) amortizado; find isolado pode custar O(V). Memória O(V).
// Find recursivo como no slide; cadeias profundas podem estourar a pilha.
// Para N grande, prefira também união por tamanho (DSU de kruskal.cpp).
// Entrada: n q; q comandos tipo u v, 1-based: 1=join, 2=same.
// Saída: SIM/NAO nas consultas. DSU não remove arestas.
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> pai;

    DSU(int n) {
        pai.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            pai[i] = i;
        }
    }

    int find(int u) {
        if (pai[u] == u) {
            return u;
        }
        pai[u] = find(pai[u]); // salva a raiz: compressão de caminhos
        return pai[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return;
        }
        pai[v] = u;
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
