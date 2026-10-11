// JANELA VARIÁVEL: maior trecho com soma <= limite.
// Entrada: n limite; n valores NÃO NEGATIVOS; limite >= 0.
// Saída: maior tamanho (0 se nenhum); somas cabem em long long.
// O(N) tempo/memória; estado O(1). Não ordene; não use negativos.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long limite;
    cin >> n >> limite;
    vector<long long> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];

    int esquerda = 0;
    int melhor = 0; // zero se nenhum trecho não vazio couber
    long long soma = 0;

    for (int direita = 0; direita < n; direita++) {
        soma += valores[direita];

        while (soma > limite && esquerda <= direita) {
            soma -= valores[esquerda];
            esquerda++;
        }

        int tamanho = direita - esquerda + 1;
        if (tamanho > melhor) melhor = tamanho;
    }
    cout << melhor << '\n';
    // Cada elemento entra/sai no máximo uma vez.
}
