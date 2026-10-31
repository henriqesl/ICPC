// FIBONACCI BRUTO: mostra estados repetidos, sem memoização.
// Entrada: 0 <= n <= 35. Saída: F(n), sem módulo.
// O(2^N) tempo (limite superior), O(N) pilha. Só para estudo/N pequeno.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(int n) {
    if (n <= 1) return n;
    return solve(n - 1) + solve(n - 2);
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << '\n';
}

/*
COMO LER ESTE CÓDIGO
solve(n) soma os dois anteriores; 0 e 1 encerram a recursão.
Para F(5), F(3) aparece tanto no ramo de F(4) quanto no de F(3).
Recalcular esses ramos causa o custo exponencial; veja fibonacci_memo.cpp.
*/
