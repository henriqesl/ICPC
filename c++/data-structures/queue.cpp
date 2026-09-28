// FILA: quem entra primeiro sai primeiro (FIFO).
// Use para atender pessoas na ordem de chegada, sem prioridades.
// Entrada: N e N nomes sem espaços. Ex.: 3 Ana Bia Caio
// Saída, uma pessoa por linha: Ana / Bia / Caio.
// Tempo total O(N), memória O(N). Cada push/front/pop é O(1).
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    // queue<string> significa "uma fila que guarda textos".
    queue<string> fila;

    for (int i = 0; i < n; i++) {
        string nome;
        cin >> nome;
        fila.push(nome); // entra no FINAL
    }
    // Estado após ler o exemplo: frente -> Ana, Bia, Caio <- final

    // empty() pergunta "está vazia?". ! significa "não".
    while (!fila.empty()) {
        string proximo = fila.front(); // CONSULTA Ana, ainda não remove
        cout << proximo << '\n';

        fila.pop(); // REMOVE Ana; agora Bia é a primeira
        // pop() não devolve a pessoa removida. Por isso lemos front() antes.
    }
    // Não use front() nem pop() quando a fila estiver vazia.
    // Métodos da STL (push/pop) são operações prontas, não funções que você cria.
}
