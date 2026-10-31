// VACATION TOP-DOWN: memo[day][last] = maior felicidade dos dias day..n-1.
// Entrada: n >= 0; n linhas A B C, pontos NÃO NEGATIVOS. Não repete atividade seguida.
// Saída: felicidade máxima; total cabe em ll. O(N) tempo/memória/pilha.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<vector<ll>> points, memo;

ll solve(int day, int last) {
    if (day == n) return 0;
    if (memo[day][last] != -1) return memo[day][last];
    ll ans = 0;
    for (int activity = 0; activity < 3; activity++) {
        if (activity != last) ans = max(ans, points[day][activity] + solve(day + 1, activity));
    }
    return memo[day][last] = ans;
}

int main() {
    cin >> n;
    points.assign(n, vector<ll>(3));
    for (auto &day : points) for (ll &x : day) cin >> x;
    memo.assign(n, vector<ll>(4, -1));
    cout << solve(0, 3) << '\n'; // 3 = nenhuma atividade anterior
}

/*
COMO LER ESTE CÓDIGO
day sozinho não basta: last muda quais atividades ainda são permitidas.
Testamos as três menos last, somamos os pontos de hoje e escolhemos max.
O last especial 3 permite qualquer atividade no primeiro dia, por isso há 4 colunas.
Exemplo: dias [10,40,70] e [20,50,80] -> 120, escolhendo C e B ou B e C.
N grande pode exceder a pilha; vacation_iterative.cpp é a alternativa separada.
*/
