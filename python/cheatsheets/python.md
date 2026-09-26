# Python Quick Reference

[Índice](../../README.md) · [Coleções](python-collections.md) · [Strings](python-strings.md) · [C++ × Python](cpp-python.md)

## Entrada e saída

```python
n = int(input())
a, b = map(int, input().split())
v = list(map(int, input().split()))
s = input().strip()  # remove também espaços nas extremidades
for _ in range(int(input())):  # somente se o enunciado fornecer T
    a, b = map(int, input().split())
    print(a + b)
```

Para muitas linhas: `import sys; input = sys.stdin.readline`. Essa leitura mantém
a quebra de linha; use `rstrip("\n")` se espaços fizerem parte da resposta.
Cada `list(map(...))` acima lê uma linha; não presume que N valores ocupem várias linhas.
Veja [I/O](../basics/io.py) para leitura por tokens.

```python
print(1, 2, sep=",", end="\n")  # 1,2
print(*[1, 2, 3])              # 1 2 3
print(f"{1 / 3:.2f}")          # 0.33
```

## Tipos e funções

| Recurso | Exemplo / retorno |
|---|---|
| list / tuple | `[1, 2]` mutável / `(1, 2)` imutável |
| set / dict | `{1, 2}` únicos / `{"a": 2}` chave → valor |
| str | `"abc"`, imutável; não existe tipo char separado |
| deque / heapq | fila nas duas pontas / heap mínimo; veja [coleções](python-collections.md) |
| len / sum | `len([2, 4]) == 2`, `sum([2, 4]) == 6` |
| min / max | `min([2, 4]) == 2`, `max([2, 4]) == 4`; vazios exigem default |
| sorted / reversed | `sorted([3, 1]) == [1, 3]`; `list(reversed([1, 2])) == [2, 1]` |
| enumerate | `list(enumerate(["a"])) == [(0, "a")]` |
| zip | `list(zip([1, 2], [3])) == [(1, 3)]`; para na menor sequência |
| range | `list(range(2, 7, 2)) == [2, 4, 6]`; fim exclusivo |
| abs / all / any | `abs(-3) == 3`; `all([True, False]) == False`; `any([False, True]) == True` |

`len` de coleções nativas é O(1); somas, extremos, all/any percorrem até N itens.
`sorted` é O(N log N); range, enumerate, zip e reversed permitem iteração sem
criar uma lista com todos os resultados. all([]) é True; any([]) é False.

## Iteração e comprehensions

```python
v = [3, 1, 3]
for i in range(len(v)):       # precisa do índice
    pass
for i, value in enumerate(v): # precisa de índice e valor
    pass
for a, b in zip(v, [4, 5, 6]): # pares de sequências
    pass
squares = [x * x for x in range(5)]
unique = {x * x for x in v}
positions = {x: i for i, x in enumerate(v)}  # último índice de cada x
```

Use comprehensions quando a transformação for simples e legível.

## Inteiros e divisão

Inteiros têm precisão arbitrária, ao contrário de int/long long em C++.
Números enormes consomem mais memória e tornam operações mais caras.
`/` produz float; `//` arredonda para baixo; `%` dá resto com o sinal do divisor.

```python
7 / 2     # 3.5
7 // 2    # 3
-7 // 2   # -4 (em C++, -7 / 2 inteiro resulta -3)
-7 % 2    # 1: (-4)*2 + 1 == -7
```

[Performance](../basics/performance.md) · [Matemática](../math/README.md)
