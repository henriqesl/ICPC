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

/*
COMO LER ESTE CÓDIGO
1. DSU dsu(n) começa com n componentes separados: pai[i]=i.
   A raiz representa o componente e é o único nó que aponta para si mesmo.
2. find(u) segue os pais até a raiz. Ao voltar da recursão, pai[u] recebe
   essa raiz: as próximas buscas pulam os nós intermediários (compressão).
3. same(u,v) compara as RAÍZES, não os pais imediatos dos dois vértices.
4. join(u,v) primeiro encontra as duas raízes. Se forem iguais, nada muda;
   se forem diferentes, pai[v]=u liga a raiz de v à raiz de u.
5. No main, comando 1 faz uma união; comando 2 imprime SIM ou NAO.
Exemplo: numa cadeia 3->2->1, find(3) retorna 1 e muda pai[3] para 1.
Aqui NÃO há união por tamanho. Para size(u) e as duas otimizações juntas,
use o DSU de kruskal.cpp. Cadeias profundas exigem cuidado com a recursão.
*/
