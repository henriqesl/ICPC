// JANELA FIXA: maior soma de K consecutivos; aceita negativos.
// Entrada: n k; n valores; 1 <= K <= N. Saída: maior soma.
// O(N) tempo/memória; estado O(1). Somas cabem em long long.
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
    long long melhor = soma; // não zero: aceita negativos

    for (int direita = k; direita < n; direita++) {
        soma -= valores[direita - k]; // sai
        soma += valores[direita];     // entra
        if (soma > melhor) melhor = soma;
    }
    cout << melhor << '\n';
}
