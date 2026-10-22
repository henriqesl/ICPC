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

/*
COMO LER ESTE CÓDIGO
1. Somamos os primeiros k elementos para montar a primeira janela.
   melhor começa nessa soma, não em zero, para aceitar resultados negativos.
2. A cada direita, sai valores[direita-k] e entra valores[direita].
   A soma passa a representar exatamente os últimos k elementos.
3. Comparamos essa soma com melhor, sem recalcular os k valores toda vez.
Exemplo: [2,-1,4], k=2 -> somas 1 e 3; resposta 3.
Aqui o tamanho é fixo e a resposta é uma SOMA. Exige 1<=k<=n.
*/
