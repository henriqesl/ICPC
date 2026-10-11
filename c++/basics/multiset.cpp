// MULTISET: ordenado, preserva cópias; erase(it) remove uma.
// Entrada: n; n valores; X. Remove um X; imprime lista/extremos/restantes.
// O(log N) inserir/find; count O(log N+C); O(N) memória.
// erase(X) apaga TODAS as C cópias. Não leia extremos vazios.
#include <iostream>
#include <iterator> // prev e distance
#include <set> // multiset também fica em <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int> valores;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        valores.insert(x);
    }

    int remover;
    cin >> remover;
    auto it = valores.find(remover); // aponta para uma ocorrência
    if (it != valores.end()) {
        valores.erase(it); // remove SOMENTE essa ocorrência
    }

    for (int x : valores) cout << x << ' ';
    cout << '\n';

    if (!valores.empty()) {
        cout << "menor=" << *valores.begin();
        cout << " maior=" << *valores.rbegin() << '\n';
    } else cout << "vazio\n";
    cout << "restantes=" << valores.count(remover) << '\n';

    // begin/rbegin: menor/maior O(1); prev(end()) também dá último, se não vazio.
    // [lower_bound(X),upper_bound(X)): cópias de X; não use upper-lower.
    // valores.erase(valores.lower_bound(X), valores.upper_bound(X)); // todas
    // Apagar C cópias: O(log N+C). Vizinhos: ../algorithms/bounds.cpp.
}
