// Aplicação: remove duplicatas e mantém os valores ordenados.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> values;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        values.insert(x);
    }

    for (int x : values) cout << x << ' ';
    cout << '\n';
}

