// Aplicação: buscar, contar, ordenar ou obter o índice de um valor.
// Entrada: n, os n valores e um valor x.
// Complexidade: find/count O(N); sort O(N log N).
// Ex.: 4 3 1 3 8 3 -> indice=0 / ocorrencias=2 / 1 3 3 8.
// Índice ORIGINAL antes do sort; -1 se ausente. Memória O(N).
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cin >> x;

    // find retorna um iterador; a distância até begin() é o índice.
    auto it = find(v.begin(), v.end(), x);
    // end() significa que não encontrou. Não podemos ler *end().
    int index = -1;
    if (it != v.end()) index = int(it - v.begin());

    cout << "indice=" << index << '\n';
    cout << "ocorrencias=" << count(v.begin(), v.end(), x) << '\n';

    sort(v.begin(), v.end()); // ordena o próprio vector
    for (int value : v) cout << value << ' ';
    cout << '\n';
}
