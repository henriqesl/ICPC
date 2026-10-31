// DICE TOP-DOWN: memo[sum] = sequências de faces 1..6 com soma sum.
// Entrada: n >= 0. Saída: quantidade mod 1e9+7; a ordem importa.
// O(6N)=O(N) tempo, O(N) memória/pilha. N grande: use o arquivo iterative.
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
vector<int> memo;

int solve(int sum) {
    if (sum == 0) return 1;
    if (sum < 0) return 0;
    if (memo[sum] != -1) return memo[sum];
    int ans = 0;
    for (int face = 1; face <= 6; face++) {
        ans = (ans + solve(sum - face)) % MOD;
    }
    return memo[sum] = ans;
}

int main() {
    int n;
    cin >> n;
    memo.assign(n + 1, -1);
    cout << solve(n) << '\n';
}

/*
COMO LER ESTE CÓDIGO
As bases vêm antes de acessar memo, inclusive para sum negativo.
Cada soma é resolvida uma vez; cada estado tenta só as seis faces.
Aplicamos MOD a cada soma. Para n=3, a resposta é 4, contando 12 e 21 separados.
A memoização reduz o trabalho, mas não a profundidade da recursão O(N).
*/
