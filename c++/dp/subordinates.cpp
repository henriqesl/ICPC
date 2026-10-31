// ÁRVORE: memo[u] = tamanho da subárvore de u, incluindo u.
// Entrada: n >= 1; chefes dos funcionários 2..n. Raiz 1; hierarquia válida.
// Saída: subordinados de cada funcionário, sem contar ele mesmo.
// O(N) tempo/memória; DFS recursiva, cuidado com cadeia muito profunda.
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> children;
vector<int> memo;

int solve(int u) {
    if (memo[u] != -1) return memo[u];
    int ans = 1;
    for (int v : children[u]) ans += solve(v);
    return memo[u] = ans;
}

int main() {
    int n;
    cin >> n;
    children.resize(n + 1);
    memo.assign(n + 1, -1);
    for (int u = 2; u <= n; u++) {
        int boss;
        cin >> boss;
        children[boss].push_back(u);
    }
    solve(1);
    for (int u = 1; u <= n; u++) cout << memo[u] - 1 << ' ';
    cout << '\n';
}

/*
COMO LER ESTE CÓDIGO
Uma folha retorna 1: ela própria. O pai soma as subárvores dos filhos e mais 1.
solve(1) preenche todos os estados; subtraímos 1 só na saída para excluir o chefe.
Em uma árvore, cada filho já é explorado uma vez; memo guarda os resultados
para consulta, mas nem toda DP em árvore precisa evitar estados repetidos.
*/
