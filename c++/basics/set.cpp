// SET: valores únicos, automaticamente em ordem crescente.
// Entrada: N e N inteiros. 4 3 1 3 8 -> 1 3 8.
// Use para distintos; se precisa de duplicatas, use multiset ou frequências.
// Inserção/busca O(log(K+1)), memória O(K).
// Depois da lista: "menor=X maior=Y", ou "vazio".
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
        valores.insert(x); // inserir 3 duas vezes mantém só um 3
    }

    for (int x : valores) cout << x << ' ';
    cout << '\n';

    // begin() aponta para o primeiro; rbegin() aponta para o último.
    // * lê o valor. No set crescente, são menor e maior, em O(1).
    if (!valores.empty()) {
        cout << "menor=" << *valores.begin();
        cout << " maior=" << *valores.rbegin() << '\n';
    } else cout << "vazio\n";

    // end() fica DEPOIS do último. *end() é inválido!
    // prev(valores.end()) também aponta para o último (<iterator>), se não vazio.
    // Remover menor: if (!valores.empty()) valores.erase(valores.begin());
    // Remover maior: if (!valores.empty()) valores.erase(prev(valores.end()));
    // erase invalida só o iterador removido. Ao percorrer, use it = valores.erase(it).

    // valores.count(3) retorna 0 ou 1: existe ou não existe.
    // valores.erase(3) remove o 3 se existir.
    // auto it = valores.lower_bound(5); primeiro valor >= 5.
    // if (it != valores.end()) cout << *it; (*it lê o elemento apontado).
    // Set NÃO tem valores[i]. Para menor: *begin(), somente se não vazio.
    // lower_bound(x): primeiro >= x; upper_bound(x): primeiro > x.
    // Exemplo completo de vizinhos: ../algorithms/bounds.cpp.
    // Decrescente: for (auto it = valores.rbegin(); it != valores.rend(); ++it)
    //                  cout << *it << ' ';
    // size() conta distintos; empty() testa vazio; clear() remove todos.
}
