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

/*
COMO LER ESTE CÓDIGO
1. prefixo tem n+1 posições: prefixo[0]=0 e prefixo[i] soma [0,i).
2. Ao ler valor do índice i, prefixo[i+1]=prefixo[i]+valor.
3. Para [L,R] inclusivo, prefixo[R+1]-prefixo[L] cancela tudo antes de L.
Exemplo: valores [2,-1,4] -> prefixo [0,2,1,5]. Consulta [1,2]: 5-2=3.
O +1 em R vem da convenção de prefixo, não de a entrada ser base 1.
Não precisa ordenar e aceita negativos. Se valores mudarem, refaça os prefixos
ou use uma estrutura de atualização; o vetor antigo não se atualiza sozinho.
*/
