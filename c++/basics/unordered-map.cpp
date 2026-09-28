// UNORDERED_MAP: chave -> valor, sem ordem de percurso garantida.
// Use para consultas/contagens frequentes quando não precisa de ordem.
// Entrada: N, N inteiros, Q e Q valores a consultar.
// Ex.: 4 3 3 8 3 3 3 8 7 -> 3 / 1 / 0.
// Operação O(1) médio, O(K) pior caso; memória O(K).
// Saída segue a ordem das CONSULTAS, não a ordem interna do mapa.
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> frequencia;

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
        else cout << it->second << '\n'; // ->second é o valor associado
        consultas--;
    }
    // A sintaxe é parecida com map; a ordem e a complexidade são diferentes.
}
