// Aplicação: ordenação crescente e decrescente.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;

    sort(v.begin(), v.end());
    for (int x : v) cout << x << ' ';
    cout << '\n';

    sort(v.rbegin(), v.rend());
    for (int x : v) cout << x << ' ';
    cout << '\n';
}

