// Aplicação: buscar, contar, ordenar ou obter o índice de um valor.
// Entrada: n, os n valores e um valor x.
// Complexidade: find/count O(N); sort O(N log N).
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int& value : v) cin >> value;
    cin >> x;

    // find retorna um iterador; a distância até begin() é o índice.
    auto it = find(v.begin(), v.end(), x);
    int index = it == v.end() ? -1 : int(it - v.begin());

    cout << "indice=" << index << '\n';
    cout << "ocorrencias=" << count(v.begin(), v.end(), x) << '\n';

    sort(v.begin(), v.end()); // ordena o próprio vector
    for (int value : v) cout << value << ' ';
    cout << '\n';
}
