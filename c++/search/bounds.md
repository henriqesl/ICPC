# BOUNDS — presença, limites e contagem

[Índice](README.md) · [Busca manual](binary-search.md) · [Iteradores](../basics/iterators.md)

## NECESSIDADE / RECONHECIMENTO

Vetor **ordenado crescente**; quero presença, primeiro >=, primeiro > ou número de repetições.
Os limites descrevem posições de inserção: **não garantem igualdade com o alvo**.

## IDEIA / EXEMPLO

```text
índice: 0  1  2  3  4  5     6 = end()
vetor: [1, 2, 2, 2, 5, 8]

alvo 2: lower → índice 1; upper → índice 4; quantidade → 4 - 1 = 3
alvo 3: lower → índice 4; upper → índice 4; quantidade → 0
alvo 9: lower → índice 6; upper → índice 6; nenhum elemento válido
```

### binary_search — existe x?

Retorna **bool**, não iterador nem índice.

<a id="lower-bound"></a>
### lower_bound — primeiro elemento >= x

Retorna um **iterador**, uma posição na coleção. `*it` lê o valor;
em vector, `it - v.begin()` converte para índice. Para igualdade: confira
`it != v.end() && *it == x`. Se não houver >= x, retorna `v.end()`.

<a id="upper-bound"></a>
### upper_bound — primeiro elemento > x

Também retorna iterador; passa por todas as ocorrências iguais a x.
Se não houver > x, retorna `v.end()`.

<a id="contar"></a>
### Contar ocorrências

O intervalo dos iguais é **[lower_bound(x), upper_bound(x))**:
inclui o início e exclui o fim. Em vector, quantidade = upper − lower.

## TEMPLATE C++

Exemplo completo; troque v e x pelos seus dados. A saída confirma as posições acima.

<!-- search-example: bounds -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> v = {1, 2, 2, 2, 5, 8};
    long long x = 2;

    bool exists = binary_search(v.begin(), v.end(), x);
    auto lower = lower_bound(v.begin(), v.end(), x);
    auto upper = upper_bound(v.begin(), v.end(), x);

    cout << exists << '\n';                 // 1 (true)
    cout << lower - v.begin() << '\n';      // 1
    cout << upper - v.begin() << '\n';      // 4
    cout << upper - lower << '\n';          // 3 ocorrências

    if (lower != v.end()) cout << *lower << '\n'; // 2
    if (upper != v.end()) cout << *upper << '\n'; // 5

    bool exact = lower != v.end() && *lower == x;
    cout << exact << '\n';                  // 1 (true)
}
```

## COMPLEXIDADE

Em vector ordenado: O(log N) por chamada, O(1) de memória extra.
Contar com duas chamadas continua O(log N). Ordenar, se necessário: O(N log N) uma vez.

## ARMADILHAS

- **Nunca leia `*v.end()`**. Índice N significa ausência de limite válido, não elemento N.
- Não confunda iterador com valor: `lower` é posição; `*lower` é o valor (se válido).
- Em `set`, `multiset` e `map`, use `s.lower_bound(x)` / `s.upper_bound(x)`:
  são O(log N). As versões genéricas podem percorrer O(N) iteradores nesses containers.
- Não subtraia iteradores de set/map. `distance(s.begin(), it)` é O(N);
  `distance(lower, upper)` custa O(quantidade de elementos percorridos).
- A regra desta página assume ordem crescente padrão. Comparador diferente exige ordenação e busca coerentes.
- Só precisa da última ocorrência? Se lower != upper, o índice é `(upper - v.begin()) - 1`.
