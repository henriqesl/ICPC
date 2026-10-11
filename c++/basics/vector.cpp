// VECTOR: índice / contagem / sort / remoção / únicos.
// Entrada: n; n valores; X. Saída demonstrativa com rótulos.
// Find/count O(N); sort O(N log N); memória O(N).
// Índice original antes do sort; -1 se ausente. Nunca leia *end().
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cin >> x;

    // Find -> iterador; it-begin() -> índice.
    auto it = find(v.begin(), v.end(), x);

    int index = -1;
    if (it != v.end()) index = int(it - v.begin());

    cout << "indice=" << index << '\n';
    cout << "ocorrencias=" << count(v.begin(), v.end(), x) << '\n';

    sort(v.begin(), v.end()); // ordena o próprio vector
    for (int value : v) cout << value << ' ';
    cout << '\n';

    if (!v.empty()) {
        // Só são min/max porque ordenamos.
        cout << "primeiro=" << v.front() << " ultimo=" << v.back() << '\n';
    } else cout << "vazio\n";

    vector<int> semX = v; // cópia O(N); v não muda
    semX.erase(remove(semX.begin(), semX.end(), x), semX.end());
    cout << "sem_x:";
    for (int valor : semX) cout << ' ' << valor;
    cout << '\n';

    vector<int> distintos = v; // iguais estão juntos porque v está ordenado
    distintos.erase(unique(distintos.begin(), distintos.end()), distintos.end());
    cout << "distintos:";
    for (int valor : distintos) cout << ' ' << valor;
    cout << '\n';

    // remove/unique + erase: O(N). Unique só junta iguais consecutivos.
    // Insert: v.insert(v.begin()+i,x), 0 <= i <= size, O(N).
    // Erase: v.erase(v.begin()+i), 0 <= i < size, O(N).
    // Último: if (!v.empty()) v.pop_back(), O(1).
    // Reserve não muda size; resize muda. Crescer/erase pode invalidar iteradores.
}
