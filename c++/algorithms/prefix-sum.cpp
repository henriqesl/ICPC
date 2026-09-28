// PREFIX SUM: soma de muitos intervalos em uma sequência que não muda.
// Entrada: N, N valores, Q e Q pares L R (inclusivos, começando em ZERO).
// Ex.: 4 2 3 5 1 2 1 2 0 3 -> saídas 8 e 11.
// Exige 0 <= L <= R < N; somas intermediárias cabem em long long.
// Construção O(N), cada consulta O(1), memória O(N).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> prefixo(n + 1, 0);
    // Uma posição extra: prefixo[0] = 0 (não somou nada).

    for (int i = 0; i < n; i++) {
        long long valor;
        cin >> valor;
        prefixo[i + 1] = prefixo[i] + valor;
    }
    // valores:        [2, 3, 5, 1]
    // prefixo:     [0, 2, 5,10,11]
    // prefixo[i] = soma dos PRIMEIROS i elementos (não inclui posição i).

    int consultas;
    cin >> consultas;
    while (consultas > 0) {
        int esquerda, direita;
        cin >> esquerda >> direita;

        // Soma até direita MENOS tudo que veio antes de esquerda.
        // [1,2] => prefixo[3] - prefixo[1] => 10 - 2 => 8.
        long long soma = prefixo[direita + 1] - prefixo[esquerda];
        cout << soma << '\n';
        consultas--;
    }
    // Se a entrada usar índices a partir de 1: subtraia 1 de ambos antes.
    // Se os valores forem alterados, os prefixos precisam ser atualizados.
}
