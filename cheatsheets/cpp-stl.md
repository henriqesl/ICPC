# C++ STL — consulta rápida

| Função | Uso | Complexidade |
|---|---|---:|
| `sort` | Ordena | `O(N log N)` |
| `reverse` | Inverte intervalo | `O(N)` |
| `find` / `count` | Busca / conta ocorrências | `O(N)` |
| `min` / `max` | Menor / maior | `O(1)` |
| `min_element` / `max_element` | Iterador do extremo | `O(N)` |
| `accumulate` | Soma | `O(N)` |
| `lower_bound` / `upper_bound` | Limites em intervalo ordenado | `O(log N)` |
| `binary_search` | Verifica existência ordenada | `O(log N)` |
| `swap` / `abs` | Troca / valor absoluto | `O(1)` |

```cpp
sort(v.begin(), v.end());
auto it = find(v.begin(), v.end(), x);
int index = it == v.end() ? -1 : int(it - v.begin());
long long sum = accumulate(v.begin(), v.end(), 0LL);
```

`lower_bound` e `upper_bound` exigem intervalo ordenado.

