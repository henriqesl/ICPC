# Algoritmos: quando aplicar

| Necessidade | Arquivo | Pré-condição / custo |
|---|---|---|
| Posição exata em sequência qualquer | [Busca linear](searching/linear-search.cpp) | O(N); retorna -1 se ausente |
| Primeiro valor >= alvo | [Busca binária](searching/binary-search-main.cpp) | crescente; busca O(log N) |
| Ordenar / comparar vizinhos | [Ordenação](sorting/sorting-example.cpp) | O(N log N); altera índices |
| Muitas somas de intervalos | [Prefix sum](prefix-sum/prefix-sum-main.cpp) | valores fixos; construção O(N), consulta O(1) |
| Dois valores com soma alvo | [Dois ponteiros](two-pointers/two-pointers.cpp) | crescente; O(N) |
| Máximo número de intervalos sem conflito | [Guloso](greedy/intervals.cpp) | sem pesos, início < fim; O(N log N) |

Em busca binária, resultado len(v) significa ausência de valor >= alvo;
para igualdade, confira índice válido E v[i]==alvo.
lower_bound/upper_bound retornam iteradores; a diferença entre eles conta
ocorrências em vetor ordenado.

sort não é estável; stable_sort preserva ordem dos empates. Para decrescente
use rbegin/rend ou greater<int>(). Comparador deve usar <, nunca <=.

Prefix sum usa prefix[r+1]-prefix[l] para intervalo inclusivo base zero.
Se valores mudarem, o pré-processamento fica desatualizado.

Dois ponteiros descarta uma ponta porque os dados estão ordenados.
Guloso precisa de prova da escolha local; o exemplo contém o argumento de troca.
[Equivalentes Python](../../python/algorithms/README.md).
