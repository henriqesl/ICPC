// Aplicação: sempre processar primeiro o maior valor disponível.
// Use em prioridades, maiores pontuações, tarefas urgentes ou top K.
// Para obter o menor no topo: priority_queue<int, vector<int>, greater<int>>.
// Complexidade: push/pop O(log N), top O(1).
// Entrada: N e N inteiros. Ex.: 3 2 9 4 -> 9 4 2.
// Total O(N log N), memória O(N); extrações consomem a estrutura.
// Use para chegadas/remoções intercaladas; só ordenar é mais simples com sort.
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
