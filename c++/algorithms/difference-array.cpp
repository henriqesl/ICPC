// DIFFERENCE ARRAY: muitas SOMAS em intervalos, só consulta o resultado no FINAL.
// Entrada: N Q, N valores iniciais e Q linhas L R incremento (base zero inclusiva).
// Ex.: 4 2 1 2 3 4 0 2 10 1 3 -2 -> 11 10 11 2.
// Exige 0 <= L <= R < N; acumulados cabem em long long.
// Tempo O(N+Q), memória O(N). Não resolve consultas intercaladas em O(1).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    vector<long long> diferenca(n + 1, 0); // posição extra permite R+1 == N

    for (int i = 0; i < q; i++) {
        int l, r;
        long long incremento;
        cin >> l >> r >> incremento;
        diferenca[l] += incremento;     // começa a somar aqui
        diferenca[r + 1] -= incremento; // para de somar depois do intervalo
    }

    long long acumulado = 0;
    for (int i = 0; i < n; i++) {
        acumulado += diferenca[i]; // prefix sum das alterações
        cout << valores[i] + acumulado << ' ';
    }
    cout << '\n';
    // Prefix sum original: soma de intervalos em valores fixos.
    // Diferenças: adicionar a intervalos e reconstruir tudo no final.
}
