// DICE BRUTO: sequências ordenadas de faces 1..6 somando n.
// Entrada: 0 <= n <= 20, para estudo. Saída: quantidade mod 1e9+7.
// O(6^N) tempo (limite superior), O(N) pilha; sem cache.
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int solve(int sum) {
    if (sum == 0) return 1;
    if (sum < 0) return 0;
    int ans = 0;
    for (int face = 1; face <= 6; face++) {
        ans = (ans + solve(sum - face)) % MOD;
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << '\n';
}

/*
COMO LER ESTE CÓDIGO
sum é quanto falta. Escolher uma face leva a sum-face.
Zero retorna 1: completamos uma sequência; negativo retorna 0: ultrapassamos.
Para n=3, há 4 sequências: 111,12,21,3. A ordem importa.
O for só compacta as seis chamadas da recorrência; ele não evita recomputação.
*/
