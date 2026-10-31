// RECONSTRUIR LCS: calcula comprimentos e segue uma transição ótima.
// Entrada: duas linhas, podem ser vazias. Saída: tamanho e uma LCS na linha seguinte.
// O(N*M+N+M) tempo, O(N*M) tabela + O(N+M) pilha/resultado; empates aceitam qualquer LCS.
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

    string answer;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            answer += a[i];
            i++;
            j++;
        } else if (solve(i + 1, j) >= solve(i, j + 1)) {
            i++;
        } else {
            j++;
        }
    }
    cout << answer << '\n';
}

/*
COMO LER ESTE CÓDIGO
Iguais entram na resposta e avançam os dois índices. Diferentes seguem o vizinho
com maior comprimento ótimo; no empate, qualquer lado preserva o tamanho.
Chamamos solve em vez de ler memo cru porque nem todo vizinho foi visitado antes.
Exemplo: ABCDGH e AEDFHR -> 3 e ADH. Pode haver outras respostas ótimas.
Para LPS via reversa, use o COMPRIMENTO: uma LCS arbitrária não é garantia de palíndromo.
*/
