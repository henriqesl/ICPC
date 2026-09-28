// Maior trecho CONSECUTIVO com no máximo K valores diferentes.
// Entrada: N K e N inteiros. Ex.: 6 2 1 2 1 3 3 2 -> 3.
// K >= 0; aceita valores negativos (a condição é frequência, não soma).
// Tempo O(N) médio com hash, pior caso O(N²); memória O(N) com vetor.
// Cada posição entra e sai uma vez; a tabela guarda frequências da janela atual.
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];

    unordered_map<int, int> frequencia;
    int esquerda = 0, melhor = 0;
    for (int direita = 0; direita < n; direita++) {
        frequencia[valores[direita]]++; // inclui o novo valor
        while (int(frequencia.size()) > k) {
            int sai = valores[esquerda];
            frequencia[sai]--;
            if (frequencia[sai] == 0) {
                frequencia.erase(sai); // zero NÃO pode contar como distinto!
            }
            esquerda++;
        }
        int tamanho = direita - esquerda + 1;
        if (tamanho > melhor) melhor = tamanho;
    }
    cout << melhor << '\n';
    // Exatamente K distintos é outro objetivo: não troque apenas um sinal sem analisar.
}
