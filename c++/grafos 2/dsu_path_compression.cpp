// DSU: otimização 1 do slide; SOMENTE compressão de caminhos.
// Find encurta caminhos; join apenas liga as raízes, sem comparar tamanhos.
// O(log V) amortizado; find isolado pode custar O(V). Memória O(V).
// Find iterativo: não depende da pilha de recursão.
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
        int raiz = u;
        while (pai[raiz] != raiz) {
            raiz = pai[raiz];
        }

        while (u != raiz) { // aponta o caminho inteiro para a raiz
            int proximo = pai[u];
            pai[u] = raiz;
            u = proximo;
        }
        return raiz;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return false;
        }
        pai[v] = u;
        return true;
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
