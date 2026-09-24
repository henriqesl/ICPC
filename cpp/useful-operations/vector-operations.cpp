// Aplicação: operações básicas com vector.
// Entrada: n, os n valores e um valor x.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int& value : v) cin >> value;
    cin >> x;

    auto it = find(v.begin(), v.end(), x);
    int index = it == v.end() ? -1 : int(it - v.begin());

    cout << "indice=" << index << '\n';
    cout << "ocorrencias=" << count(v.begin(), v.end(), x) << '\n';

    sort(v.begin(), v.end());
    for (int value : v) cout << value << ' ';
    cout << '\n';
}

