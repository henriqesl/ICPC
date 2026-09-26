# Algoritmos Python: escolha pelo problema

| Aplicação | Python | Referência C++ existente |
|---|---|---|
| Índice exato em dados sem ordenação; O(N) | [linear_search](searching.py) | [find](../../c++/basics/useful-operations/vector-operations.cpp) |
| Primeiro valor >= alvo em dados ordenados; O(log N) | [first_at_least](searching.py) | [Busca binária](../../c++/algorithms/searching/binary-search-main.cpp) |
| Somas de intervalos imutáveis; O(N) + O(1)/consulta | [Prefix sum](prefix_sum.py) | [Prefix sum](../../c++/algorithms/prefix-sum/prefix-sum-main.cpp) |
| Colocar dados em ordem; O(N log N) | [Ordenação](sorting.py) | [sort](../../c++/algorithms/sorting/sorting-example.cpp) |
| Dois índices com soma alvo; O(N), lista ordenada | [Dois ponteiros](two_pointers.py) | [Dois ponteiros](../../c++/algorithms/two-pointers/two-pointers.cpp) |
| Máximo número de intervalos compatíveis, sem pesos | [Guloso](greedy.py) | [Intervalos](../../c++/algorithms/greedy/intervals.cpp) |
| Frequências | [Counter](../collections/frequency.py) | [map](../../c++/data-structures/map/frequency-map.cpp) |
| Divisores, primo, MDC/MMC | [Teoria dos números](../math/number_theory.py) | [Referência](../../c++/math/math-reference.cpp) |

Os conceitos dos pares existentes são os mesmos; consulte os comentários C++
para a ideia geral e o Python para sintaxe. Novas técnicas têm justificativa no
próprio arquivo. Grafos/DFS/BFS ainda não estão implementados.

## Bisect: limite não é presença

```python
from bisect import bisect_left, bisect_right, insort
v = [1, 3, 3, 8]
i = bisect_left(v, 3)  # 1: primeiro >= 3 (lower_bound)
j = bisect_right(v, 3) # 3: primeiro > 3 (upper_bound)
exists = i < len(v) and v[i] == 3
amount = j - i         # 2 ocorrências
insort(v, 4)          # [1, 3, 3, 4, 8]
```

A lista deve estar ordenada. bisect custa O(log N); insort custa O(N) porque
desloca elementos, apesar da busca rápida. Retorno len(v) é válido e não pode
ser usado para acessar v. [Fonte oficial](https://docs.python.org/3/library/bisect.html).

## Ordenação

`sorted(v)` cria lista; `v.sort()` modifica v e retorna None.
`sorted(v, reverse=True)` é decrescente.
`sorted(pares, key=lambda x: x[1])` ordena pelo segundo campo.
A ordenação Python é estável: empates mantêm ordem de entrada.
Ordenar pode invalidar índices originais: carregue pares (valor, índice) se precisar deles.
