# Onde aplicar cada arquivo `.cpp`

Use este arquivo quando você reconhecer o padrão do problema e precisar de um ponto de partida.

| Se o problema pede... | Arquivo | Ideia principal |
|---|---|---|
| Encontrar posição, contar ocorrências ou ordenar um vetor | [`vector-operations.cpp`](cpp/useful-operations/vector-operations.cpp) | `find`, `count`, índice pelo iterador e `sort`. |
| Ordenar dados crescente e decrescente | [`sorting-example.cpp`](algorithms/sorting/sorting-example.cpp) | `sort` nos dois sentidos. |
| Procurar em vetor ordenado ou achar o primeiro valor `>= x` | [`binary-search-main.cpp`](algorithms/searching/binary-search-main.cpp) | Busca binária em `O(log N)`. O vetor precisa estar ordenado. |
| Responder várias somas de intervalos `[l, r]` | [`prefix-sum-main.cpp`](algorithms/prefix-sum/prefix-sum-main.cpp) | Prefix sum: construção `O(N)`, consulta `O(1)`. |
| Verificar parênteses, colchetes ou chaves | [`balanced-parentheses-main.cpp`](data-structures/stack/balanced-parentheses-main.cpp) | `stack`: o último aberto fecha primeiro. |
| Reutilizar a função de delimitadores | [`balanced-parentheses.cpp`](data-structures/stack/balanced-parentheses.cpp) | Versão sem `main()`, pronta para copiar. |
| Processar elementos na ordem de chegada | [`queue-example.cpp`](data-structures/queue/queue-example.cpp) | `queue` segue FIFO. |
| Remover duplicatas e manter valores ordenados | [`set-example.cpp`](data-structures/set/set-example.cpp) | `set` guarda cada valor uma vez. |
| Contar frequência de números ou categorias | [`frequency-map.cpp`](data-structures/map/frequency-map.cpp) | `map[chave]++`. |
| Sempre escolher o maior elemento disponível | [`priority-queue-example.cpp`](data-structures/priority-queue/priority-queue-example.cpp) | `priority_queue` mantém o maior no topo. |

## Como adaptar

Os exemplos têm `main()` e servem para entender a aplicação. Durante o contest:

1. Copie a estrutura necessária para o seu template.
2. Troque a leitura e a saída conforme o enunciado.
3. Remova o que não for necessário.
4. Confira as pré-condições: busca binária exige ordenação; prefix sum exige índices corretos; `top()` e `front()` exigem estrutura não vazia.

## Reconhecimento rápido

- “Quantas vezes cada valor aparece?” → `map` ou vetor de frequência.
- “Os símbolos fecham na ordem correta?” → `stack`.
- “Muitas somas de intervalos?” → prefix sum.
- “Menor ou maior disponível a cada passo?” → `priority_queue`.
- “Valores únicos e ordenados?” → `set`.
- “Vetor ordenado e preciso localizar um limite?” → busca binária.

