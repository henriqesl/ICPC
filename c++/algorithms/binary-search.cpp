// BUSCA BINÁRIA: primeiro índice >= alvo; vetor crescente.
// Entrada: n; n valores; alvo. Saída: índice base 0 ou -1.
// O(log N) busca; O(N) leitura/memória. Limite não garante igualdade.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, alvo;
    cin >> n;
    vector<int> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    cin >> alvo;

    int esquerda = 0;
    int direita = n; // [esquerda,direita)
    while (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (valores[meio] >= alvo) {
            direita = meio; // tenta menor
        } else {
            esquerda = meio + 1; // descarta até meio
        }
    }
    if (esquerda == n) cout << -1 << '\n';
    else cout << esquerda << '\n';
    // Igualdade: valide índice e compare valor com alvo.
}
