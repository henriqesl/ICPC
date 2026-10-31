// DICE BOTTOM-UP: dp[sum] = sequências ordenadas que somam sum.
// Entrada: n >= 0. Saída: quantidade mod 1e9+7.
// O(6N)=O(N) tempo, O(N) memória; sem recursão, serve para N grande.
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int sum = 1; sum <= n; sum++) {
        for (int face = 1; face <= 6; face++) {
            if (sum >= face) dp[sum] = (dp[sum] + dp[sum - face]) % MOD;
        }
    }
    cout << dp[n] << '\n';
}

/*
COMO LER ESTE CÓDIGO
dp[0]=1 representa a sequência vazia; ela permite começar novas sequências.
Para cada soma, escolhemos qual foi a última face e somamos dp[sum-face].
O laço externo nas somas conta ORDENS; trocar os laços muda o problema.
*/
