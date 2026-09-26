# Tempo, memória e erros frequentes

| N | N log2 N (aprox.) | N² | N³ |
|---|---:|---:|---:|
| 100 | 664 | 10 mil | 1 milhão |
| 1.000 | 9.966 | 1 milhão | 1 bilhão |
| 100.000 | 1,66 milhão | 10 bilhões | 10^15 |

O(1) fixo; O(log N) reduz candidatos; O(N) percorre; O(2^N) enumera
subconjuntos (2^30 já passa de 1 bilhão). Não há limite universal de operações.
Alocações, mapas, strings e cache mudam bastante o tempo.
Dois loops consecutivos somam; dois ponteiros que só avançam podem ser O(N)
mesmo com while dentro de while.

Memória dos dados: N*sizeof(T). Com int de 4 bytes, 10^6 inteiros = 4 MB
(~3,81 MiB); long long de 8 bytes = 8 MB. Matriz N*M multiplica esse custo.
Vector pode ter capacity maior que size; map/set têm nós e ponteiros adicionais.
Prefira vector a arrays locais gigantes, que podem estourar a pilha.

| Erro | Correção prática |
|---|---|
| int total; total += x; | inicialize total = 0 |
| long long p = a*b; com int | 1LL*a*b, e confira limite de long long |
| if (x = 2) | x == 2 |
| v[v.size()] | último é v.back(), somente se não vazio |
| unsigned size()-1 com vazio | teste empty antes; cuidado com underflow |
| bool ok redefinido a cada passo | acumule: ok = ok && condicao |
| double x = 1/2 | 1.0/2 |
| usar iterador após erase | use o retorno de erase ou refaça a busca |
| sort destrói posições originais | armazene pair<valor,indice> |
| variável declarada dentro de if | declare fora se precisa depois |
| comparar decimais sempre com == | analise tolerância permitida pelo problema |
| while sem progresso | confira se intervalo/contador muda |

Compilação de treino: -std=c++17 -Wall -Wextra -Wpedantic -g -O0.
Opcional no GCC: -D_GLIBCXX_DEBUG para detectar alguns usos inválidos da STL.
assert documenta hipóteses, mas some com -DNDEBUG.
No GDB: break main, run, next, print variavel, continue, quit.
Diagnóstico: cerr << valor << '\n'; remova antes de submeter.
