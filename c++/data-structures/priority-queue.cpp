// HEAP: retirar sempre o maior (padrão) / menor (greater).
// Entrada: n; n valores. Saída: decrescente, depois crescente.
// Top O(1); push/pop O(log N); total O(N log N), memória O(N).
// Sem erase(valor), find ou bounds; extração consome o heap.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int> pq; // max-heap
    priority_queue<int, vector<int>, greater<int>> minimo;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.push(x);
        minimo.push(x);
    }

    while (!pq.empty()) {
        int maior = pq.top();
        cout << maior << ' ';
        pq.pop();
    }
    cout << '\n';

    while (!minimo.empty()) {
        cout << minimo.top() << ' ';
        minimo.pop();
    }
    cout << '\n';
    // K maiores: min-heap, push(x); se size()>K, pop().
    // Consultar sem consumir: copie O(N). Top/pop exigem não vazio.
}
