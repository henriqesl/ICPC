// KADANE: maior soma de subarray CONTÍGUO, não vazio; aceita negativos.
// Entrada: n >= 1; n inteiros. Saída: maior soma; somas cabem em ll.
// O(N) tempo, O(1) memória; DP comprimida em curr e ans.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    ll curr;
    cin >> curr;
    ll ans = curr;
    for (int i = 1; i < n; i++) {
        ll x;
        cin >> x;
        curr = max(x, curr + x);
        ans = max(ans, curr);
    }
    cout << ans << '\n';
}

/*
COMO LER ESTE CÓDIGO
curr é a melhor soma que TERMINA aqui: começamos em x ou estendemos a anterior.
ans é a melhor entre TODAS as posições. Só precisamos do curr anterior.
Começamos no primeiro valor, não em zero: [-5,-2,-8] responde -2, não 0.
Para [-2,1,-3,4,-1,2,1,-5,4], a resposta é 6, do trecho [4,-1,2,1].
*/
