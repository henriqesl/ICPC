// PREFIX SUM: somas em array fixo; aceita negativos.
// Entrada: n; n valores; q; q pares L R (base 0, inclusivos).
// O(N) preparo/memória; O(1) consulta. 0 <= L <= R < N.
// Somas em long long; atualização deixa prefixos desatualizados.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> prefixo(n + 1, 0);

    for (int i = 0; i < n; i++) {
        long long valor;
        cin >> valor;
        prefixo[i + 1] = prefixo[i] + valor;
    }
    // prefixo[i] = soma de [0,i).

    int consultas;
    cin >> consultas;
    while (consultas > 0) {
        int esquerda, direita;
        cin >> esquerda >> direita;

        // [L,R] inclusivo: p[R+1] - p[L].
        long long soma = prefixo[direita + 1] - prefixo[esquerda];
        cout << soma << '\n';
        consultas--;
    }
    // Input 1-based: --L; --R. Contar pares: acumule (valor%2 == 0).
    // Média: double(soma)/(R-L+1). Não funciona para mínimo.
    // Atualizar intervalos, só ver final: difference-array.cpp.
}
