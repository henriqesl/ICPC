// JANELA: maior trecho com até K distintos; aceita negativos.
// Entrada: n k; n valores (K >= 0). Saída: maior tamanho.
// O(N) médio com hash, O(N²) pior; O(N) memória.
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
        frequencia[valores[direita]]++;
        while (int(frequencia.size()) > k) {
            int sai = valores[esquerda];
            frequencia[sai]--;
            if (frequencia[sai] == 0) {
                frequencia.erase(sai); // zero não conta
            }
            esquerda++;
        }
        int tamanho = direita - esquerda + 1;
        if (tamanho > melhor) melhor = tamanho;
    }
    cout << melhor << '\n';
    // Exatamente K distintos exige outra adaptação.
}

/*
COMO LER ESTE CÓDIGO
1. frequencia[x] conta quantas cópias de x estão na janela atual.
   frequencia.size() conta chaves distintas, não o tamanho do trecho.
2. direita inclui um elemento. Se houver mais de k chaves, esquerda retira
   elementos até corrigir; frequência zero precisa ser apagada com erase.
3. Após corrigir, comparamos direita-esquerda+1 com melhor.
Exemplo: [1,2,1,3], k=2 -> trecho [1,2,1], tamanho 3.
Aceita valores negativos porque a condição depende de frequências, não da soma.
Com k=0, a resposta é zero. ATÉ k não significa EXATAMENTE k.
*/
