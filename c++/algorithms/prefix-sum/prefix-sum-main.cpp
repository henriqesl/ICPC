// Aplicação: responder muitas somas de intervalos [l, r].
// Use quando o vetor não muda depois da leitura e há várias consultas.
// Complexidade: O(N) para construir + O(1) por consulta; memória O(N).
// Entrada: N, valores, Q e Q pares l r inclusivos, base zero.
// Ex.: 3 2 -1 4 2 0 2 1 1 -> 5 / -1.
// Exige 0 <= l <= r < N; somas intermediárias devem caber em long long.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, queries;
    cin >> n;
    // prefix[i] guarda a soma dos elementos antes do índice i.
    vector<long long> prefix(n + 1);

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix[i + 1] = prefix[i] + x;
    }

    cin >> queries;
    while (queries--) {
        int l, r;
        cin >> l >> r;
        // A soma [l, r] é a diferença entre dois prefixos.
        cout << prefix[r + 1] - prefix[l] << '\n';
    }
}
