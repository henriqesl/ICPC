// JOGO DA AULA: de i, retire 1..floor((i+1)/2); quem não pode jogar perde.
// Entrada: n >= 0. Saída: VENCEDOR ou PERDEDOR para quem joga agora.
// O(N²) tempo, O(N) memória; versão direta, sem a otimização de janela.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, 0); // dp[0]=0: perdedor
    for (int i = 1; i <= n; i++) {
        for (int take = 1; take <= (i + 1) / 2; take++) {
            if (dp[i - take] == 0) {
                dp[i] = 1;
                break;
            }
        }
    }
    cout << (dp[n] ? "VENCEDOR" : "PERDEDOR") << '\n';
}

/*
COMO LER ESTE CÓDIGO
dp[i] se refere ao jogador da vez. Uma jogada vencedora deixa o adversário
num estado perdedor; basta existir uma. Se todas levam a vencedor, perdemos.
Exemplo: dp[0]=0, dp[1]=1, dp[2]=0. As jogadas permitidas dependem do enunciado.
*/
