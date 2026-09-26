# C++17 × Python 3

| Objetivo | C++17 | Python | Diferença |
|---|---|---|---|
| Vetor | vector | list | Python guarda referências; mais memória |
| Conjunto | set / unordered_set | set | Python hash, O(1) médio; não ordenado |
| Mapa | map / unordered_map | dict | hash O(1) médio; ordem de inserção |
| Fila | queue | deque | append / popleft |
| Duas pontas | deque | deque | Python: acesso ao meio O(N), C++ O(1) |
| Pilha | stack | list | append / pop / [-1] |
| Heap | priority_queue | heapq | máximo em C++, mínimo em heapq |
| Ordenação | sort | sort / sorted | Python estável; sort retorna None |
| Lower / upper bound | lower_bound / upper_bound | bisect_left / bisect_right | Python devolve índice, C++ iterador |
| Inteiro | int / long long | int | precisão arbitrária e custo variável |
| Divisão inteira negativa | -7 / 2 → -3 | -7 // 2 → -4 | trunca para zero / arredonda para baixo |

[Referência Python](python.md) · [Referência C++](../../c++/basics/reference.cpp)
