// FROG 1 BOTTOM-UP: mesma DP de frog_1.cpp, começando da pedra 0.
// Entrada: n >= 1; n alturas. Saída: custo mínimo; somas/diferenças cabem em ll.
// O(N) tempo/memória; sem recursão.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> h(n), dp(n, 0);
    for (ll &x : h) cin >> x;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    cout << dp[n - 1] << '\n';
}

/*
COMO LER ESTE CÓDIGO
dp[0]=0. Ao calcular i, as duas pedras anteriores já têm seus custos prontos.
O min escolhe a melhor chegada; não somamos os custos de todas as opções.
É uma alternativa explícita à versão recursiva, com a mesma resposta.
*/
