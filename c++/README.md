# C++17 — comece por aqui

Exemplos diretos no `main()`, com entrada, saída e comentários.
Cada arquivo resolve uma aplicação pequena: compile **um de cada vez**.

| Pasta | O que tem |
|---|---|
| [basics/](basics/) | Entrada, strings, vector, map, unordered_map, set, multiset e referências da linguagem. |
| [data-structures/](data-structures/) | Fila, pilha, deque, pair e heap. Todos diretamente nessa pasta. |
| [algorithms/](algorithms/README.md) | Busca, ordenação, prefix sum, sliding window, dois ponteiros e guloso. |
| [math/](math/README.md) | Divisores, primalidade, MDC/MMC e potência modular. |

## Encontre pelo que precisa fazer

| Preciso... | Abra |
|---|---|
| Entender map, unordered_map, set e multiset | [Comparação com exemplos](basics/maps-and-sets.md) |
| Contar valores em ordem / consultar rápido | [map.cpp](basics/map.cpp) / [unordered-map.cpp](basics/unordered-map.cpp) |
| Guardar únicos / permitir repetidos ordenados | [set.cpp](basics/set.cpp) / [multiset.cpp](basics/multiset.cpp) |
| Primeiro/último, begin/end/rbegin e remoção | [Set](basics/set.cpp), [multiset](basics/multiset.cpp), [guia](basics/maps-and-sets.md#extremos-e-vizinhos) |
| lower_bound, upper_bound, vizinhos e quantidade em intervalo | [bounds.cpp](algorithms/bounds.cpp) |
| Atender por chegada | [queue.cpp](data-structures/queue.cpp) |
| Fechar símbolos na ordem correta | [stack.cpp](data-structures/stack.cpp) |
| Mexer nas duas pontas / pegar maior prioridade | [deque.cpp](data-structures/deque.cpp) / [priority-queue.cpp](data-structures/priority-queue.cpp) |
| Guardar valor e índice | [pair.cpp](data-structures/pair.cpp) |
| Achar índice ou contar num vetor | [vector.cpp](basics/vector.cpp) |
| Converter letras/dígitos | [strings.cpp](basics/strings.cpp), [referência](basics/strings.md) |
| Aprender prefix sum e sliding window | [Guia com passo a passo](algorithms/prefix-and-window.md) |
| Somar intervalos / melhor soma de K consecutivos | [prefix-sum.cpp](algorithms/prefix-sum.cpp) / [janela fixa](algorithms/sliding-window-fixed.cpp) |
| Maior trecho com soma limitada (não negativos) | [janela variável](algorithms/sliding-window-variable.cpp) |
| Maior trecho com até K valores diferentes | [janela com frequências](algorithms/sliding-window-distinct.cpp) |
| Somar a vários intervalos e obter resultado final | [vetor de diferenças](algorithms/difference-array.cpp) |
| Outros algoritmos | [Índice](algorithms/README.md) |
| Relembrar STL, tipos ou complexidade | [C++](basics/cpp.md), [estruturas](basics/collections.md), [performance](basics/performance.md) |
| Começar uma solução | [template.cpp](template.cpp) |

`push`, `pop`, `find`, `sort` e `gcd` são operações prontas da biblioteca.
Não é necessário escrever essas funções. Por exemplo, em queue, `push` insere,
`front` consulta o primeiro e `pop` remove: o arquivo explica a execução inteira.

## Rodar um exemplo

A partir de icpc:

```text
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 "c++/data-structures/queue.cpp" -o fila
```

Windows: `./fila.exe`; Linux: `./fila`. Digite `3 Ana Bia Caio`.
Saída: Ana, Bia, Caio, uma pessoa por linha.

Arquivos .cpp de referência, contendo só comentários, não são executáveis.
Os demais têm main. Testes: `python -B "c++/test_library.py"`.
Não precisa abrir o teste durante o contest.

**Ordem de estudo:** basics → fila/pilha → prefix sum → janela fixa → janela
variável → busca binária/dois ponteiros/guloso. Grafos, DP e geometria ficam para depois.
