// UNORDERED_MAP: chave -> frequência, sem ordem/bounds.
// Entrada: n; n valores; q; q chaves. Saída: frequências na ordem das consultas.
// O(1) médio por chave, O(D) pior; memória O(D), D distintos.
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> frequencia;
    frequencia.reserve(n); // capacidade; não cria chaves

    for (int i = 0; i < n; i++) {
        int numero;
        cin >> numero;
        frequencia[numero]++;
    }

    int consultas;
    cin >> consultas;
    while (consultas > 0) {
        int procurado;
        cin >> procurado;
        auto it = frequencia.find(procurado);

        if (it == frequencia.end()) cout << 0 << '\n';
        else cout << it->second << '\n';
        consultas--;
    }
    // count(chave): presença 0/1, não frequência; erase(chave): remove.
    // Ordem/vizinhos: use map. Rehash invalida iteradores; refaça find.
    // Reserve não elimina pior caso do hash.
}
