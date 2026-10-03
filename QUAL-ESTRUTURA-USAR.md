# QUAL ESTRUTURA USAR?

[Índice](README.md) · [Mapa de resolução](MAPA-DE-RESOLUCAO.md)

**Qual operação vou repetir? → Qual estrutura faz isso sem percorrer tudo?**
Este arquivo compara custos e aponta para as explicações completas.
Para reconhecer frases do enunciado, comece pelo
[mapa de padrões](MAPA-DE-RESOLUCAO.md#o-que-o-enunciado-está-me-pedindo).

Os exemplos foram organizados por assunto nas pastas existentes:
[sequências/frequências](c++/basics/collections.md),
[sets/mapas](c++/basics/maps-and-sets.md),
[filas/pilhas/heaps](c++/data-structures/README.md),
[algoritmos e padrões](c++/algorithms/patterns.md),
[prefixos/janelas](c++/algorithms/prefix-and-window.md).
N é o número de itens guardados; K é o tamanho da janela. Custos assumem
comparações e hash de chaves pequenas, como int.

## Procure pela operação

| Preciso... | Candidata | Detalhes |
|---|---|---|
| <a id="op01"></a>Acessar por índice | vector / array | [Explicação e exemplo](c++/basics/collections.md#vector) |
| <a id="op02"></a>Saber se um valor existe | unordered_set / set | [Explicação e exemplo](c++/basics/maps-and-sets.md#unordered-set) |
| <a id="op03"></a>Contar frequências | vector / unordered_map / map | [Explicação e exemplo](c++/basics/collections.md#frequency-counting) |
| <a id="op04"></a>Manter únicos | set / unordered_set | [Explicação e exemplo](c++/basics/maps-and-sets.md#set) |
| <a id="op05"></a>Manter ordem dinamicamente | set / multiset | [Explicação e exemplo](c++/basics/maps-and-sets.md#multiset) |
| <a id="op06"></a>Inserir/remover e continuar ordenado | set / multiset | [Explicação e exemplo](c++/basics/maps-and-sets.md#multiset) |
| <a id="op07"></a>Primeiro >= X | lower_bound | [Explicação e exemplo](c++/algorithms/patterns.md#lower-bound) |
| <a id="op08"></a>Primeiro > X | upper_bound | [Explicação e exemplo](c++/algorithms/patterns.md#upper-bound) |
| <a id="op09"></a>Retirar menor/maior repetidamente | min-heap / max-heap | [Explicação e exemplo](c++/data-structures/README.md#min-heap) |
| <a id="op10"></a>Remover um valor arbitrário | multiset / set / hash | [Explicação e exemplo](c++/basics/maps-and-sets.md#multiset) |
| <a id="op11"></a>Atender por chegada | queue | [Explicação e exemplo](c++/data-structures/README.md#queue) |
| <a id="op12"></a>Resolver o último inserido | stack | [Explicação e exemplo](c++/data-structures/README.md#stack) |
| <a id="op13"></a>Mexer nas duas pontas | deque | [Explicação e exemplo](c++/data-structures/README.md#deque) |
| <a id="op14"></a>Existe ativo em [L,R]? | set + lower_bound | [Explicação e exemplo](c++/basics/maps-and-sets.md#set) |
| <a id="op15"></a>Manter os K itens de uma janela | estado depende da consulta | [Explicação e exemplo](c++/algorithms/prefix-and-window.md#sliding-window) |
| <a id="op16"></a>Mediana dinâmica | dois multisets | [Explicação e exemplo](c++/data-structures/README.md#median) |
| <a id="op17"></a>Próximo menor/maior à esquerda/direita | monotonic stack | [Explicação e exemplo](c++/algorithms/patterns.md#monotonic-stack) |
| <a id="op18"></a>Somar intervalos fixos | prefix sum | [Explicação e exemplo](c++/algorithms/prefix-and-window.md#prefix-sum) |
| Intercalar atualizações e somas | Fenwick / segment tree | [Explicação e exemplo](#op19) |
| <a id="op20"></a>Ordenar uma vez e só consultar | vector + sort + bounds | [Explicação e exemplo](c++/algorithms/patterns.md#sort) |
| Máximo/mínimo de cada janela | monotonic deque | [Explicação e exemplo](c++/algorithms/patterns.md#monotonic-deque) |
| Ordem diferente: maior nota, menor id | custom comparator | [Explicação e exemplo](c++/algorithms/patterns.md#custom-comparator) |
| Dois valores somam um alvo | two pointers | [Explicação e exemplo](c++/algorithms/patterns.md#two-pointers) |
| Ordenar trecho, coluna ou índices originais | variantes de sort | [Explicação e exemplo](c++/algorithms/sorting.md) |
| Ler/mover o iterador devolvido pela consulta | begin/end, *it, it-> | [Explicação e exemplo](c++/basics/iterators.md) |

## Comparação curta

"Ordenada" abaixo significa **por valor/chave**, não ordem de chegada.
A busca é por valor/chave; não confunda `map[chave]` com acesso por posição.

| Estrutura | Ordenada? | Duplicatas? | Índice? | Busca | Inserir | Remover | Melhor uso |
|---|---|---|---|---|---|---|---|
| vector | só se ordenar | sim | O(1) | O(N); ordenado: O(log N) | fim: O(1) amort.; meio: O(N) | fim: O(1); meio: O(N) | sequência/indexação |
| array | só se ordenar | sim | O(1) | O(N); ordenado: O(log N) | tamanho fixo | tamanho fixo | tamanho conhecido ao compilar |
| set | sim | não | não | O(log N) | O(log N) | por chave: O(log N) | únicos + vizinhos |
| multiset | sim | sim | não | O(log N) | O(log N) | uma cópia: O(log N)¹ | ordem + repetidos |
| unordered_set | não | não | não | O(1) médio | O(1) médio | O(1) médio | presença |
| map | por chave | chave única | não | O(log N) | O(log N) | O(log N) | chave → dado em ordem |
| unordered_map | não | chave única | não | O(1) médio | O(1) médio | O(1) médio | frequência/associação |
| priority_queue | só topo extremo | sim | não | arbitrária: sem API | O(log N) | só topo: O(log N) | retirar menor/maior |
| stack / queue | não | sim | não | sem API | O(1)² | topo/frente: O(1)² | LIFO / FIFO |
| deque | não | sim | O(1) | O(N) | pontas: O(1); meio: O(N) | pontas: O(1); meio: O(N) | duas pontas |

Hash: O(N) no pior caso por operação. ¹Multiset: `find` + `erase(it)` custa
O(log N); `erase(x)` apaga TODAS as C cópias em O(log N + C).
²Custos com os containers padrão: stack usa deque; queue usa deque.
`pair` não é um container: só junta dois campos, como valor e índice.
[Regras dos containers associativos no padrão C++](https://eel.is/c++draft/associative.reqmts).

## NÃO ESCOLHA A ESTRUTURA PELO NOME DO PROBLEMA

“Intervalo”, “menor”, “ordenado” e “janela” não escolhem a estrutura sozinhos.
Veja [PARECE X, MAS É Y](MAPA-DE-RESOLUCAO.md#parece-x-mas-é-y) e os
[seis problemas estudados](MAPA-DE-RESOLUCAO.md#problemas-estudados).
Presença não é frequência; ordem dinâmica não é ordenar uma única vez;
remoção arbitrária não é retirar o topo.

## Atualizações + consultas — referência adicional

<a id="op19"></a>

### 19. Fazer muitas atualizações + consultas

**Use Fenwick** para somar incremento numa posição + consultar somas:
O(log N) por operação, O(N) memória. Para substituir valor, use delta = novo - antigo.
**Segment tree** atende também mínimo/máximo com atualização pontual, O(log N).
Não use prefixo estático para consultas intercaladas sem reconstruir.
Alternativa: vetor simples se pequeno; diferenças O(N+Q) se só consulta no final.
**Reconheça:** “O valor mudou, mas a próxima consulta já precisa enxergar a mudança.”

Recorte Fenwick dentro de `main()`, com o [template](c++/template.cpp).
Começa com todos os valores zero; índices **1 até N**:

<!-- example: fenwick -->
```cpp
int n = 5; vector<long long> bit(n + 1, 0);
int pos = 3; long long delta = 7; // adicionar 7 na posição 3
for (int i = pos; i <= n; i += i & -i) bit[i] += delta;
int r = 4; long long soma = 0;
for (int i = r; i > 0; i -= i & -i) soma += bit[i];
cout << soma; // soma [1,4] = 7
```

`i & -i` é o menor bit ligado; os saltos visitam os blocos que guardam somas.
Exige 1 <= pos <= N e 0 <= r <= N; pos=0 faria o loop travar.
Soma [L,R] = prefixo(R) - prefixo(L-1), repetindo a consulta acima nos dois limites.
Fenwick/segment tree ainda não têm arquivos completos aqui; este é um recorte
de reconhecimento. [difference-array.cpp](c++/algorithms/difference-array.cpp)
resolve **adições em intervalos com resultado só no final**, não consultas online.

## CHECKLIST DE 20 SEGUNDOS ANTES DE CODAR

O checklist completo está [no mapa, logo após a tabela de reconhecimento](MAPA-DE-RESOLUCAO.md#checklist-de-20-segundos-antes-de-codar).
Confira sobretudo: operações repetidas, ordem, duplicatas, dados mudando,
tipo de consulta e complexidade para N, Q e soma dos tamanhos dos testes.

## Equivalentes Python já existentes

Presença: [set](python/collections/sets.py); frequências:
[Counter](python/collections/frequency.py); fila/duas pontas:
[deque](python/collections/queue.py); limites ordenados:
[bisect](python/algorithms/README.md#bisect-limite-não-é-presença);
[prefix sum](python/algorithms/prefix_sum.py) e
[janela fixa](python/algorithms/sliding_window_fixed.py).
`set` Python não é ordenado; `bisect` em lista não torna inserção O(log N).
Não há equivalente pronto de dois multisets ordenados nesta trilha Python.
