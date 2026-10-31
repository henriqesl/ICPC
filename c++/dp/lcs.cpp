// LCS: memo[i][j] = tamanho da maior subsequência comum de a[i..] e b[j..].
// Entrada: duas linhas (strings; podem ser vazias). Saída: tamanho, não a sequência.
// O(N*M+N+M) tempo, O(N*M) tabela + O(N+M) pilha. Não exige contiguidade.
#include <bits/stdc++.h>
using namespace std;
string a, b;
int n, m;
vector<vector<int>> memo;

int solve(int i, int j) {
    if (i == n || j == m) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (a[i] == b[j]) return memo[i][j] = 1 + solve(i + 1, j + 1);
    return memo[i][j] = max(solve(i + 1, j), solve(i, j + 1));
}

int main() {
    getline(cin, a);
    getline(cin, b);
    n = int(a.size());
    m = int(b.size());
    memo.assign(n, vector<int>(m, -1));
    cout << solve(0, 0) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Quando um sufixo termina, não há mais caracteres para combinar: retorna 0.
Iguais: usamos o caractere e avançamos ambos. Diferentes: pulamos em a OU b
e escolhemos max. Não somamos as duas opções.
ABCDGH e AEDFHR têm LCS de tamanho 3 (ADH). Podemos pular letras, não trocar sua ordem.
LPS: o TAMANHO da maior subsequência palíndroma de s é LCS(s,reversa(s)).
*/
