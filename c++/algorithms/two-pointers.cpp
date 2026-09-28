// DOIS PONTEIROS: dois índices distintos cuja soma seja alvo.
// Entrada: N, N valores ORDENADOS e alvo. Ex.: 4 1 3 5 8 9 -> 0 3.
// Tempo O(N), estado O(1), vetor O(N). Soma deve caber em long long.
// Aceita negativos. Não ordene sem preservar índices, se a saída exige os originais.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    long long alvo;
    cin >> alvo;

    int esquerda = 0;
    int direita = n - 1;
    bool encontrou = false;
    while (esquerda < direita) {
        long long soma = valores[esquerda] + valores[direita];
        if (soma == alvo) {
            cout << esquerda << ' ' << direita << '\n';
            encontrou = true;
            break;
        }
        if (soma < alvo) esquerda++; // precisamos de uma soma maior
        else direita--;             // precisamos de uma soma menor
    }
    if (!encontrou) cout << -1 << '\n';
    // Diferente de sliding window: aqui escolhemos dois valores, não somamos um trecho.
}
