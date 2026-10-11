// STACK: última abertura fecha primeiro (LIFO).
// Entrada: delimitadores sem espaços. Saída: balanceado / desbalanceado.
// O(N) tempo/memória. Se houver N antes do texto, leia-o também.
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
            abertos.push(atual);
        } else if (atual == ')' || atual == ']' || atual == '}') {
            if (abertos.empty()) { // sem abertura
                valido = false;
                break;
            }

            char topo = abertos.top();
            bool combina = (topo == '(' && atual == ')') ||
                           (topo == '[' && atual == ']') ||
                           (topo == '{' && atual == '}');

            if (!combina) {
                valido = false;
                break;
            }
            abertos.pop();
        }
    }
    if (!abertos.empty()) valido = false; // faltou fechar
    if (valido) cout << "balanceado\n";
    else cout << "desbalanceado\n";
}
