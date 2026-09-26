// Aplicação: encontrar a primeira posição com valor >= x.
// Use quando o vetor está ordenado ou quando a resposta é monotônica.
// Complexidade: O(log N) tempo e O(1) memória.
// Entrada: N, N inteiros ORDENADOS e alvo. Ex.: 4 1 3 3 8 3 -> 1.
// Índice base zero do primeiro >= alvo; -1 na saída se ausente.
// A função retorna size() se ausente; cheque antes de acessar.
// Esta função exige vetor crescente; predicados monotônicos exigem adaptação.
// O(log N)/O(1) é só busca; leitura e armazenamento O(N).
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
