// BOUNDS: limites, ocorrências, vizinhos e quantidade em intervalo.
// Entrada: N, N inteiros (qualquer ordem), X, L e R, com L <= R.
// Ex.: 5 1 3 3 8 10 3 3 8
// Saída:
// lower=1 upper=3
// iguais=2 intervalo=3
// menor_que=1
// menor_igual=3
// maior_igual=3
// maior_que=8
// Ausência de vizinho é "nenhum"; índices pertencem ao vetor ORDENADO.
// Ordenar/construir O(N log N), memória O(N); cada busca O(log N).
#include <algorithm>
#include <iostream>
#include <iterator> // prev
#include <set>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> valores(n);
    for (int i = 0; i < n; i++) cin >> valores[i];
    int x, l, r;
    cin >> x >> l >> r;
    sort(valores.begin(), valores.end());

    // VECTOR: funções de <algorithm>, retorno é ITERADOR.
    auto inferior = lower_bound(valores.begin(), valores.end(), x); // primeiro >= x
    auto superior = upper_bound(valores.begin(), valores.end(), x); // primeiro > x
    int primeiroIndice = int(inferior - valores.begin());
    int depoisDoUltimo = int(superior - valores.begin());
    cout << "lower=" << primeiroIndice << " upper=" << depoisDoUltimo << '\n';
    // n é uma posição de inserção válida, mas valores[n] NÃO existe!
    // Para existência exata: inferior != valores.end() && *inferior == x.

    auto inicio = lower_bound(valores.begin(), valores.end(), l);
    auto fim = upper_bound(valores.begin(), valores.end(), r);
    cout << "iguais=" << superior - inferior; // diferença O(1) no vector
    cout << " intervalo=" << fim - inicio << '\n'; // quantidade em [L,R]

    // MULTISET: use os MÉTODOS para manter O(log N).
    // Em set, as mesmas consultas funcionam; só não haveria duplicatas.
    multiset<int> conjunto(valores.begin(), valores.end());
    auto primeiroGE = conjunto.lower_bound(x);
    auto primeiroGT = conjunto.upper_bound(x);

    cout << "menor_que=";
    if (primeiroGE == conjunto.begin()) cout << "nenhum";
    else cout << *prev(primeiroGE); // anterior ao primeiro >= x
    cout << '\n';

    cout << "menor_igual=";
    if (primeiroGT == conjunto.begin()) cout << "nenhum";
    else cout << *prev(primeiroGT); // anterior ao primeiro > x
    cout << '\n';

    cout << "maior_igual=";
    if (primeiroGE == conjunto.end()) cout << "nenhum";
    else cout << *primeiroGE;
    cout << '\n';

    cout << "maior_que=";
    if (primeiroGT == conjunto.end()) cout << "nenhum";
    else cout << *primeiroGT;
    cout << '\n';

    // Nunca use prev(begin()), nem *end(). As verificações tratam também vazio.
    // No set/multiset, não há it2-it1; distance(it1,it2) percorre O(K) elementos.
    // lower_bound(s.begin(),s.end(),x) genérico pode andar O(N) vezes.
    // s.lower_bound(x) usa a árvore e custa O(log N).
}
