// Aplicação: processamento FIFO de pessoas em uma fila.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    queue<string> q;

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        q.push(name);
    }

    while (!q.empty()) {
        cout << q.front() << '\n';
        q.pop();
    }
}

