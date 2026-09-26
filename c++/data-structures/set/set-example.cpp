// Aplicação: guardar valores únicos em ordem crescente.
// Use quando duplicatas não importam e você precisa consultar/percorrer ordenado.
// Complexidade: insert/find O(log N); memória O(N).
// Entrada: N e N inteiros. Ex.: 4 3 1 3 8 -> 1 3 8.
// Total O(N log(K+1)), memória O(K) para K distintos. Set perde frequências.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> values;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        values.insert(x); // uma segunda inserção do mesmo x não cria duplicata
    }

    for (int x : values) cout << x << ' ';
    cout << '\n';
}
