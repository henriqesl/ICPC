// PADRÃO: primeiro MENOR ESTRITO à esquerda e à direita de cada posição.
// Entrada: N e N inteiros. Ex.: 3 3 1 2
// Saída (índices base zero; -1 se ausente): -1 -1 1 / 1 -1 -1.
// Tempo O(N), memória O(N). Cada índice entra/sai uma vez em cada percurso.
// Guarde ÍNDICES: os valores servem para comparar; as posições são a resposta.
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
        // >= não serve como MENOR ESTRITO; descarte até sobrar um menor.
        while (!candidatos.empty() && valores[candidatos.top()] >= valores[i]) {
            candidatos.pop();
        }
        if (!candidatos.empty()) esquerda[i] = candidatos.top();
        candidatos.push(i);
    }

    while (!candidatos.empty()) candidatos.pop(); // outro lado começa vazio
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
    // Maior estrito: troque >= por <=. Menor ou igual: troque >= por >.
    // Para somar contribuições de mínimos, NÃO use estrito dos dois lados:
    // empates precisam de menor estrito num lado e menor ou igual no outro.
    // Nesse outro lado, a condição de DESCARTE seria >, não >=. Veja patterns.md.
    // Este exemplo só encontra vizinhos; não resolve a soma de subarrays.
}
