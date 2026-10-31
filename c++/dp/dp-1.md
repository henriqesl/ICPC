# Programação Dinâmica — DP 1

[Índice e códigos](README.md) · [Reconhecer DP](#reconhecer) · [Checklist](#checklist) · [Erros](#erros)

Base: Aula 5 — DP 1 da MaratonaCIn, rev. 1.1, com os exercícios clássicos complementares solicitados.
Os programas completos ficam nos `.cpp`; os trechos abaixo destacam só o núcleo.
Algoritmos-base ficam em `dp/`; soluções dos exercícios, em [exercises/](exercises/README.md).

<a id="ideia"></a>
## 1. Ideia central

**DP = estados + transições + casos base + armazenamento de resultados.**

| Peça | Pergunta |
|---|---|
| Estado | O que exatamente `solve(...)` retorna nessa situação? |
| Transição | Que escolhas levam aos próximos estados? |
| Caso base | Quando sei a resposta sem fazer outra chamada? |
| Memo/tabela | Esse estado já foi calculado? Onde guardo sua resposta? |

**Regra mental:** quais informações do passado ainda influenciam o futuro?
Uma informação pode bastar para `dp[i]`; duas podem exigir `dp[i][j]`.
Não guarde o histórico inteiro, mas não descarte algo que muda as opções futuras.
Ex.: em Vacation, o dia não basta: a atividade anterior restringe a próxima.

Força bruta recursiva explora escolhas. Quando caminhos diferentes chegam ao
mesmo estado, memoizar evita refazer toda a continuação. Isso transforma a árvore
de chamadas em estados reutilizados; não torna qualquer exponencial automaticamente viável.

| Forma | Ordem | Como evita repetir |
|---|---|---|
| Top-down | começa na pergunta; recursão busca dependências | consulta memo antes de calcular |
| Bottom-up | começa nas bases; laços respeitam dependências | escreve cada posição da tabela na ordem certa |

Mesmo estado e recorrência; muda a ordem de avaliação. Top-down tem pilha recursiva.
Bottom-up nem sempre significa ordem crescente: Vacation calcula os dias de trás para frente.

<a id="fibonacci"></a>
## 2. Fibonacci

**Estado:** `F(n)`. **Base:** `F(0)=0`, `F(1)=1`.
**Transição:** `F(n)=F(n-1)+F(n-2)`.

```text
F(4)
|-- F(3)
|   |-- F(2) -> F(1), F(0)
|   `-- F(1)
`-- F(2)     -> F(1), F(0)  [repetiu F(2)]
```

[Bruto completo](fibonacci_bruteforce.cpp): O(2^N), limite superior; pilha O(N).

<!-- dp-example: fib-brute -->
```cpp
long long solve(int n) {
    if (n <= 1) return n;
    return solve(n - 1) + solve(n - 2);
}
```

[Top-down completo](fibonacci_memo.cpp): `memo` global de N+1 posições, iniciado com -1.

<!-- dp-example: fib-memo -->
```cpp
vector<long long> memo;
long long solve(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n - 1) + solve(n - 2);
}
```

[Bottom-up completo](fibonacci_iterative.cpp): trecho dentro do `main`, com `n` já lido.

<!-- dp-example: fib-iterative -->
```cpp
vector<long long> dp(n + 1, 0);
if (n >= 1) dp[1] = 1;
for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
cout << dp[n] << '\n';
```

As duas DPs custam O(N) tempo/memória. **Sem MOD:** `long long` só comporta até F(92).
A versão bruta é apenas demonstração; não rode para N grande.

<a id="dice"></a>
## 3. Dice Combinations

**Pedido:** contar sequências de faces 1..6 cuja soma é N; **a ordem importa**.
**Estado:** `C(sum)` = maneiras de completar a soma restante.

```text
C(sum) = C(sum-1)+C(sum-2)+C(sum-3)+C(sum-4)+C(sum-5)+C(sum-6)
C(0) = 1   [a sequência já foi completada]
C(sum < 0) = 0
```

[Bruto completo](exercises/dice_combinations_bruteforce.cpp): O(6^N), limite superior; pilha O(N).

<!-- dp-example: dice-brute -->
```cpp
const int MOD = 1000000007;
int solve(int sum) {
    if (sum == 0) return 1;
    if (sum < 0) return 0;
    int ans = 0;
    for (int face = 1; face <= 6; face++) ans = (ans + solve(sum - face)) % MOD;
    return ans;
}
```

[Memo completo](exercises/dice_combinations_memo.cpp): mesmas chamadas, cache por soma.

<!-- dp-example: dice-memo -->
```cpp
const int MOD = 1000000007;
vector<int> memo;
int solve(int sum) {
    if (sum == 0) return 1;
    if (sum < 0) return 0;
    if (memo[sum] != -1) return memo[sum];
    int ans = 0;
    for (int face = 1; face <= 6; face++) ans = (ans + solve(sum - face)) % MOD;
    return memo[sum] = ans;
}
```

[Iterativo completo](exercises/dice_combinations_iterative.cpp): trecho dentro do `main`, com `n` lido.

<!-- dp-example: dice-iterative -->
```cpp
const int MOD = 1000000007;
vector<int> dp(n + 1, 0);
dp[0] = 1;
for (int sum = 1; sum <= n; sum++) {
    for (int face = 1; face <= 6; face++) {
        if (sum >= face) dp[sum] = (dp[sum] + dp[sum - face]) % MOD;
    }
}
cout << dp[n] << '\n';
```

O `for` de 1 a 6 só compacta as seis transições. DP: O(6N)=O(N) tempo, O(N) memória.
N=3 → `111,12,21,3`: 4 maneiras. Trocar a ordem dos laços pode passar a contar outro problema.
N grande, como 10^6, pede a versão iterativa: memo não elimina a pilha O(N).

<a id="arvore"></a>
## 4. DP em árvore — Subordinates

[Código: DFS recursiva + memo](exercises/subordinates.cpp).

- **Estado:** `dp[u]` = tamanho da subárvore de u, **incluindo u**.
- **Base:** folha vale 1.
- **Transição:** `dp[u] = 1 + soma(dp[filho])`.
- **Saída:** subordinados = `dp[u]-1`.
- **Custo:** O(N) tempo/memória; uma hierarquia em cadeia pode exigir pilha O(N).

Os filhos são calculados antes de completar o pai. Em uma árvore, a DFS já visita
cada nó uma vez: DP em árvore não precisa necessariamente ter estados recomputados.

<a id="probabilidade"></a>
## 5. DP com probabilidade — Pou

[Código](exercises/expected_moves.cpp). Estado `E(i)` = jogadas esperadas restantes até n.
Em cada jogada, fica em i com probabilidade `1/k`, ou avança a i+1.

```text
E(n) = 0
E(i) = 1 + (1/k)*E(i) + (1-1/k)*E(i+1)
(1-1/k)*E(i) = 1 + (1-1/k)*E(i+1)
E(i) = k/(k-1) + E(i+1), para k>1
```

O 1 conta a jogada atual. **Isole o próprio estado antes de implementar:** chamar
`solve(i)` dentro de `solve(i)` recursa para sempre, mesmo com memo.
Use `double`. N=3, k=2 → esperança 6. Se k=1 e falta avançar, a esperança é infinita.
O(N) tempo/memória na DP; neste exemplo específico, a fórmula fechada é `n*k/(k-1)`.

<a id="jogos"></a>
## 6. DP em jogos

[Código direto da regra da aula](exercises/winning_states.cpp): de i, retire entre 1 e `floor((i+1)/2)`.

- **Estado:** `dp[i]` indica se quem joga agora consegue vencer.
- **Base:** `dp[0]=0`, perdedor: sem jogada, perde.
- **Transição:** vencedor se **existe** jogada para algum `dp[i-j]=0`.
- Se todas as jogadas deixam o adversário em vencedor, o estado é perdedor.
- O(N²) tempo/O(N) memória na versão direta. A aula também otimiza a busca por perdedor na janela.

Cada estado já considera que o jogador seguinte também joga da melhor forma.
As remoções permitidas mudam conforme o problema; não copie essa regra para todo jogo.

<a id="subset-sum"></a>
## 7. Subset Sum

[Código top-down](subset_sum.cpp). Array não negativo; cada índice entra no máximo uma vez.

**Bruto:** pegar/não pegar cada elemento → O(2^N) chamadas com atualização O(1) da soma.

```text
solve(i,sum): existe solução com os itens i..n-1, faltando sum?
sum == 0 -> true
i == n ou sum < 0 -> false
solve(i,sum) = solve(i+1,sum) OR solve(i+1,sum-a[i])
```

Dois caminhos podem chegar ao mesmo `(i,sum)`: guarde ambos os índices no memo.
O(N*(T+1)) tempo/memória; pilha O(N). É pseudo-polinomial: T enorme não cabe na tabela.
Ex.: `[3,34,4,12,5,2]`, T=9 → SIM (4+5). O vazio é válido para alvo 0.

<a id="frog"></a>
## 8. Frog — minimização

[Top-down](exercises/frog_1.cpp) · [bottom-up](exercises/frog_1_iterative.cpp).

**Estado:** `dp[i]` = menor custo para chegar à pedra i (base 0).
**Base:** `dp[0]=0`. Para i>=1:

```text
dp[i] = min(dp[i-1]+abs(h[i]-h[i-1]),
            dp[i-2]+abs(h[i]-h[i-2]))  [segunda opção só se i>=2]
```

Só i basta: as alturas e os próximos saltos não dependem do caminho anterior.
`[10,30,40,20]` → 30. O(N) tempo/memória; top-down tem pilha O(N).
O último índice é n-1: chame `solve(n-1)`, não `solve(n)`.

<a id="grid"></a>
## 9. Grid Paths

[Código](exercises/grid_paths.cpp): grid quadrado, `*` bloqueado, movimentos baixo/direita.

- **Estado:** `dp[row][col]` = caminhos dessa célula até o destino.
- **Bases, nessa ordem:** fora → 0; obstáculo → 0; destino livre → 1.
- **Transição:** `solve(row+1,col) + solve(row,col+1)`, módulo 1e9+7.
- **Custo:** O(N²) tempo/tabela, pilha O(N); retangular seria O(linhas*colunas).

**Valide os limites antes de acessar `grid[row][col]`.** O destino bloqueado
não conta caminho. Grid 2x2 livre → 2; grid 1x1 livre → 1.

<a id="vacation"></a>
## 10. Vacation

[Memoização recursiva](exercises/vacation.cpp) · [alternativa iterativa](exercises/vacation_iterative.cpp).

**Estado:** `dp[day][last]` = maior felicidade a partir de day, sabendo a atividade anterior.
**Base:** `day==n` → 0.
**Transição:** testar atividades A/B/C diferentes de last e maximizar
`points[day][activity]+solve(day+1,activity)`.

`last=3` significa nenhuma atividade anterior: `solve(0,3)` permite as três no primeiro dia.
São 4 estados por dia e até 3 transições: O(N) tempo/memória; recursão O(N).
Os templates assumem pontos não negativos. Escolher o maior ponto de cada dia isolado não basta.

<a id="rectangle"></a>
## 11. Rectangle Cutting

[Código](exercises/rectangle_cutting.cpp). **Estado:** `dp[a][b]` = mínimo de cortes para obter quadrados.
**Base:** `a==b` → 0.

```text
Horizontal em i: 1 + dp[i][b] + dp[a-i][b], 1 <= i < a
Vertical em i:   1 + dp[a][i] + dp[a][b-i], 1 <= i < b
```

Teste todos e use **min**. O +1 é o corte atual; somam-se as duas partes de
UMA divisão, não todas as divisões possíveis. Inicialize o mínimo com INF.
2x3 → 2 cortes. O(A*B*(A+B)) tempo, O(A*B) tabela; pilha O(A+B).

<a id="kadane"></a>
## 12. Kadane

[Código curto](kadane.cpp). Maior soma de subarray contíguo **não vazio**.

**Estado conceitual:** melhor soma de um trecho que termina em i.

```text
curr = max(a[i], curr+a[i])  [começar aqui ou estender o anterior]
ans = max(ans,curr)         [melhor de todas as posições]
```

Só precisamos do estado anterior: comprimimos a tabela em `curr` e `ans`.
Ambos começam em `a[0]`, não em 0: `[-5,-2,-8]` → -2.
O(N) tempo/O(1) memória. Subarray é consecutivo; subsequência pode pular posições.

<a id="knapsack"></a>
## 13. Knapsack 0/1

[Código top-down](knapsack_01.cpp). N itens, peso/valor, capacidade W; maximizar valor sem ultrapassar W.

**Bruto:** pega/não pega → O(2^N). **Estado:** `(i,cap)` = item atual + capacidade restante.

```text
solve(n,cap) = 0
Não pegar: solve(i+1,cap)
Pegar, se weight[i]<=cap: value[i]+solve(i+1,cap-weight[i])
Resposta = max das opções válidas
```

Os dois ramos avançam i: não reutiliza o item. O(N*(W+1)) tempo/memória, pilha O(N).
Peso/valor não negativos; aceita peso zero, então `cap==0` NÃO é base suficiente.
Capacidade enorme inviabiliza a tabela. Knapsack ilimitado é outra variante.

<a id="lcs"></a>
## 14. Longest Common Subsequence — LCS

[Só tamanho](lcs.cpp) · [reconstruir uma LCS](lcs_reconstruct.cpp).

**Pedido:** maior sequência presente nas duas strings, preservando a ordem;
pode pular caracteres. Não é maior substring comum.

```text
solve(i,j): tamanho da LCS entre a[i..] e b[j..]
i==n ou j==m -> 0
a[i]==b[j] -> 1+solve(i+1,j+1)
senão -> max(solve(i+1,j), solve(i,j+1))
```

O(NM) para preencher estados; com leitura/reconstrução, O(NM+N+M).
Tabela O(NM), pilha O(N+M). `ABCDGH` e `AEDFHR` → tamanho 3, uma LCS é `ADH`.

### Reconstrução

1. Comece em `(0,0)`.
2. Caracteres iguais: acrescente o caractere e avance ambos.
3. Diferentes: siga o vizinho com maior resposta ótima; empate permite qualquer lado.
4. Pare quando uma string acabar.

No top-down, consulte `solve(vizinho)`, não um `memo` possivelmente ainda em -1.
Também seria possível guardar a transição escolhida, como nos slides.

### Aplicação: Longest Palindromic Subsequence

O **tamanho** da LPS de s é o tamanho de `LCS(s,reversa(s))`.
Ex.: `bbbab` → 4 (`bbbb`). Para obter a string palíndroma, não suponha que
uma LCS arbitrária reconstruída contra a reversa será sempre palíndroma.

<a id="reconhecer"></a>
## 15. Como reconhecer DP

- A força bruta cria várias escolhas? Os mesmos estados aparecem por caminhos diferentes?
- Poucas variáveis descrevem completamente a situação e o futuro?
- A resposta depende de estados menores, ou de uma ordem de dependências válida?
- O número de estados vezes as transições cabe no tempo e na memória?

| Problema | Estado | Operação |
|---|---|---|
| Fibonacci | n | soma |
| Dice | soma restante | soma |
| Frog | posição | mínimo |
| Subordinates | vértice | soma dos filhos + 1 |
| Subset Sum | índice, soma restante | OR |
| Vacation | dia, anterior | máximo |
| Rectangle Cutting | altura, largura | mínimo entre cortes |
| Knapsack | índice, capacidade | máximo |
| LCS | i, j | +1 / máximo |
| Grid Paths | linha, coluna | soma |
| Kadane | posição; melhor soma terminando nela | máximo |
| Jogos | quantidade restante | existe movimento para perdedor |

Não basta aparecer “mínimo/máximo”: pode ser BFS, Dijkstra ou guloso.
Identifique a recorrência e o que torna dois estados equivalentes.

<a id="checklist"></a>
## 16. Checklist de implementação

- O que `solve(...)` significa? Qual o estado e quantas dimensões?
- Quais são as bases e as transições?
- É soma, OR, min ou max? Falta o custo/ganho da escolha atual?
- Consultei o memo? O marcador pode ser uma resposta válida?
- Verifiquei limites antes de ler o vetor?
- Preciso de MOD, `long long`, `double` ou INF?
- Estados × transições cabe? Tabela e pilha cabem?
- Reiniciei memo e globais para outro caso de teste?

<a id="erros"></a>
## 17. Erros comuns

| Erro | Correção curta |
|---|---|
| `memo[i]` em Subset Sum | o estado é `(i,sum)`; mesma posição com somas diferentes não é equivalente |
| Esquecer base / chamar o próprio estado | garanta término; no valor esperado, isole a equação |
| Ler grid/memo antes dos limites | valide índices primeiro |
| Usar sempre base 1 | Dice(0)=1; Frog(0)=0; esperança no destino=0: depende do significado |
| Somar quando é min/max | soma conta opções; min/max escolhe uma delas |
| Esquecer ganho/custo atual | Knapsack soma value[i]; Rectangle soma +1 do corte |
| Não aplicar MOD | contagens crescem rápido; aplique em cada transição |
| Inicializar mínimo em 0 | use INF; no máximo, 0 só é seguro sob as hipóteses certas |
| Máximo 0 com todos negativos | Kadane não vazio começa no primeiro valor |
| `solve(n)` no Frog | último índice é n-1 |
| Confundir subsequência e subarray | LCS/LIS podem pular; Kadane precisa de trecho contíguo |
| Achar que memo resolve toda entrada | N grande pode estourar pilha; alvo/capacidade grandes estouram tabela |

<a id="lis"></a>
## 18. Complemento da própria aula — LIS

[Código O(N²)](lis.cpp). **Estado:** `(i,prev)`; prev é o índice do último escolhido.
Ignore i, ou pegue se `prev==-1 || a[i]>a[prev]`, acrescentando 1 e fazendo prev=i.
Base i==n → 0; resposta `solve(0,-1)`.

Guarde em `memo[i][prev+1]` para representar o anterior -1 sem índice negativo.
`[10,2,5,3,7,18]` → 4. Estritamente crescente não aceita repetir valor.
A versão O(N log N) citada como exercício na aula não substitui esta DP didática.
