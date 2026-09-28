// MULTISET: valores ordenados, permitindo duplicatas.
// Entrada: N, N valores e X para remover UMA ocorrência.
// Ex.: 5 3 1 3 8 3 3 -> 1 3 3 8.
// Inserção/busca O(log N), memória O(N); percurso da saída O(N).
#include <iostream>
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
}
