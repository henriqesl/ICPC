// Aplicação: verificar parênteses, colchetes e chaves balanceados.
// Use stack porque o último símbolo aberto deve ser o primeiro a fechar.
// Complexidade: O(N) tempo e O(N) memória.
// Entrada: expressão SEM espaços. Ex.: ([{}]) -> balanceado; ([)] -> desbalanceado.
// Use getline para linha inteira. A função aceita vazio e ignora outros caracteres.
#include <bits/stdc++.h>
using namespace std;

bool balanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            char open = st.top(); // compara com o fechamento atual
            st.pop();
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) return false;
        }
    }
    return st.empty();
}

int main() {
    string expression;
    cin >> expression;
    cout << (balanced(expression) ? "balanceado" : "desbalanceado") << '\n';
}
