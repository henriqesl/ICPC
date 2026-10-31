// FIBONACCI TOP-DOWN: memo[n] = F(n); -1 significa não calculado.
// Entrada: 0 <= n <= 92. Saída: F(n), sem módulo; F(93) não cabe em ll.
// O(N) tempo/memória, incluindo pilha. Bases F(0)=0, F(1)=1.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> memo;

ll solve(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1) + solve(n - 2);
}

int main() {
    int n;
    cin >> n;
    memo.assign(n + 1, -1);
    cout << solve(n) << '\n';
}

/*
COMO LER ESTE CÓDIGO
A recorrência é a mesma da força bruta; só adicionamos a consulta e o armazenamento.
Um estado já resolvido retorna memo[n], sem abrir seus dois ramos novamente.
Exemplo: F(5)=5. O valor -1 é seguro porque Fibonacci nunca é negativo.
*/
