// Aplicação: responde soma de intervalos [l, r].
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, queries;
    cin >> n;
    vector<long long> prefix(n + 1);

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix[i + 1] = prefix[i] + x;
    }

    cin >> queries;
    while (queries--) {
        int l, r;
        cin >> l >> r;
        cout << prefix[r + 1] - prefix[l] << '\n';
    }
}

