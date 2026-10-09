# ICPC — consulta de contest

C++17 principal · [Python](python/README.md) · [template.cpp](c++/template.cpp)

**Procure o pedido na tabela → abra o trecho → confira a condição → adapte o código.**
Não precisa ler o guia inteiro. “Entender melhor” guarda o passo a passo, recolhido no GitHub.
Use Ctrl+F com palavras como `soma`, `janela`, `divisores`, `lower` ou `permutação`.

## Algoritmos: o que a questão pede?

| Preciso... | Abra direto | Só serve assim |
|---|---|---|
| Saber se X existe / achar sua posição | [Linear](c++/search/binary-search.md#linear) · [binária](c++/search/binary-search.md#tradicional) | binária exige ordenação |
| Primeiro >= X / primeiro > X / contar iguais | [Bounds](c++/search/binary-search.md#bounds) | dados ordenados; limite não prova igualdade |
| Menor valor que funciona | [FIRST TRUE](c++/search/binary-search.md#first-true) | funcionar em X implica funcionar nos maiores |
| Maior valor que funciona | [LAST TRUE](c++/search/binary-search.md#last-true) | funcionar em X implica funcionar nos menores |
| Somar vários intervalos [L,R] | [Prefix sum](c++/algorithms/prefix-and-window.md#prefix-sum) | array não muda; aceita negativos |
| Melhor soma de K consecutivos | [Janela fixa](c++/algorithms/sliding-window-fixed.cpp) | 1 <= K <= N; aceita negativos |
| Maior trecho com soma <= S | [Janela variável](c++/search/two-pointers.md#janela) | valores não negativos e S >= 0 |
| Maior trecho com até K distintos | [Janela + frequências](c++/algorithms/sliding-window-distinct.cpp) | apagar frequência zero; K >= 0 |
| Somar em vários intervalos, ver só o final | [Diferenças](c++/algorithms/difference-array.cpp) | não são consultas intercaladas |
| Alterar valores e já consultar somas | [Fenwick: recorte](QUAL-ESTRUTURA-USAR.md#op19) | atualização pontual; índices de 1 a N |
| Par com soma / diferença alvo | [Soma](c++/search/two-pointers.md#par) · [diferença](c++/search/two-pointers.md#diferenca) | ordenado; dois índices distintos |
| Juntar dois arrays ordenados | [Merge](c++/search/two-pointers.md#merge) | ambos ordenados; mantém repetições |
| Intervalos ativos / eventos no tempo | [Sweep line](c++/search/sweep-line.md#receita) · [consultas](c++/search/sweep-line.md#query-events) | definir extremos e ordem dos empates |
| Valores enormes, mas preciso de índices pequenos | [Compressão](c++/search/sweep-line.md#compression) | preserva ordem, não distância |
| Primeiro menor/maior à esquerda ou direita | [Pilha monotônica](c++/algorithms/patterns.md#monotonic-stack) | importa posição; não ordene |
| Máximo/mínimo de cada janela K | [Deque monotônica](c++/algorithms/patterns.md#monotonic-deque) | 1 <= K <= N; usa índices |
| Mediana com entradas e saídas | [Dois multisets: recorte](c++/data-structures/README.md#median) | rebalancear; conferir mediana inferior/média |
| Testar pares/trios / subconjuntos / ordens | [Loops](c++/search/exhaustive-search.md#pares) · [bitmask](c++/search/exhaustive-search.md#subconjuntos) · [permutação](c++/search/exhaustive-search.md#permutacoes) | estimar N² / N·2^N / N·N! |
| Construir, testar e desfazer escolhas | [Backtracking](c++/search/backtracking.md#mapeamento) | estado completo e poda justificada |
| Máxima quantidade de atividades sem conflito | [Guloso](c++/algorithms/greedy.cpp) | sem pesos; ordenar pelo fim |
| Ordenar por campo, trecho, coluna ou índice | [Variantes de sort](c++/algorithms/sorting.md) | preserve índices originais, se pedidos |
| Primos / divisores / MDC / potência módulo M | [Matemática](c++/math/README.md) | conferir limites e overflow |

## Estruturas e sintaxe

| Preciso... | Abra direto |
|---|---|
| Índice / valor+id / frequências | [Vector](c++/basics/collections.md#vector) · [pair](c++/basics/collections.md#pair) · [contagem](c++/basics/collections.md#frequency-counting) |
| Únicos / repetidos em ordem | [Set](c++/basics/maps-and-sets.md#set) · [multiset](c++/basics/maps-and-sets.md#multiset) |
| Chave → valor ou quantidade | [Map](c++/basics/maps-and-sets.md#map) · [unordered_map](c++/basics/maps-and-sets.md#unordered-map) |
| Primeiro, último, antecessor, sucessor | [Extremos e vizinhos](c++/basics/maps-and-sets.md#extremos-e-vizinhos) |
| Ordem de chegada / fechar delimitadores | [Queue](c++/data-structures/README.md#queue) · [stack](c++/data-structures/README.md#stack) |
| Duas pontas / retirar sempre menor ou maior | [Deque](c++/data-structures/README.md#deque) · [min-heap](c++/data-structures/README.md#min-heap) · [max-heap](c++/data-structures/README.md#max-heap) |
| begin/end, *it, it->, índice de um iterador | [Iteradores](c++/basics/iterators.md) |
| Tipos, entrada, strings, tempo/memória | [C++](c++/basics/cpp.md) · [strings](c++/basics/strings.md) · [limites](c++/basics/performance.md) |

Ainda não reconheceu? [Mapa de raciocínio](MAPA-DE-RESOLUCAO.md) · [Qual estrutura usar?](QUAL-ESTRUTURA-USAR.md).
Arquivos por pasta: [C++](c++/README.md) · [Python](python/README.md).

## Antes de enviar

Confira: saída exata, base 0/1, vazio/um item, repetidos, negativos, `long long`,
extremos inclusivos/exclusivos e custo total de todos os casos. Exemplos demonstrativos podem imprimir rótulos: retire-os para o juiz.

## Dificuldade

- **Básico:** entrada/saída, strings, vector/array, sort, pilha e fila.
- **Intermediário:** mapas/sets, heap, bounds, prefix sum, janelas, two pointers, busca na resposta, sweep line, compressão, backtracking, estruturas monotônicas, mediana, guloso e teoria dos números.
- **Avançado — futuro:** grafos, programação dinâmica e geometria.
