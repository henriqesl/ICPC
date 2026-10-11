// DEQUE MONOTÔNICA: máximo de cada janela K consecutiva.
// Entrada: n k; n valores. Saída: máximos; 1 <= K <= N.
// O(N) tempo; deque O(K), entrada O(N). Aceita negativos/repetidos.
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
        // [r-K+1,r]: remove expirados.
        while (!candidatos.empty() && candidatos.front() <= r - k) {
            candidatos.pop_front();
        }
        // Remove dominados pelo novo.
        while (!candidatos.empty() && valores[candidatos.back()] <= valores[r]) {
            candidatos.pop_back();
        }
        candidatos.push_back(r);
        // Frente = máximo válido.
        if (r >= k - 1) cout << valores[candidatos.front()] << ' ';
    }
    cout << '\n';
    // Mínimo: <= vira >= só no segundo while; não mude expiração.
    // Cada índice entra/sai uma vez.
}
