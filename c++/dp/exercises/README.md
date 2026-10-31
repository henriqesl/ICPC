# DP 1 — exercícios de aplicação

[Códigos-base](../README.md) · [Guia DP 1](../dp-1.md)

Cada `.cpp` é um programa independente, com entrada, saída e complexidade no topo.
As variantes recursiva e iterativa ficam em arquivos separados.

| Exercício | Estado / ideia | Solução |
|---|---|---|
| Dice Combinations | soma restante; contar sequências ordenadas com MOD | [Bruto](dice_combinations_bruteforce.cpp) · [memo](dice_combinations_memo.cpp) · [iterativo](dice_combinations_iterative.cpp) |
| Subordinates | tamanho da subárvore de cada chefe | [DFS + DP](subordinates.cpp) |
| Pou — valor esperado | isolar a equação que depende do próprio estado | [Código](expected_moves.cpp) |
| Jogo da aula | existe jogada para deixar o adversário em perdedor | [Código](winning_states.cpp) |
| Frog 1 | menor custo de chegar à pedra i | [Memo](frog_1.cpp) · [iterativo](frog_1_iterative.cpp) |
| Grid Paths | contar caminhos por baixo/direita, com obstáculos e MOD | [Código](grid_paths.cpp) |
| Vacation | dia + atividade anterior; maximizar felicidade | [Memo](vacation.cpp) · [iterativo](vacation_iterative.cpp) |
| Rectangle Cutting | mínimo entre cortes horizontais e verticais | [Código](rectangle_cutting.cpp) |

Para testes, na raiz `icpc`: `python -B c++/test_dp.py`.
