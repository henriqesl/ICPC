// TWO POINTERS: um par de índices distintos com soma alvo.
// Entrada: n; n valores ORDENADOS; alvo. Saída: i j (base 0) ou -1.
// O(N) tempo/vetor; estado O(1). Soma em long long; aceita negativos.
// Índices são do vetor ordenado; preserve (valor,id) se necessário.
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
        if (soma < alvo) esquerda++;
        else direita--;
    }
    if (!encontrou) cout << -1 << '\n';
    // Um par, não um trecho inteiro.
}
