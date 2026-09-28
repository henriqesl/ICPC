// SET: valores únicos, automaticamente em ordem crescente.
// Entrada: N e N inteiros. 4 3 1 3 8 -> 1 3 8.
// Use para distintos; se precisa de duplicatas, use multiset ou frequências.
// Inserção/busca O(log(K+1)), memória O(K).
#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> valores;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        valores.insert(x); // inserir 3 duas vezes mantém só um 3
    }

    for (int x : valores) cout << x << ' ';
    cout << '\n';

    // valores.count(3) retorna 0 ou 1: existe ou não existe.
    // valores.erase(3) remove o 3 se existir.
    // auto it = valores.lower_bound(5); primeiro valor >= 5.
    // if (it != valores.end()) cout << *it; (*it lê o elemento apontado).
    // Set NÃO tem valores[i]. Para menor: *begin(), somente se não vazio.
}
