// KNAPSACK 0/1: memo[i][cap] = maior valor dos itens i..n-1 com capacidade cap.
// Entrada: n W; n pares peso valor, não negativos. Saída: maior valor; soma cabe em ll.
// O(N*(W+1)) tempo/memória, pilha O(N). Capacidade precisa caber na tabela.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
vector<int> weight;
vector<ll> value;
vector<vector<ll>> memo;

ll solve(int i, int cap) {
    if (i == n) return 0;
    if (memo[i][cap] != -1) return memo[i][cap];
    ll ans = solve(i + 1, cap); // não pegar
    if (weight[i] <= cap) {
        ans = max(ans, value[i] + solve(i + 1, cap - weight[i]));
    }
    return memo[i][cap] = ans;
}

int main() {
    int capacity;
    cin >> n >> capacity;
    weight.resize(n);
    value.resize(n);
    for (int i = 0; i < n; i++) cin >> weight[i] >> value[i];
    memo.assign(n, vector<ll>(capacity + 1, -1));
    cout << solve(0, capacity) << '\n';
}

/*
COMO LER ESTE CÓDIGO
Há dois ramos: não pegar, ou pegar se couber. max escolhe o melhor valor.
Ambos avançam i: cada item só entra uma vez. A base é i==n, NÃO cap==0,
pois este exemplo também permite itens de peso zero com valor positivo.
Exemplo: itens (3,4),(4,5),(2,3),(6,7), capacidade 7 -> valor 9.
W enorme inviabiliza O(NW), mesmo com poucos itens: é custo pseudo-polinomial.
*/
