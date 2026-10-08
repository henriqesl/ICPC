# Algoritmos — arquivos diretos nesta pasta

Antes do código: [gatilhos → ideia → exemplo → comandos → custo → não confundir](patterns.md).
Para reconhecer o pedido: [mapa geral](../../MAPA-DE-RESOLUCAO.md#o-que-o-enunciado-está-me-pedindo).
Consulta das técnicas de study/: [buscas, two pointers, sweep line, compressão e enumeração](../search/README.md).

| Preciso... | Abra | Condição |
|---|---|---|
| Localizar primeira ocorrência exata | [linear-search.cpp](linear-search.cpp) | qualquer ordem; O(N) |
| Primeiro valor >= alvo | [binary-search.cpp](binary-search.cpp) | vetor ordenado; O(log N) na busca |
| lower_bound / upper_bound: primeiro >= / >; último < / <=; contar em [L,R] | [bounds.cpp](bounds.cpp) | ordenação/conjunto ordenado; trata ausência |
| Ordenar crescente/decrescente | [sorting.cpp](sorting.cpp) | O(N log N); muda índices |
| Sort por trecho, coluna, second ou lista de índices | [Variantes](sorting.md), [sorting-variants.cpp](sorting-variants.cpp) | inclui stable_sort; exemplos independentes |
| Ordenar por pontuação e desempatar por id | [Custom comparator](patterns.md#custom-comparator) | regra estrita; não use <= como desempate |
| Somar muitos intervalos | [prefix-sum.cpp](prefix-sum.cpp) | dados fixos; O(N)+O(1) por consulta |
| Adicionar a muitos intervalos e consultar só no final | [difference-array.cpp](difference-array.cpp) | O(N+Q); não é consulta online |
| Maior soma de K consecutivos | [sliding-window-fixed.cpp](sliding-window-fixed.cpp) | 1 <= K <= N; O(N) |
| Maior trecho com soma limitada | [sliding-window-variable.cpp](sliding-window-variable.cpp) | não negativos; O(N) |
| Maior trecho com até K distintos | [sliding-window-distinct.cpp](sliding-window-distinct.cpp) | aceita negativos; O(N) médio |
| Dois valores somam alvo | [two-pointers.cpp](two-pointers.cpp) | ordenado; O(N) |
| Primeiro menor estrito à esquerda e à direita | [monotonic-stack.cpp](monotonic-stack.cpp) | índices; O(N); veja [empates](patterns.md#monotonic-stack) |
| Máximo de cada janela K | [monotonic-deque.cpp](monotonic-deque.cpp) | 1 <= K <= N; O(N); adaptável para mínimo |
| Máximo número de atividades compatíveis | [greedy.cpp](greedy.cpp) | sem pesos; O(N log N) |

Começando agora: [prefix sum e sliding window passo a passo](prefix-and-window.md).

Todos os exemplos acima estão diretamente no main; leia de cima para baixo.
Busca binária devolve um limite, não necessariamente igualdade. Ordenação
não é estável com sort; use stable_sort quando a ordem dos empates importar.
Guloso exige justificar a escolha local — o comentário do arquivo faz isso.
[Equivalentes Python](../../python/algorithms/README.md).
