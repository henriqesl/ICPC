// FIBONACCI BOTTOM-UP: começa nas bases e calcula em ordem crescente.
// Entrada: 0 <= n <= 92. Saída: F(n), sem módulo.
// O(N) tempo/memória. Usa tabela explícita para mostrar a tabulação.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> dp(n + 1, 0);
    if (n >= 1) dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n] << '\n';
}

/*
COMO LER ESTE CÓDIGO
dp[0]=0 e dp[1]=1 são conhecidos antes do laço.
Ao calcular i, i-1 e i-2 já estão prontos. Não há chamadas recursivas.
É a mesma DP do arquivo memo, apenas com outra ordem de cálculo.
*/
