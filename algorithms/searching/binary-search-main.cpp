// Aplicação: encontrar a primeira posição com valor >= x.
// Use quando o vetor está ordenado ou quando a resposta é monotônica.
// Complexidade: O(log N) tempo e O(1) memória.
#include <bits/stdc++.h>
using namespace std;

int first_at_least(const vector<int>& v, int x) {
    int lo = 0, hi = int(v.size());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2; // evita overflow de lo + hi
        if (v[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int& value : v) cin >> value;
    cin >> x;

    int index = first_at_least(v, x);
    cout << (index == n ? -1 : index) << '\n';
}
