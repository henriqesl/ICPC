# Coleções Python

[Índice](../../README.md). Custos abaixo assumem chaves e comparações de tamanho limitado.

## Listas

Sequência indexada como vector, mas armazena referências a objetos e usa mais memória.
`a = [3, 1, 3]`, `empty = []`, `zeros = [0] * n`.

| Operação | Resultado / cuidado | Tempo |
|---|---|---|
| `a[i]`, `a[-1]` | acesso; último com -1, vazio gera IndexError | O(1) |
| `a[l:r]` | cópia, fim exclusivo; `a[::-1]` inverte copiando | O(tamanho copiado) |
| `a.append(x)` | insere no fim | O(1) amortizado |
| `a.pop()` | retorna e remove último; exige não vazio | O(1) |
| `a.pop(i)`, `del a[i]` | remove por índice | O(N) |
| `a.insert(i, x)` | desloca elementos | O(N) |
| `a.remove(x)` | remove primeira ocorrência; ValueError se ausente | O(N) |
| `a.clear()` | esvazia | O(N) |
| `a.sort()` | modifica a lista; retorna None | O(N log N) |
| `a.reverse()` | inverte no lugar; retorna None | O(N) |
| `a.index(x)` | primeiro índice; ValueError se ausente | O(N) |
| `a.count(x)`, `x in a` | conta / testa presença | O(N) |

```python
a = [3, 1, 3]
i = a.index(3) if 3 in a else -1
a.remove(3)                 # [1, 3]
a = [x for x in a if x != 3] # remove TODAS
matrix = [[0] * 3 for _ in range(2)]  # linhas independentes
```

[Aplicação executável](../collections/lists.py).

## Sets

```python
s = set()  # {} é dict
s.add(4)
s.remove(4)  # KeyError se ausente
s.discard(4) # não falha se ausente
found = 4 in s
a, b = {1, 2}, {2, 3}
a & b  # {2}: interseção, O(min(len(a), len(b))) médio
a | b  # {1, 2, 3}: união, O(len(a)+len(b)) médio
a - b  # {1}: diferença, O(len(a)) médio
```

Inserção, remoção e presença: O(1) médio, O(N) no pior caso.
Não há ordem de classificação garantida. Para imprimir em ordem, use sorted(s).
Útil para distintos e buscas repetidas; perde contagens.
[Aplicação](../collections/sets.py).

## Dictionaries

```python
freq = {}
for x in [3, 3, 8]:
    freq[x] = freq.get(x, 0) + 1
freq[9] = 2
freq.get(7, 0)   # 0 sem criar chave
freq[3]         # 2; chave ausente causaria KeyError
freq.pop(9)     # remove e retorna 2
list(freq.items())  # [(3, 2), (8, 1)]
list(freq.keys())   # [3, 8]
list(freq.values()) # [2, 1]
from collections import Counter
counts = Counter([3, 3, 8]) # mesma contagem; counts[7] retorna 0
```

dict preserva ordem de inserção, não ordem numérica. Busca/inserção/remoção O(1)
médio, O(N) pior caso; percorrer items/keys/values custa O(N).
Use o loop para personalizar atualizações e Counter para contagem direta.
[Aplicação](../collections/frequency.py).

## Deque

```python
from collections import deque
q = deque([2])
q.append(3)
q.appendleft(1)
q.popleft()  # 1
q.pop()      # 3
```

Todas essas operações são O(1); retiradas exigem não vazio. Use como queue de
C++ com append/popleft ou nas duas pontas como deque de C++.
`list.pop(0)` desloca elementos em O(N). Acesso ao meio de deque é O(N),
diferente do deque de C++. [Aplicação](../collections/queue.py).

## Pilha

```python
stack = []
stack.append("(")
if stack:
    top = stack[-1]
    removed = stack.pop()
```

append O(1) amortizado, top/pop O(1). LIFO; mesma ideia da
[pilha C++](../../c++/data-structures/stack/balanced-parentheses.cpp).
[Delimitadores em Python](../collections/balanced.py).

## Heap

```python
import heapq
h = [5, 2, 9]
heapq.heapify(h)       # O(N), modifica a lista
heapq.heappush(h, 1)  # O(log N)
smallest = h[0]       # O(1), exige não vazio
heapq.heappop(h)      # O(log N), remove o menor
h = [-x for x in [5, 2, 9]]
heapq.heapify(h)
largest = -heapq.heappop(h) # 9
```

heapq tradicional é min-heap, priority_queue de C++ é max-heap.
Negar números funciona também em versões anteriores ao Python 3.14.
A lista inteira NÃO está ordenada. [Aplicação](../collections/heap.py).
Referência: [heapq oficial](https://docs.python.org/3/library/heapq.html).
