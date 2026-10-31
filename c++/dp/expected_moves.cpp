// POU: memo[i] = jogadas esperadas para ir de i até n, como na aula.
// Entrada: n >= 0 e k >= 1; fica parado com probabilidade 1/k.
// Saída: esperança com 10 casas; INF se k=1 e ainda precisa avançar.
// O(N) tempo/memória/pilha. Para N grande, há a fórmula n*k/(k-1), k>1.
#include <bits/stdc++.h>
using namespace std;
int n;
double k;
vector<double> memo;

double solve(int i) {
    if (i == n) return 0;
    if (memo[i] >= 0) return memo[i];
    return memo[i] = k / (k - 1) + solve(i + 1);
}

int main() {
    cin >> n >> k;
    if (n > 0 && k == 1) {
        cout << "INF\n";
        return 0;
    }
    memo.assign(n, -1);
    cout << fixed << setprecision(10) << solve(0) << '\n';
}

/*
COMO LER ESTE CÓDIGO
E(i)=1+(1/k)E(i)+(1-1/k)E(i+1): jogada atual, ficar e avançar.
Isolando E(i), obtemos k/(k-1)+E(i+1). Não chame solve(i) dentro dele mesmo:
isso não termina só por haver memo. E(n)=0; com n=3,k=2, a esperança é 6.
k é double para a divisão não ser inteira. Se k=1, nunca avançamos.
*/
