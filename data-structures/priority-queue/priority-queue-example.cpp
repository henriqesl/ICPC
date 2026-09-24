// Aplicação: sempre processar primeiro o maior valor disponível.
// Use em prioridades, maiores pontuações, tarefas urgentes ou top K.
// Para obter o menor no topo: priority_queue<int, vector<int>, greater<int>>.
// Complexidade: push/pop O(log N), top O(1).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int> pq;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.push(x); // o maior valor fica acessível por pq.top()
    }

    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << '\n';
}
