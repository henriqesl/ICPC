// SUBSET SUM: memo[i][sum] = existe solução com os itens i..n-1 faltando sum?
// Entrada: n target; n inteiros NÃO NEGATIVOS. Saída: SIM/NAO.
// O(N*(target+1)) tempo/memória, pilha O(N). Escolhe cada índice no máximo uma vez.
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> a;
vector<vector<int>> memo;

int solve(int i, int sum) {
    if (sum == 0) return 1;
    if (i == n || sum < 0) return 0;
    if (memo[i][sum] != -1) return memo[i][sum];
    return memo[i][sum] = solve(i + 1, sum) || solve(i + 1, sum - a[i]);
}

int main() {
    int target;
    cin >> n >> target;
    a.resize(n);
    for (int &x : a) cin >> x;
    memo.assign(n, vector<int>(target + 1, -1));
    cout << (solve(0, target) ? "SIM" : "NAO") << '\n';
}

/*
COMO LER ESTE CÓDIGO
O primeiro ramo não pega a[i]; o segundo pega e desconta seu valor do que falta.
OR (||) basta porque buscamos existência, não quantidade. sum==0 aceita o vazio.
As bases vêm antes de memo[i][sum], evitando acessar n ou uma soma negativa.
Exemplo: [3,4,5], alvo 9 -> SIM, pegando 4 e 5. Só memo[i] não descreveria o estado.
*/
