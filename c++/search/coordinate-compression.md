# COMPRESSÃO DE COORDENADAS — valores viram índices

[Índice](README.md) · [Bounds](bounds.md) · [Sweep line](sweep-line.md)

## NECESSIDADE / RECONHECIMENTO

Valores chegam a 10^9, 10^18 ou são negativos, mas existem poucos valores distintos.
Preciso de índices para frequências, eventos ou estruturas indexadas — não de um vetor até o maior valor.
É um **pré-processamento**, não um algoritmo de busca por resposta.

## IDEIA

1. Copie os valores para não destruir a ordem de entrada.
2. Ordene a cópia.
3. Remova repetidos: cada valor distinto ganha um índice.
4. `lower_bound` encontra o índice do valor original na cópia ordenada.

```text
original:    [100, 5, 100, 1000000000]
distintos:   [5, 100, 1000000000]
comprimido:  [1, 0, 1, 2]
```

## TEMPLATE C++

Entrada: N e N valores. Saída: valor original -> índice (base 0), na ordem de entrada.

<!-- search-example: coordinate-compression -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> values(n);
    for (long long &x : values) cin >> x;

    vector<long long> compressed = values;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

    for (long long x : values) {
        auto index = lower_bound(compressed.begin(), compressed.end(), x) - compressed.begin();
        cout << x << " -> " << index << '\n';
        // compressed[index] recupera o valor original desse índice.
    }
}
```

```text
Entrada: 4
         100 5 100 1000000000
Saída:   100 -> 1
         5 -> 0
         100 -> 1
         1000000000 -> 2
```

## COMPLEXIDADE

Ordenar O(N log N), remover repetidos O(N), mapear N valores O(N log M),
onde M <= N é o número de distintos. Total O(N log N), memória O(N).
Uma conversão posterior por lower_bound custa O(log M).

## ARMADILHAS

- Preserva **igualdade e ordem**: a < b implica índice(a) < índice(b).
  **Não preserva distância**: 1000000000 − 100 não vira 2 − 1.
- `unique` sozinho não encolhe o vetor; use `erase`. Ordene antes para juntar todos os iguais.
- O índice comprimido **não é a posição original** na entrada.
- `lower_bound` só representa um ID exato se o valor estiver na lista.
  Para um valor novo, pode retornar posição de inserção ou end(); confira igualdade.
- Precisa incluir limites de consultas? Reúna as coordenadas necessárias antes de comprimir,
  ou use bounds para localizar intervalos entre coordenadas existentes.
- Em dados online, inserir novas coordenadas pode mudar IDs; não suponha que a compressão inicial basta.
