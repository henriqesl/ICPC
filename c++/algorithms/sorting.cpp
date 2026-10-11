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
