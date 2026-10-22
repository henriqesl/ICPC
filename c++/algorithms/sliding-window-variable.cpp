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

/*
COMO LER ESTE CÓDIGO
1. direita expande o trecho, somando o elemento que entra.
2. Enquanto soma>limite, retiramos valores[esquerda] e avançamos esquerda.
3. Depois de corrigir, [esquerda,direita] é válido; guardamos seu tamanho.
   Se nenhum elemento couber, a janela pode ficar vazia e ter tamanho zero.
Exemplo: [2,1,3,1,1], limite 5 -> maior tamanho 3, como [3,1,1].
Cada índice só avança; o while interno não torna o algoritmo quadrático.
Não ordene nem use negativos: retirar valores deixaria de reduzir a soma.
*/
