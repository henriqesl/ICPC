// Aplicação: processar itens na ordem em que chegaram (FIFO).
// Use em simulações, BFS e problemas de atendimento sequencial.
// Complexidade: push/pop/front O(1).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    queue<string> q;

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        q.push(name); // entra no final da fila
    }

    while (!q.empty()) {
        cout << q.front() << '\n'; // sai o primeiro que entrou
        q.pop();
    }
}
