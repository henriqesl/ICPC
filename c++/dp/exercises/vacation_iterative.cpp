// VACATION BOTTOM-UP: mesma definição de estado da versão memoizada.
// Entrada: n >= 0; n linhas A B C, pontos não negativos. Saída: maior felicidade.
// O(N) tempo/memória; totais cabem em ll. Sem recursão.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<vector<ll>> points(n, vector<ll>(3));
    for (auto &day : points) for (ll &x : day) cin >> x;
    vector<vector<ll>> dp(n + 1, vector<ll>(4, 0));
    for (int day = n - 1; day >= 0; day--) {
        for (int last = 0; last < 4; last++) {
            for (int activity = 0; activity < 3; activity++) {
                if (activity != last) {
                    dp[day][last] = max(dp[day][last], points[day][activity] + dp[day + 1][activity]);
                }
            }
        }
    }
    cout << dp[0][3] << '\n';
}

/*
COMO LER ESTE CÓDIGO
dp[n][last]=0: não há mais dias. Calculamos de trás para frente porque
dp[day][last] usa o dia SEGUINTE. Os estados são iguais aos da recursão.
Não é escolher todo dia o maior ponto: a escolha de hoje restringe amanhã.
*/
