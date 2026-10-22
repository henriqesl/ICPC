// SORT: crescente / decrescente; muda a sequência.
// Entrada: n; n valores. Saída: crescente, depois decrescente.
// O(N log N) tempo, O(N) vetor. Sort não é estável; preserve (valor,id).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    sort(v.begin(), v.end()); // crescente
    for (int x : v) cout << x << ' ';
    cout << '\n';

    // Trecho [L,R): sort(v.begin()+L,v.begin()+R), 0 <= L <= R <= N.
    // Extremos: min_element/max_element O(N). Empates estáveis: stable_sort.
    // Únicos: sort + erase(unique(...),end()); veja ../basics/vector.cpp.
    // Coluna/second/índices: sorting-variants.cpp.

    sort(v.rbegin(), v.rend()); // decrescente
    for (int x : v) cout << x << ' ';
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. sort(begin,end) reorganiza o próprio vetor em ordem crescente.
   end fica depois do último: os intervalos da STL são [início,fim).
2. rbegin/rend percorrem ao contrário; ordenar nesse sentido deixa v decrescente.
3. Os dois for imprimem valores, não índices originais.
Exemplo: [3,1,2] imprime 1 2 3 e depois 3 2 1.
Ordenar não remove repetições e perde a ordem original; preserve uma cópia
ou pares {valor,índice} se o problema precisar recuperar as posições.
*/
