# BUSCA LINEAR

[Índice](README.md) · [Tradicional](binary-search.md) · [Bounds](bounds.md)

## NECESSIDADE / RECONHECIMENTO

“Existe x?”, “qual a primeira posição com essa propriedade?”; os dados não têm uma
ordem útil, ou basta uma consulta. Não precisa ordenar.

## IDEIA

Visite um elemento por vez; pare no primeiro que satisfaz a condição.
Para contar ou listar todas as ocorrências, não pare no primeiro acerto.

## TEMPLATE C++

Entrada: N, alvo e N valores. Saída: primeiro índice (base 0), ou -1 se ausente.

<!-- search-example: linear -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;

    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    int answer = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] == target) {
            answer = i; // primeira ocorrência
            break;
        }
    }

    cout << answer << '\n';
}
```

## EXEMPLO

```text
Entrada: 5 7
         4 7 1 7 9
Saída:   1
```

## COMPLEXIDADE

Busca: O(N) no pior caso, O(1) de memória extra. O vetor de entrada ocupa O(N).
Q buscas independentes custam O(QN); se Q = N, vira **O(N²)**.

Muitas consultas no mesmo conjunto? Pense em ordenar uma vez + [busca binária](binary-search.md)
(O(N log N + Q log N)), ou em `set` / `unordered_set` para presença
(O(log N) / O(1) médio por consulta; hash pode chegar a O(N) no pior caso).
Se a posição original importa, preserve-a antes de ordenar.

## ARMADILHAS

- Não acesse `v[answer]` se answer = -1.
- Vetor vazio: o loop não executa; a resposta continua -1.
- Uma condição arbitrária serve para busca linear; para busca binária, precisa da propriedade adequada.
