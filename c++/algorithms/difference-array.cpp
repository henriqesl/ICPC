// DIFERENÇAS: adicionar em intervalos; consultar só no final.
// Entrada: n q; n valores; q linhas L R incremento (base 0, inclusivos).
// O(N+Q) tempo, O(N) memória. 0 <= L <= R < N; somas cabem em long long.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    vector<long long> diferenca(n + 1, 0); // permite R+1 == N

    for (int i = 0; i < q; i++) {
        int l, r;
        long long incremento;
        cin >> l >> r >> incremento;
        diferenca[l] += incremento;     // + em L
        diferenca[r + 1] -= incremento; // - em R+1
    }

    long long acumulado = 0;
    for (int i = 0; i < n; i++) {
        acumulado += diferenca[i]; // prefix sum das alterações
        cout << valores[i] + acumulado << ' ';
    }
    cout << '\n';
}
