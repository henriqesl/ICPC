# C++17 — linguagem principal

| Preciso... | Consulte |
|---|---|
| Sintaxe, tipos, funções e STL | [Referência rápida](cheatsheets/cpp.md) |
| Vetores, índice, remoção, set/map/fila/heap | [Estruturas](cheatsheets/collections.md) |
| Letras, dígitos, conversões e linhas | [Strings](cheatsheets/strings.md) |
| Escolher algoritmo e aplicação | [Algoritmos](algorithms/README.md) |
| MDC, divisores, primos e módulo | [Matemática](math/README.md) |
| Entrada e saída | [Exemplo](basics/io.cpp) |
| Template | [template.cpp](template.cpp) |
| Tempo, memória e erros comuns | [Cuidados](basics/performance.md) |
| Consulta em comentários C++ | [reference.cpp](basics/reference.cpp), [APPLICATIONS.cpp](APPLICATIONS.cpp) |
| Equivalências Python | [Comparação](../python/cheatsheets/cpp-python.md) |

## Aplicações de estruturas

| Aplicação | Exemplo executável |
|---|---|
| Índice, frequência e ordenação de vetor | [Vector](basics/useful-operations/vector-operations.cpp) |
| Delimitadores balanceados | [Stack](data-structures/stack/balanced-parentheses-main.cpp) |
| Atendimento por chegada | [Queue](data-structures/queue/queue-example.cpp) |
| Duas pontas | [Deque](data-structures/deque/deque-example.cpp) |
| Valores com índices originais | [Pair](data-structures/pair/pair-example.cpp) |
| Distintos ordenados | [Set](data-structures/set/set-example.cpp) |
| Frequência por valor | [Map](data-structures/map/frequency-map.cpp) |
| Maior prioridade primeiro | [Heap](data-structures/priority-queue/priority-queue-example.cpp) |
| Letras e dígitos | [Conversões](strings/conversions.cpp) |

Exemplos com main são programas independentes. Compile um por vez, a partir de icpc:

```text
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 "c++/algorithms/searching/binary-search-main.cpp" -o busca
```

Windows: execute `./busca.exe`; Linux: `./busca`.
Digite `4 1 3 3 8 3`; saída: 1. A lista precisa estar ordenada.

Cabeçalhos descrevem aplicação, pré-condições e entrada/saída.
reference.cpp, APPLICATIONS.cpp e math-reference.cpp são consulta comentada.
balanced-parentheses.cpp tem função reutilizável sem main; compile com -c ou copie a função.
Para submissão use as flags permitidas pelo juiz (normalmente -O2).
Testes: `python -B "c++/tests/test_library.py"`; precisa de g++ no PATH.

Básico: I/O, strings, vector, pair, sort, stack, queue e deque.
Intermediário: set/map/heap, busca binária, prefix sum, dois ponteiros,
seleção gulosa de intervalos e teoria dos números.
Grafos, DP e geometria ainda não implementados.
