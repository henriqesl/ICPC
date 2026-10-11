// QUEUE: ordem de chegada (FIFO), sem prioridades.
// Entrada: n; n nomes sem espaços. Saída: um nome por linha.
// Push/front/pop O(1); total/memória O(N). Pop remove, não retorna.
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    queue<string> fila;

    for (int i = 0; i < n; i++) {
        string nome;
        cin >> nome;
        fila.push(nome);
    }

    while (!fila.empty()) {
        string proximo = fila.front();
        cout << proximo << '\n';

        fila.pop();
    }
    // Front/pop exigem não vazio.
}
