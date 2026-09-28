// PILHA: o último que entra é o primeiro que sai (LIFO).
// Aplicação: delimitadores; o último aberto precisa fechar primeiro.
// Entrada: uma sequência SEM espaços. ([{}]) -> balanceado; ([)] -> desbalanceado.
// Se o enunciado fornecer N antes da sequência, leia N também.
// Tempo O(N), memória O(N); saída pode ser adaptada para SIM/NAO.
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string texto;
    cin >> texto;
    stack<char> abertos;
    bool valido = true;

    for (char atual : texto) {
        if (atual == '(' || atual == '[' || atual == '{') {
            abertos.push(atual); // guarda abertura ainda pendente
        } else if (atual == ')' || atual == ']' || atual == '}') {
            if (abertos.empty()) { // tentou fechar sem ter aberto
                valido = false;
                break;
            }

            char topo = abertos.top(); // última abertura pendente
            bool combina = (topo == '(' && atual == ')') ||
                           (topo == '[' && atual == ']') ||
                           (topo == '{' && atual == '}');

            if (!combina) {
                valido = false;
                break;
            }
            abertos.pop(); // fechou corretamente; remove a abertura
        }
    }
    if (!abertos.empty()) valido = false; // sobraram aberturas
    if (valido) cout << "balanceado\n";
    else cout << "desbalanceado\n";
}
