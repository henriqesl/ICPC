// LIS TOP-DOWN: complemento da aula; subsequência estritamente crescente.
// Entrada: n >= 0; n valores. Saída: tamanho. Estado (i,prev), prev=-1 no início.
// O(N²) tempo/memória, pilha O(N). Esta é a DP didática, não a versão O(N log N).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<ll> a;
vector<vector<int>> memo;

int solve(int i, int prev) {
    if (i == n) return 0;
    if (memo[i][prev + 1] != -1) return memo[i][prev + 1];
    int ans = solve(i + 1, prev);
    if (prev == -1 || a[i] > a[prev]) ans = max(ans, 1 + solve(i + 1, i));
    return memo[i][prev + 1] = ans;
}

int main() {
    cin >> n;
    a.resize(n);
    for (ll &x : a) cin >> x;
    memo.assign(n, vector<int>(n + 1, -1));
    cout << solve(0, -1) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Podemos ignorar i, ou pegá-lo se for maior que o último escolhido.
prev guarda o ÍNDICE anterior, não seu valor. -1 permite qualquer primeira escolha;
prev+1 desloca a coluna do memo para nunca acessar índice negativo.
[10,2,5,3,7,18] tem resposta 4. Valores iguais não aumentam uma LIS estrita.
*/
