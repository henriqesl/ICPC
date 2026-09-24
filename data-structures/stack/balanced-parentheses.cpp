// Função reutilizável para delimitadores balanceados.
// Use quando símbolos precisam ser fechados na ordem inversa da abertura.
// Tempo O(N), espaço O(N). Este arquivo não possui main().
#include <bits/stdc++.h>
using namespace std;

bool balanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            char open = st.top();
            st.pop();
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) return false;
        }
    }
    return st.empty();
}
