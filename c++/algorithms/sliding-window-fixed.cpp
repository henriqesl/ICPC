// SLIDING WINDOW FIXA: maior soma de K elementos CONSECUTIVOS.
// Entrada: N K e N valores. Ex.: 5 3 2 1 5 1 3 -> 9.
// Janelas: [2,1,5]=8; [1,5,1]=7; [5,1,3]=9.
// Exige 1 <= K <= N. Aceita negativos. Somas devem caber em long long.
// Tempo O(N), memória O(N) para guardar entrada; estado da janela O(1).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];

    long long soma = 0;
    for (int i = 0; i < k; i++) soma += valores[i]; // primeira janela
    long long melhor = soma; // não comece em zero: todos podem ser negativos!

    for (int direita = k; direita < n; direita++) {
        soma -= valores[direita - k]; // sai o mais antigo, da esquerda
        soma += valores[direita];     // entra um novo, da direita
        if (soma > melhor) melhor = soma;
    }
    cout << melhor << '\n';
}
