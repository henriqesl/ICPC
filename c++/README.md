# C++17 — arquivos por pasta

Durante o contest, comece pelo [índice por necessidade](../README.md).
[Template](template.cpp) · [Sintaxe](basics/cpp.md) · [Iteradores](basics/iterators.md) · [Tempo e memória](basics/performance.md)

| Pasta | Conteúdo / entrada |
|---|---|
| [basics/](basics/collections.md) | Vector, array, pair, frequências; [map/set/multiset](basics/maps-and-sets.md), strings e I/O. |
| [data-structures/](data-structures/README.md) | Fila, pilha, deque, heaps e recorte de mediana. |
| [algorithms/](algorithms/README.md) | Sort/comparadores, prefix sum, janelas, diferenças, pilha/deque monotônicas e guloso. |
| [search/](search/README.md) | Buscas/bounds, two pointers, sweep line, compressão, enumeração e backtracking. |
| [grafos/](grafos/) | Nove .cpp: [atalhos por necessidade](../README.md#grafos); DFS/BFS, grid, bipartido, topológica, multisource, ciclos e diâmetro. |
| [math/](math/README.md) | Divisores, primalidade, MDC/MMC e potência modular. |

**Como copiar:** recortes dos guias vão no `main()` do template; programas com
`main()` são independentes — copie um por vez. Leia entrada/saída e hipóteses antes de adaptar.
As receitas de [backtracking](search/backtracking-templates.cpp) têm funções sem `main()`;
copie só o namespace/receita necessário, inicialize o estado e chame sua função.
`reference.cpp` e `math-reference.cpp` são consultas comentadas.
Grafos: programas independentes, comentários breves; entrada/saída no topo de cada .cpp.
`graph_representation.cpp` apenas constrói as três representações, sem imprimir.

<details>
<summary>Fora do contest: compilar, testar e ordem de estudo</summary>

## Rodar um exemplo

Na raiz icpc:

```text
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 "c++/data-structures/queue.cpp" -o fila
```

Windows: `./fila.exe`; Linux: `./fila`. Entrada: `3 Ana Bia Caio`.
Saída: Ana, Bia, Caio, uma pessoa por linha. Compile um programa por vez.

```text
python -B c++/test_library.py
python -B c++/test_search.py
python -B c++/test_backtracking.py
python -B c++/test_graphs.py
```

Estudo sugerido: basics → fila/pilha → prefix sum → janela fixa → janela variável
→ bounds → busca binária/two pointers → demais padrões.
[Equivalências C++ × Python](../python/cheatsheets/cpp-python.md).

</details>
