// Aplicação: contar frequência de valores, letras, categorias ou estados.
// Use map quando as chaves não forem apenas índices pequenos e contínuos.
// Complexidade: O(log N) por inserção/busca; memória O(N).
// Entrada: N e N inteiros. Ex.: 4 3 3 8 3 -> 3: 3 / 8: 1.
// Saída crescente; K distintos usam O(K) memória. find consulta sem inserir.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> frequency;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        frequency[x]++; // cria a chave com zero se ela ainda não existir
    }

    for (auto [value, amount] : frequency)
        cout << value << ": " << amount << '\n';
}
