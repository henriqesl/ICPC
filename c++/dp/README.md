# DP 1 — escolha pelo estado

[Consulta geral](../../README.md) · [Guia DP 1](dp-1.md) · [Checklist](dp-1.md#checklist)

**DP = estado + transições + casos base + resultados guardados.**
Pergunta principal: quais informações do passado ainda influenciam o futuro?

| Preciso... | Estado / condição | Abra o código |
|---|---|---|
| Entender recursão virando DP | Fibonacci; bruto só N pequeno; DP sem MOD até N=92 | [Bruto](fibonacci_bruteforce.cpp) · [memo](fibonacci_memo.cpp) · [iterativo](fibonacci_iterative.cpp) |
| Contar sequências de faces somando N | soma restante; ordem importa; MOD | [Bruto](dice_combinations_bruteforce.cpp) · [memo](dice_combinations_memo.cpp) · [iterativo](dice_combinations_iterative.cpp) |
| Contar subordinados de cada chefe | tamanho da subárvore; árvore enraizada em 1 | [Subordinates](subordinates.cpp) |
| Calcular jogadas esperadas | Pou; isole a dependência do próprio estado | [Valor esperado](expected_moves.cpp) |
| Saber se o jogador da vez vence | leva o adversário a perdedor; regras da aula | [Jogos](winning_states.cpp) |
| Saber se alguma escolha soma exatamente T | índice + soma restante; valores não negativos | [Subset Sum](subset_sum.cpp) |
| Menor custo de saltos de 1 ou 2 pedras | posição; alturas fixas | [Frog memo](frog_1.cpp) · [iterativo](frog_1_iterative.cpp) |
| Contar caminhos com obstáculos | linha + coluna; só baixo/direita; MOD | [Grid Paths](grid_paths.cpp) |
| Maximizar pontos sem repetir atividade seguida | dia + atividade anterior; pontos não negativos | [Vacation memo](vacation.cpp) · [iterativo](vacation_iterative.cpp) |
| Cortar retângulo em quadrados | altura + largura; mínimo | [Rectangle Cutting](rectangle_cutting.cpp) |
| Maior soma de trecho consecutivo não vazio | melhor soma terminando aqui; aceita negativos | [Kadane](kadane.cpp) |
| Escolher itens com maior valor dentro da capacidade | índice + capacidade; cada item no máximo uma vez | [Knapsack 0/1](knapsack_01.cpp) |
| Maior subsequência comum entre duas strings | dois índices; preserva ordem, pode pular | [LCS tamanho](lcs.cpp) · [reconstrução](lcs_reconstruct.cpp) |
| Maior subsequência estritamente crescente | índice + anterior; versão O(N²) da aula | [LIS](lis.cpp) |

## Antes de copiar

- Os `.cpp` são programas independentes: entrada/saída e hipóteses estão no topo.
- As versões memoizadas usam recursão clássica; a pilha também tem limite.
- Para Dice, Frog e Vacation com N grande, há versões iterativas separadas.
- O custo da tabela importa: Subset Sum e Knapsack não servem para alvo/capacidade enormes.
- `-1` significa não calculado nos exemplos, cujas respostas são não negativas.
- Cada arquivo termina com **COMO LER ESTE CÓDIGO**, sem explicar cada linha trivial.

<details>
<summary>Organização e testes (fora do contest)</summary>

Base: Aula 5 — DP 1, MaratonaCIn, rev. 1.1; Frog, Grid Paths, Vacation e
Rectangle Cutting são os complementos clássicos solicitados.
O [guia](dp-1.md) reúne reconhecimento, recorrências, diferenças entre as formas e erros comuns.

Na raiz `icpc`: `python -B c++/test_dp.py`.
Compila todos os programas C++17 com warnings e compara casos pequenos com oráculos.

</details>
