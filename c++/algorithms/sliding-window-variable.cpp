// SLIDING WINDOW VARIÁVEL: maior trecho consecutivo com soma <= LIMITE.
// Entrada: N LIMITE e N valores NÃO NEGATIVOS. LIMITE >= 0.
// Ex.: 5 7 2 1 5 1 3 -> 3 (o trecho [1,5,1]).
// Tempo O(N), memória O(N) para entrada; estado da janela O(1).
// Não use este algoritmo com negativos: retirar da esquerda pode aumentar a soma!
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
        soma += valores[direita]; // tenta ampliar a janela

        while (soma > limite && esquerda <= direita) {
            soma -= valores[esquerda]; // encolhe até a soma caber
            esquerda++;
        }

        int tamanho = direita - esquerda + 1;
        if (tamanho > melhor) melhor = tamanho;
    }
    cout << melhor << '\n';
    // Apesar do while dentro do for, cada elemento entra e sai no máximo uma vez.
}
