// BOUNDS: lower >= X; upper > X. Nunca leia *end().
// Entrada: n; n valores; X L R (L <= R). Ordena a entrada.
// Saída: índices lower/upper; contagens; vizinhos ou "nenhum".
// O(N log N) preparo, O(log N) busca, O(N) memória.
// Vector: it-begin() dá índice; set/multiset: use os métodos.
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

    // Vector ordenado: diferença de iteradores O(1).
    auto inferior = lower_bound(valores.begin(), valores.end(), x); // primeiro >= x
    auto superior = upper_bound(valores.begin(), valores.end(), x); // primeiro > x
    int primeiroIndice = int(inferior - valores.begin());
    int depoisDoUltimo = int(superior - valores.begin());
    cout << "lower=" << primeiroIndice << " upper=" << depoisDoUltimo << '\n';
    // Igualdade: inferior != valores.end() && *inferior == x.

    auto inicio = lower_bound(valores.begin(), valores.end(), l);
    auto fim = upper_bound(valores.begin(), valores.end(), r);
    cout << "iguais=" << superior - inferior; // diferença O(1) no vector
    cout << " intervalo=" << fim - inicio << '\n'; // quantidade em [L,R]

    // Set/multiset: métodos O(log N), sem subtração de iteradores.
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

    // Nunca prev(begin()) ou *end(). distance no multiset: O(K) passos.
    // lower_bound genérico em set/multiset pode andar O(N).
}
