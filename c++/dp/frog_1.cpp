// FROG 1 TOP-DOWN: memo[i] = menor custo para chegar à pedra i, base 0.
// Entrada: n >= 1; n alturas. Salta 1 ou 2 pedras; custo abs(altura nova-antiga).
// Saída: custo até n-1. O(N) tempo/memória/pilha; diferenças/somas cabem em ll.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> h, memo;

ll solve(int i) {
    if (i == 0) return 0;
    if (memo[i] != -1) return memo[i];
    ll ans = solve(i - 1) + abs(h[i] - h[i - 1]);
    if (i >= 2) ans = min(ans, solve(i - 2) + abs(h[i] - h[i - 2]));
    return memo[i] = ans;
}

int main() {
    int n;
    cin >> n;
    h.resize(n);
    for (ll &x : h) cin >> x;
    memo.assign(n, -1);
    cout << solve(n - 1) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Para chegar a i, a última pedra foi i-1 ou i-2. Somamos o salto ao custo
de chegar à anterior e escolhemos min. Só i basta: alturas e saltos são fixos,
e o caminho anterior não altera as opções futuras. [10,30,40,20] -> custo 30.
Para N grande, a recursão pode estourar a pilha; há um arquivo iterative separado.
*/
