// PADRÃO: MÁXIMO de cada janela de K elementos CONSECUTIVOS.
// Entrada: N K e N inteiros. Ex.: 5 3 2 1 5 1 3 -> 5 5 5.
// Exige 1 <= K <= N. Aceita negativos e repetidos.
// Tempo O(N); deque O(K), vetor de entrada O(N).
// A deque guarda ÍNDICES de candidatos, não todos os itens da janela.
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    if (k < 1 || k > n) return 1;
    vector<int> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];

    deque<int> candidatos;
    for (int r = 0; r < n; r++) {
        // Janela atual: [r-K+1,r]. Quem ficou antes disso expirou.
        while (!candidatos.empty() && candidatos.front() <= r - k) {
            candidatos.pop_front();
        }
        // O novo é >= ao antigo e sairá mais tarde: o antigo não precisa ficar.
        while (!candidatos.empty() && valores[candidatos.back()] <= valores[r]) {
            candidatos.pop_back();
        }
        candidatos.push_back(r);
        // Valores decrescentes: frente é o maior candidato ainda válido.
        if (r >= k - 1) cout << valores[candidatos.front()] << ' ';
    }
    cout << '\n';
    // Para MÍNIMO: troque <= por >= só na comparação de VALORES (segundo while).
    // Não mude a comparação de índices que testa expiração.
    // Cada índice entra e sai no máximo uma vez: não vira O(N²) pelo while.
}
