// Aplicação: ordenar para facilitar buscas, agrupamentos, pareamentos
// ou comparações entre valores vizinhos.
// Complexidade: O(N log N) tempo.
// Entrada: N e N inteiros. Ex.: 3 2 1 3 -> 1 2 3 / 3 2 1.
// Vector usa O(N); sort não é estável. Para índices originais, guarde pair.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;

    sort(v.begin(), v.end()); // crescente
    for (int x : v) cout << x << ' ';
    cout << '\n';

    sort(v.rbegin(), v.rend()); // decrescente
    for (int x : v) cout << x << ' ';
    cout << '\n';
}
