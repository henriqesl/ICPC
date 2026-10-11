// PILHA MONOTÔNICA: menor estrito à esquerda/direita.
// Entrada: n; n valores. Saída: índices base 0; -1 se ausente.
// O(N) tempo/memória; guarda índices, não só valores.
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> valores(n), esquerda(n, -1), direita(n, -1);
    for (int i = 0; i < n; i++) cin >> valores[i];

    stack<int> candidatos;
    for (int i = 0; i < n; i++) {
        // Descarta >=; sobra menor estrito.
        while (!candidatos.empty() && valores[candidatos.top()] >= valores[i]) {
            candidatos.pop();
        }
        if (!candidatos.empty()) esquerda[i] = candidatos.top();
        candidatos.push(i);
    }

    while (!candidatos.empty()) candidatos.pop(); // reinicia para o outro lado
    for (int i = n - 1; i >= 0; i--) {
        while (!candidatos.empty() && valores[candidatos.top()] >= valores[i]) {
            candidatos.pop();
        }
        if (!candidatos.empty()) direita[i] = candidatos.top();
        candidatos.push(i);
    }

    for (int i : esquerda) cout << i << ' ';
    cout << '\n';
    for (int i : direita) cout << i << ' ';
    cout << '\n';
    // Maior estrito: descarte <=. Menor ou igual: descarte >.
    // Soma de mínimos: empate exige estrito num lado, não estrito no outro.
    // Aqui só encontra vizinhos; não soma contribuições.
}
