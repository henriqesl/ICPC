// BUSCA BINÁRIA: primeiro índice com valor >= alvo em vetor ORDENADO.
// Entrada: N, N inteiros e alvo. Ex.: 4 1 3 3 8 3 -> 1.
// Se não existir valor >= alvo, imprime -1. Não é busca de igualdade!
// Busca O(log N), O(1) auxiliar; leitura/armazenamento O(N).
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
    int direita = n; // limite EXCLUSIVO; nunca acessamos valores[n]
    while (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (valores[meio] >= alvo) {
            direita = meio; // pode servir; procure um índice ainda menor
        } else {
            esquerda = meio + 1; // meio e anteriores são pequenos demais
        }
    }
    if (esquerda == n) cout << -1 << '\n';
    else cout << esquerda << '\n';
    // Para igualdade: confira também valores[esquerda] == alvo após validar índice.
}
