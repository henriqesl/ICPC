// SET: únicos ordenados; não tem s[i].
// Entrada: n; n valores. Saída: distintos; extremos ou "vazio".
// O(log D) inserir/find/bounds, O(D) memória; D distintos.
// begin/rbegin: menor/maior, só se não vazio. end não é elemento.
#include <iostream>
#include <iterator> // prev: aponta para o elemento anterior
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> valores;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        valores.insert(x);
    }

    for (int x : valores) cout << x << ' ';
    cout << '\n';

    // Extremos O(1).
    if (!valores.empty()) {
        cout << "menor=" << *valores.begin();
        cout << " maior=" << *valores.rbegin() << '\n';
    } else cout << "vazio\n";

    // Último: prev(valores.end()), só se não vazio.
    // Menor: if (!valores.empty()) valores.erase(valores.begin());
    // Maior: if (!valores.empty()) valores.erase(prev(valores.end()));
    // Percurso com remoção: it = valores.erase(it); não ++it depois.
    // count(3): presença 0/1; erase(3): remove; size(): distintos; clear(): zera.
    // auto it = valores.lower_bound(5); // primeiro >= 5
    // if (it != valores.end()) cout << *it;
    // upper_bound(5): primeiro > 5. Vizinhos: ../algorithms/bounds.cpp.
    // Reverso: for (auto it=valores.rbegin(); it!=valores.rend(); ++it) cout << *it;
}
