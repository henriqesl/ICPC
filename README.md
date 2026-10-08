# ICPC Library

C++17 é a linguagem principal; Python 3 é complementar.

Está com uma questão em mãos? Abra [O QUE O ENUNCIADO ESTÁ ME PEDINDO?](MAPA-DE-RESOLUCAO.md#o-que-o-enunciado-está-me-pedindo)
e procure uma frase parecida. Confira também as [pegadinhas](MAPA-DE-RESOLUCAO.md#parece-x-mas-é-y)
e o [checklist de 20 segundos](MAPA-DE-RESOLUCAO.md#checklist-de-20-segundos-antes-de-codar).

Já sabe quais operações precisa repetir? Abra [QUAL ESTRUTURA USAR?](QUAL-ESTRUTURA-USAR.md):
escolha por operação, compare os custos e confira as limitações.

Precisa reconhecer uma **busca ou varredura**? Abra [c++/search/](c++/search/README.md):
buscas, bounds, two pointers, sweep line, compressão e busca exaustiva.

| Linguagem | Conteúdo |
|---|---|
| [c++/](c++/README.md) | Referências de C++17, estruturas, algoritmos, matemática, aplicações e template. |
| [python/](python/README.md) | Referências de Python 3, coleções, algoritmos, matemática, performance e template. |

## Contest Quick Reference

| Preciso... | C++17 | Python 3 |
|---|---|---|
| Sintaxe, tipos e funções | [Referência](c++/basics/cpp.md) | [Referência](python/cheatsheets/python.md) |
| Vetores/listas, sets, mapas, filas e heap | [Estruturas](c++/basics/collections.md) | [Coleções](python/cheatsheets/python-collections.md) |
| lower_bound / upper_bound: primeiro >= X / > X | [Lower](c++/algorithms/patterns.md#lower-bound), [upper](c++/algorithms/patterns.md#upper-bound), [bounds.cpp](c++/algorithms/bounds.cpp) | [Bisect](python/algorithms/README.md#bisect-limite-não-é-presença) |
| Strings e conversões | [Strings](c++/basics/strings.md) | [Strings](python/cheatsheets/python-strings.md) |
| Algoritmos e aplicações | [Algoritmos](c++/algorithms/README.md) | [Algoritmos](python/algorithms/README.md) |
| Sort por campo/coluna, trecho ou índice original | [Variantes de sort](c++/algorithms/sorting.md) | — |
| Iteradores: begin/end, *it, it->, converter para índice | [Guia](c++/basics/iterators.md) | — |
| Primeiro menor/maior / máximo de cada janela | [Stack](c++/algorithms/patterns.md#monotonic-stack) / [deque monotônicas](c++/algorithms/patterns.md#monotonic-deque) | — |
| Matemática | [Matemática](c++/math/README.md) | [Matemática](python/math/README.md) |
| Aprender prefix sum e sliding window | [Guia passo a passo](c++/algorithms/prefix-and-window.md) | [Exemplos](python/algorithms/README.md) |
| Começar solução | [template.cpp](c++/template.cpp) | [template.py](python/templates/template.py) |

## Dificuldade

- **Básico:** entrada/saída, strings, sequências, ordenação, pilhas e filas.
- **Intermediário:** sets/mapas, heaps, comparadores, busca binária, prefix sum, sliding window, dois ponteiros, pilha/deque monotônicas, mediana dinâmica, guloso e teoria dos números.
- **Avançado — futuro:** grafos, programação dinâmica e geometria.

As implementações equivalentes usam os mesmos conceitos. Veja [C++ × Python](python/cheatsheets/cpp-python.md)
para diferenças de comportamento. Cada trilha contém seu índice completo e comandos de teste.
