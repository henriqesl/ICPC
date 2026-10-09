# SEARCH — consulta rápida de C++ para contest

**Enunciado/padrão → reconhecimento → ideia → template C++ → complexidade → armadilhas.**
Todos os exemplos são neutros. Use os links para saltar ao padrão, sem ler o arquivo inteiro.

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

Custos e diferenças entre técnicas: [tabelas de consulta](patterns.md#complexidades).
Os blocos com main são programas independentes; os trechos menores indicam o contexto necessário.

## CHECKLIST DE 20 SEGUNDOS

1. Estou procurando um valor existente ou uma resposta possível?
2. Os dados estão ordenados? Posso ordenar sem destruir a informação necessária?
3. Existe monotonicidade? Se x funciona, maiores ou menores também funcionam?
4. Estou lidando com um segmento contínuo?
5. Tenho dois índices que só precisam avançar?
6. Tenho intervalos/eventos ao longo de uma linha ou do tempo?
7. As coordenadas são enormes, mas poucas são relevantes?
8. Preciso saber apenas **QUANTOS** estão ativos ou **QUAIS** estão ativos?
9. N é pequeno o suficiente para testar todas as possibilidades e o trabalho por estado?
10. Cada elemento é escolhido/não escolhido?
11. A ordem dos elementos importa?

“Menor”, “maior” e “contínuo” são pistas, não provas.
Confira as hipóteses antes de copiar: monotonicidade, ordenação, sinal dos valores e extremos dos intervalos.

## ARQUIVOS — SEIS GUIAS, SEM CÓPIAS DO MESMO TEMPLATE

| Abra | Conteúdo |
|---|---|
| [binary-search.md](binary-search.md) | Linear, tradicional, STL/bounds, first/last true, verify e limites. |
| [two-pointers.md](two-pointers.md) | Sliding window, two sum, two difference, merge e variantes. |
| [sweep-line.md](sweep-line.md) | Receita, eventos, consultas, empates, estado ativo e compressão. |
| [exhaustive-search.md](exhaustive-search.md) | Complete search, pares/trios, subsets/bitmask e permutations. |
| [patterns.md](patterns.md) | Gatilhos, comparações, complexidades e checklist de armadilhas. |

O padrão visual vem de `maratona/study/`: títulos curtos, passos, exemplos pequenos
e comentários que explicam a ação. Referências principais:
`binary_search/binary_search_answer.cpp` e `sweep_line.cpp`, complementadas por
`two_pointers.cpp`, `coord_compress.cpp`, `bounds/` e `exaustion_search/`.
Não há um template Markdown separado em study/; adaptamos seu padrão de C++ comentado.

Busca linear, bounds e busca na resposta foram unificadas em binary-search.md;
compressão ficou em sweep-line.md, mas **não é sweep line**.
Todos os templates existentes foram mantidos uma vez, e os links foram atualizados.

Teste na raiz icpc/: `python -B c++/test_search.py`.
[Índice de C++](../README.md) · [Índice do repositório](../../README.md).

## VI BINARY SEARCH NA RESPOSTA. E AGORA?

1. Escreva: `mid = __________________` (tempo, capacidade, distância, tamanho?).
2. Escreva: `verify(mid) = "__________________?"` (uma pergunta de viabilidade).
3. Imagine mid crescendo: **FFFTTT** ou **TTTFFF**? Justifique, não apenas desenhe.
4. **FFFTTT → primeiro true:** funciona? salve e tente MENOR.
5. **TTTFFF → último true:** funciona? salve e tente MAIOR.
6. Defina l e r, prove que contêm a resposta e sinalize “não existe”.
7. Só depois copie [FIRST TRUE](binary-search.md#first-true) ou [LAST TRUE](binary-search.md#last-true).

Não existe vetor obrigatório de respostas: l/r representam o intervalo.
