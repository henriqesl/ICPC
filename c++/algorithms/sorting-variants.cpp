// VARIANTES DE SORT: trecho, pair, coluna, índices e estabilidade.
// Sem entrada: cada bloco é uma demonstração independente, dentro do main.
// Leia sorting.md para escolher o bloco; não copie todos para uma solução.
// Sort O(N log N); trecho de M itens O(M log M). Índices/pares extras usam O(N).
#include <bits/stdc++.h>
using namespace std;

int main() {
    { // 1. Ordenar só índices [1,3], inclusivos; fim exclusivo = begin()+4.
        vector<int> v{9, 4, 2, 3, 8};
        sort(v.begin() + 1, v.begin() + 4);
        cout << "trecho: ";
        for (int x : v) cout << x << ' '; // 9 2 3 4 8
        cout << '\n';
    }
    { // 2. Valor + índice original; comparação padrão: first, depois second.
        vector<int> valores{8, 3, 3};
        vector<pair<int,int>> itens;
        for (int i = 0; i < int(valores.size()); i++) itens.push_back({valores[i], i});
        sort(itens.begin(), itens.end());
        cout << "pares: ";
        for (auto p : itens) cout << p.first << ':' << p.second << ' ';
        cout << '\n';
    }
    { // 3. Ordenar pelo SECOND; empate pelo FIRST. a/b são pares, não índices.
        vector<pair<int,int>> v{{10, 2}, {8, 1}, {5, 1}};
        sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });
        cout << "second: ";
        for (auto p : v) cout << p.first << ':' << p.second << ' ';
        cout << '\n';
    }
    { // 4. Coluna 1 = nota, maior primeiro. Coluna 0 = id, menor no empate.
        vector<vector<int>> registros{{0, 7}, {1, 9}, {2, 7}};
        sort(registros.begin(), registros.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[1] != b[1]) return a[1] > b[1];
            return a[0] < b[0];
        });
        cout << "coluna: ";
        for (const auto& linha : registros) cout << linha[0] << ':' << linha[1] << ' ';
        cout << '\n';
    }
    { // 5. Ordenar ÍNDICES: o vetor de valores NÃO muda.
        vector<int> valores{8, 3, 3};
        vector<int> ordem(valores.size());
        iota(ordem.begin(), ordem.end(), 0); // gera 0,1,2
        sort(ordem.begin(), ordem.end(), [&valores](int i, int j) {
            // [&valores] consulta o vetor externo; i/j são posições nele.
            if (valores[i] != valores[j]) return valores[i] < valores[j];
            return i < j;
        });
        cout << "indices: ";
        for (int i : ordem) cout << i << ':' << valores[i] << ' ';
        cout << '\n';
    }
    { // 6. Ordenar só por nota, mantendo chegada nos empates, não id crescente.
        vector<pair<int,int>> v{{7, 4}, {9, 1}, {7, 2}};
        stable_sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.first < b.first;
        });
        cout << "estavel: ";
        for (auto p : v) cout << p.first << ':' << p.second << ' ';
        cout << '\n';
    }
    // Toda comparação acima é estrita: para itens iguais, retorna false.
    // Nunca altere os itens/chaves comparados dentro do comparator.
}
