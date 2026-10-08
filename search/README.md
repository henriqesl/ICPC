# BUSCA — consulta rápida para contest

**Necessidade → reconhecimento → algoritmo → template C++ → complexidade → armadilhas.**
Comece pela operação pedida, não pelo nome do algoritmo. Os exemplos são genéricos e usam C++17.

## O QUE PRECISO ENCONTRAR?

| Problema / necessidade | Técnica provável | Complexidade da busca |
|---|---|---|
| Procurar elemento sem nenhuma propriedade | [Busca linear](linear-search.md) | O(N) |
| Array ordenado + procurar valor exato | [Binary search tradicional](binary-search.md) | O(log N) |
| Primeiro elemento >= x | [lower_bound](bounds.md#lower-bound) | O(log N) |
| Primeiro elemento > x | [upper_bound](bounds.md#upper-bound) | O(log N) |
| Contar ocorrências em array ordenado | [upper_bound − lower_bound](bounds.md#contar) | O(log N) |
| Menor valor que satisfaz uma condição monotônica | [Na resposta / FIRST TRUE](binary-search-on-answer.md#first-true) | O(C · log(R+1)) |
| Maior valor que continua satisfazendo uma condição monotônica | [Na resposta / LAST TRUE](binary-search-on-answer.md#last-true) | O(C · log(R+1)) |

N = quantidade de elementos; R = quantidade de candidatos inteiros no intervalo;
C = custo de `verify(mid)`. Para N ou R >= 2, usamos a forma usual O(log N) / O(log R).
Se precisar ordenar, some **O(N log N)** uma vez. A tabela de bounds considera `vector` ordenado.

Frases do enunciado e teste de monotonicidade: [patterns.md](patterns.md).
Escolha de limites e erros de implementação: [na resposta](binary-search-on-answer.md#limites).

## CHECKLIST DE 20 SEGUNDOS

1. Estou procurando um valor existente ou uma resposta possível?
2. Os dados estão ordenados? Posso ordená-los sem perder informação necessária?
3. Existe uma condição monotônica: muda de false para true (ou vice-versa) no máximo uma vez?
4. Se x funciona, valores maiores também funcionam?
5. Se x funciona, valores menores também funcionam?
6. Quero o primeiro valor válido ou o último?
7. Consigo escrever `verify(x)` retornando apenas true/false, com custo aceitável?

Não basta o enunciado dizer “menor” ou “maior”. Sem monotonicidade, não use busca binária na resposta.

## ARQUIVOS

| Abra | Para quê? |
|---|---|
| [linear-search.md](linear-search.md) | Percorrer, localizar a primeira ocorrência e avaliar buscas repetidas. |
| [binary-search.md](binary-search.md) | Encontrar um valor exato em dados ordenados, usando left/right/mid. |
| [bounds.md](bounds.md) | Presença, limites, ocorrências e conversão de iterador para índice. |
| [binary-search-on-answer.md](binary-search-on-answer.md) | FIRST TRUE / LAST TRUE, verify, limites e armadilhas. |
| [patterns.md](patterns.md) | Associar frases a padrões, sem decorar sem entender. |

Os títulos curtos, exemplos pequenos e comentários por etapa seguem a referência de
`maratona/study/`, principalmente `binary_search/binary_search_answer.cpp` e `bounds/`.
Essa referência usa `.cpp`, não possui um template Markdown separado; aqui a explicação
vira Markdown com código compilável em blocos e exemplos neutros.
Os templates ficam em cada guia, sem uma segunda cópia para desatualizar.

Teste dos blocos C++ (na raiz `icpc/`): `python -B c++/test_search.py`.
[Voltar ao índice do repositório](../README.md).

## VI BINARY SEARCH NA RESPOSTA. E AGORA?

1. Escreva em uma frase: `mid = __________________` (tempo? capacidade? distância?).
2. Escreva: `verify(mid) = "__________________?"` (uma pergunta de viabilidade).
3. Imagine mid crescendo. Os resultados formam **FFFTTT** ou **TTTFFF**?
4. **FFFTTT → primeiro true**: se funciona, salve e tente MENOR.
5. **TTTFFF → último true**: se funciona, salve e tente MAIOR.
6. Defina l e r, justifique que contêm a resposta e decida como sinalizar “não existe”.
7. Só depois copie [FIRST TRUE](binary-search-on-answer.md#first-true) ou
   [LAST TRUE](binary-search-on-answer.md#last-true) e escreva o código.

```text
mid tem um significado
        ↓
verify(mid) testa se funciona
        ↓
monotonicidade define o lado que pode ser descartado
        ↓
first true OU last true → limites → código
```
