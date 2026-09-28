// MULTISET: valores ordenados, permitindo duplicatas.
// Entrada: N, N valores e X para remover UMA ocorrência.
// Ex.: 5 3 1 3 8 3 3 -> 1 3 3 8.
// Inserção/busca O(log N), memória O(N); percurso da saída O(N).
// Após a lista: "menor=X maior=Y" (ou "vazio") e "restantes=K" do valor removido.
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
    // Cuidado: valores.erase(remover) removeria TODAS as ocorrências!
    // count(x) custa O(log N + quantidade encontrada), não só O(log N).

    for (int x : valores) cout << x << ' ';
    cout << '\n';

    if (!valores.empty()) {
        cout << "menor=" << *valores.begin();
        cout << " maior=" << *valores.rbegin() << '\n';
    } else cout << "vazio\n";
    cout << "restantes=" << valores.count(remover) << '\n';

    // begin/rbegin: menor/maior em O(1). Não leia end nem conjunto vazio.
    // prev(valores.end()) também dá o último (<iterator>), somente se não vazio.
    // [lower_bound(X), upper_bound(X)) contém todas as ocorrências de X.
    // Para apagar esse intervalo:
    // valores.erase(valores.lower_bound(X), valores.upper_bound(X));
    // Custo O(log N + quantidade removida); erase(X) também apaga todas.
    // Não use upper-lower: iteradores de multiset não suportam subtração.
    // Veja ../algorithms/bounds.cpp para buscas com ausência tratada.
}
