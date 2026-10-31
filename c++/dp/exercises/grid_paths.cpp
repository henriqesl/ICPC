// GRID PATHS: memo[row][col] = caminhos dessa célula até (n-1,n-1).
// Entrada: n >= 1; n linhas de n caracteres: '.' livre, '*' bloqueado.
// Saída: caminhos mod 1e9+7; só baixo/direita. O(N²) tempo/memória; pilha O(N).
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int n;
vector<string> grid;
vector<vector<int>> memo;

int solve(int row, int col) {
    if (row < 0 || row >= n || col < 0 || col >= n) return 0;
    if (grid[row][col] == '*') return 0;
    if (row == n - 1 && col == n - 1) return 1;
    if (memo[row][col] != -1) return memo[row][col];
    return memo[row][col] = (solve(row + 1, col) + solve(row, col + 1)) % MOD;
}

int main() {
    cin >> n;
    grid.resize(n);
    for (string &row : grid) cin >> row;
    memo.assign(n, vector<int>(n, -1));
    cout << solve(0, 0) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Verificamos limites ANTES de ler grid ou memo. Parede retorna 0 mesmo no destino.
Chegar ao destino livre retorna 1; fora dele, somamos caminhos por baixo e direita.
Um grid 2x2 livre tem 2 caminhos. Não há ciclos porque cada passo aumenta row ou col.
São N² estados, mas uma cadeia recursiva tem até 2N-1 células; atenção à pilha.
*/
