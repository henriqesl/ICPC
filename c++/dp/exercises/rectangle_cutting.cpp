// RECTANGLE CUTTING: memo[a][b] = mínimo de cortes para obter só quadrados.
// Entrada: a b positivos. Saída: mínimo; cada corte separa um retângulo em dois.
// O(A*B*(A+B)) tempo, O(A*B) tabela, pilha O(A+B); dimensões pequenas.
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> memo;

int solve(int a, int b) {
    if (a == b) return 0;
    if (memo[a][b] != -1) return memo[a][b];
    int ans = INT_MAX / 2;
    for (int i = 1; i < a; i++) {
        ans = min(ans, 1 + solve(i, b) + solve(a - i, b));
    }
    for (int i = 1; i < b; i++) {
        ans = min(ans, 1 + solve(a, i) + solve(a, b - i));
    }
    return memo[a][b] = ans;
}

int main() {
    int a, b;
    cin >> a >> b;
    memo.assign(a + 1, vector<int>(b + 1, -1));
    cout << solve(a, b) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Quadrado já está pronto: zero cortes. Caso contrário, testamos cada divisão.
Para UMA divisão, somamos as respostas das duas partes e +1 do corte atual.
Entre divisões DIFERENTES, escolhemos min, não somamos todas as possibilidades.
Exemplo: 2x3 precisa de 2 cortes para formar um 2x2 e dois 1x1.
*/
