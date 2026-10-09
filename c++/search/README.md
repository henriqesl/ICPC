# SEARCH — escolha pelo pedido

[Consulta geral](../../README.md) · [Custos e pegadinhas](patterns.md#complexidades) · [Template base](../template.cpp)

## NECESSIDADE NO ENUNCIADO → TÉCNICA PROVÁVEL

| Necessidade no enunciado | Técnica provável |
|---|---|
| Procurar valor em coleção sem propriedade | [Linear search](binary-search.md#linear) |
| Array ordenado + procurar valor | [Binary search tradicional](binary-search.md#tradicional) |
| Primeiro >= x / primeiro > x | [lower_bound](binary-search.md#lower-bound) / [upper_bound](binary-search.md#upper-bound) |
| Contar ocorrências em dados ordenados | [upper − lower](binary-search.md#contar) |
| Menor valor que satisfaz condição monotônica | [Na resposta / FIRST TRUE](binary-search.md#first-true) |
| Maior valor que ainda satisfaz condição monotônica | [Na resposta / LAST TRUE](binary-search.md#last-true) |
| Segmento contínuo ajustável | [Sliding window](two-pointers.md#janela), se a condição permitir |
| Par com soma alvo em array ordenado | [Two sum](two-pointers.md#par) |
| Par com diferença alvo em array ordenado | [Two difference](two-pointers.md#diferenca) |
| Juntar dois arrays ordenados | [Merge](two-pointers.md#merge) |
| Muitos intervalos/eventos em coordenadas ou tempo | [Sweep line](sweep-line.md#receita) |
| QUANTOS / QUAIS / duplicatas ativos | [Contador / set / multiset](sweep-line.md#estado) |
| Coordenadas enormes, poucas relevantes e preciso de índices | [Coordinate compression](sweep-line.md#compression) |
| Testar todas as escolhas: pego ou não pego | [Subsets / bitmask](exhaustive-search.md#subconjuntos) |
| Testar todas as ordens | [Permutations](exhaustive-search.md#permutacoes) |
| Poucos elementos e todas as possibilidades | [Complete search](exhaustive-search.md); escolha a enumeração |
| Quantidade fixa de índices / pares / trios | [Nested loops](exhaustive-search.md#pares) |
| Construir aos poucos, testar conflitos e desfazer escolhas | [Backtracking: retorno + escolhas](backtracking.md#mapeamento) |

Antes de copiar: **ordenado? negativos? condição monotônica? intervalo fechado?**
As condições obrigatórias aparecem antes de cada template.
Blocos com `main()` são programas separados; os menores indicam o contexto necessário.

## VI BINARY SEARCH NA RESPOSTA. E AGORA?

1. Defina `mid`: qual valor estou tentando?
2. Defina `verify(mid)`: dá para fazer o que o problema pede com esse valor?
3. Se funciona, maiores também funcionam? **FFFTTT → [first true](binary-search.md#first-true)**.
4. Se funciona, menores também funcionam? **TTTFFF → [last true](binary-search.md#last-true)**.
5. Justifique a regra e escolha limites que contenham a resposta. “Menor/maior” sozinho não basta.

<details>
<summary>Organização e testes (fora do contest)</summary>

## ARQUIVOS — GUIAS E RECEITAS SEM DUPLICAÇÃO

| Guia | Conteúdo |
|---|---|
| [binary-search.md](binary-search.md) | Linear, tradicional, bounds, first/last true e verify. |
| [two-pointers.md](two-pointers.md) | Soma, diferença, janela e merge. |
| [sweep-line.md](sweep-line.md) | Eventos, empates, consultas, estado e compressão. |
| [exhaustive-search.md](exhaustive-search.md) | Loops, subsets e permutações. |
| [backtracking.md](backtracking.md) | Escolher retorno + tipo de escolha. |
| [backtracking-templates.cpp](backtracking-templates.cpp) | Sete receitas com funções, sem main. |
| [patterns.md](patterns.md) | Comparações, custos e armadilhas. |

Estilo adaptado de `maratona/study/`: títulos curtos, passos e exemplos pequenos.
`study/` não foi alterada. Compressão está junto de sweep line, mas não é a mesma técnica.

Na raiz icpc: `python -B c++/test_search.py` e `python -B c++/test_backtracking.py`.

</details>
