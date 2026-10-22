// BUSCA LINEAR: percorre até encontrar a primeira ocorrência exata.
// Entrada: N, N inteiros e alvo. Ex.: 3 8 1 8 8 -> 0; ausente -> -1.
// Tempo O(N), armazenamento O(N); não exige ordenação.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, alvo;
    cin >> n;
    vector<int> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    cin >> alvo;

    int indice = -1; // permanece -1 se não encontrarmos
    for (int i = 0; i < n; i++) {
        if (valores[i] == alvo) {
            indice = i;
            break; // queremos a PRIMEIRA ocorrência
        }
    }
    cout << indice << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. indice começa em -1, marcador de que o alvo ainda não apareceu.
2. O for testa valores[i] em ordem de índice, sem exigir vetor ordenado.
3. Ao encontrar, salva i e break encerra o laço: garante a primeira ocorrência.
Exemplo: [8,1,8], alvo 8 -> índice 0; alvo 7 -> -1.
O resultado é uma posição base 0, não o valor. Não acesse valores[-1].
*/
