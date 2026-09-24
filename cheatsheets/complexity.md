# Complexidade

| Complexidade | Ideia |
|---|---|
| `O(1)` | Operação fixa |
| `O(log N)` | Divide o espaço repetidamente |
| `O(N)` | Uma passagem |
| `O(N log N)` | Ordenações eficientes |
| `O(N²)` | Dois loops dependentes de `N` |
| `O(N³)` | Três loops dependentes de `N` |
| `O(2^N)` | Força bruta de subconjuntos |

Para `N` perto de `10^5`, procure `O(N log N)` ou melhor. Loops consecutivos somam custos; loops aninhados geralmente multiplicam. Um milhão de `int` ocupa cerca de 4 MB; `long long`, cerca de 8 MB por elemento.

