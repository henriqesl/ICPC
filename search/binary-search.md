# BINARY SEARCH TRADICIONAL

[Índice](README.md) · [Bounds](bounds.md) · [Na resposta](binary-search-on-answer.md)

## NECESSIDADE / RECONHECIMENTO

Coleção **ordenada crescente** e busca por um valor exato.

| Busca | Pergunta |
|---|---|
| Tradicional | **“X está aqui?”** — compara X com elementos do vetor. |
| Na resposta | **“Se a resposta fosse X, funcionaria?”** — testa viabilidade; pode nem existir vetor de respostas. |

## IDEIA

`left` e `right` delimitam o trecho ainda possível, **ambos inclusivos**.
`mid` é o índice do meio. Cada comparação descarta metade desse trecho.

| Comparação | Ação |
|---|---|
| v[mid] < target | `left = mid + 1`: alvo só pode estar à direita. |
| v[mid] > target | `right = mid - 1`: alvo só pode estar à esquerda. |
| v[mid] == target | Achou; salve mid e pare. |

## TEMPLATE C++

Entrada: N, alvo e N valores **já ordenados**. Saída: um índice com esse valor, ou -1.

<!-- search-example: binary -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;

    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    int left = 0;
    int right = n - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (v[mid] == target) {
            answer = mid;
            break;
        } else if (v[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << '\n';
}
```

## EXEMPLO

```text
Entrada: 6 5
         1 2 2 2 5 8
Saída:   4
```

`left + (right - left) / 2` evita somar dois índices grandes, como em `(left + right) / 2`.
`while (left <= right)` ainda testa o último candidato; terminou quando left > right.
Use índices com sinal: para N = 0, right = -1 e o loop não executa.

## COMPLEXIDADE

Busca: O(log N), O(1) de memória extra; armazenamento do vetor: O(N).
Se precisar de `sort(v.begin(), v.end())`, some O(N log N) de preparação.

## ARMADILHAS

- Não use em vetor desordenado. Ordenar muda os índices e pode destruir a ordem exigida pelo problema.
- Com repetidos, esse template acha **uma** ocorrência, não necessariamente a primeira.
  Para primeira ocorrência, use [lower_bound + teste de igualdade](bounds.md#lower-bound).
- `<` e `>` indicam o lado; igualdade resolve a busca tradicional, mas **não** resolve busca na resposta.
- Só precisa saber se existe? `std::binary_search` já devolve bool; não é índice.
- O arquivo antigo `c++/algorithms/binary-search.cpp` procura primeiro >= alvo;
  não é este template de igualdade.
