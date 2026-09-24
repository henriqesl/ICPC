// Aplicação: conta a frequência de cada número.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> frequency;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        frequency[x]++;
    }

    for (auto [value, amount] : frequency)
        cout << value << ": " << amount << '\n';
}

