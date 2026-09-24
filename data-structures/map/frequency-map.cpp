// Aplicação: contar frequência de valores, letras, categorias ou estados.
// Use map quando as chaves não forem apenas índices pequenos e contínuos.
// Complexidade: O(log N) por inserção/busca; memória O(N).
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
