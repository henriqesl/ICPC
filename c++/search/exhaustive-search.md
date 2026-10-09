# BUSCA EXAUSTIVA — N pequeno, teste todas as escolhas

[Índice](README.md) · [Pares/trios](#pares) · [Bitmask](#subconjuntos) · [Permutações](#permutacoes) · [Backtracking](backtracking.md)

| Escolhas | Template | Custo |
|---|---|---|
| Dois / três índices distintos | loops com i < j < k | O(N²) / O(N³) |
| Cada elemento entra ou não | máscara de bits | O(N·2^N) |
| Todas as ordens | next_permutation | O(N·P), P <= N! |

Estime antes: N=20 dá ~1 milhão de máscaras (~21 milhões de testes de bits); 10! dá ~3,6 milhões de ordens.
Conte também trabalho por estado, casos de teste e saída. São estimativas, não garantia de tempo.

<a id="pares"></a>
## A) PARES / TRIOS — QUANTIDADE FIXA DE ÍNDICES

**Use:** avaliar cada par uma vez, sem repetir índices. Não precisa ordenar.

**Ideia:** j começa em i+1; para trios, k começa em j+1.

Entrada: N, alvo, N valores. Saída: quantidade de pares somando alvo. Somas cabem em long long.

<!-- search-example: exhaustive-pairs -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i] + v[j] == target) answer++;
        }
    }
    cout << answer << '\n';
}
```

**Custo:** O(N²), O(1) extra além do vetor O(N).

**Cuidado:** j=0 contaria i/j e j/i e permitiria i=j. Só achar um par? [Two pointers](two-pointers.md#par) pode reduzir.

Trios, recorte independente dentro do main:

<!-- search-example: exhaustive-triples -->
```cpp
int n = 4;
long long triples = 0;
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
            triples++; // avalie a escolha i, j, k aqui
        }
    }
}
cout << triples << '\n'; // 4
```

**Custo:** O(N³). Se ordem importa ou índices podem repetir, adapte i < j < k.

<details>
<summary>Entender melhor: exemplo</summary>

`[2,2,2]`, alvo 4 → 3 pares de índices: (0,1), (0,2), (1,2).
Loops escolhem uma quantidade fixa de índices; subconjuntos podem ter tamanhos diferentes.

</details>

<a id="subconjuntos"></a>
## B) SUBCONJUNTOS — BITMASK

**Use:** cada item pode entrar ou não; não precisa ser consecutivo.

**Ideia:** mask representa um subconjunto; o bit i ligado significa que v[i] entra.

**Precisa:** aqui 0 <= N <= 20; soma dos valores absolutos cabe em long long. Aceita negativos.

Entrada: N, alvo, N valores. Saída: quantidade de subconjuntos de índices cuja soma é o alvo.

<!-- search-example: exhaustive-subsets -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    unsigned long long total = 1ULL << n;
    long long answer = 0;
    for (unsigned long long mask = 0; mask < total; mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1ULL << i)) sum += v[i];
        }
        if (sum == target) answer++;
    }
    cout << answer << '\n';
}
```

**Custo:** O(N·2^N), O(1) extra além do vetor O(N).

**Cuidado:** vazio conta se alvo=0 (para excluir, comece mask=1). Valores iguais em índices diferentes são escolhas diferentes.
`1ULL << n` não permite shift >= 64; tipo maior não torna 2^N viável para N grande.

<details>
<summary>Entender melhor: mask, bit e exemplo</summary>

| Nome / expressão | Significado |
|---|---|
| mask | qual subconjunto estou processando; é o conjunto de bits |
| bit (ou i no código) | qual elemento da entrada estou olhando |
| `1ULL << bit` | máscara com **apenas** o bit desse elemento ligado |
| `mask & (1ULL << bit)` | resultado não zero se esse elemento está escolhido |

```text
N = 3; bits da direita para a esquerda correspondem aos índices 0, 1, 2:
000 → vazio        001 → {0}       010 → {1}       011 → {0,1}
100 → {2}          101 → {0,2}     110 → {1,2}     111 → {0,1,2}
mask = 5 = 101; olhando bit = 2:
1ULL << 2 = 100; 101 & 100 = 100 (não zero) → elemento 2 escolhido.
```


`[1,2,3]`, alvo 3 → 2 subconjuntos: [1,2] e [3].

</details>

<a id="permutacoes"></a>
## C) PERMUTAÇÕES — TODAS AS ORDENS

**Use:** importa em qual ordem os itens aparecem.

**Ideia:** sort primeiro; do/while visita a ordem inicial e todas as seguintes.

Entrada: string não vazia sem espaços. Saída: uma permutação distinta por linha.
Para vector, use v.begin()/v.end() da mesma forma.

<!-- search-example: exhaustive-permutations -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());

    do {
        cout << s << '\n'; // troque pela avaliação dessa ordem
    } while (next_permutation(s.begin(), s.end()));
}
```

**Custo:** O(N·P), P permutações distintas; pior caso O(N·N!), incluindo geração/saída.
String O(N); geração O(1) extra; sort inicial O(N log N).

**Cuidado:** sem sort perde ordens anteriores; sem do/while perde a primeira. Repetidos não duplicam a mesma sequência de valores.

<details>
<summary>Entender melhor: exemplo e quando podar</summary>

`aba` → `aab`, `aba`, `baa`.
Em contest, normalmente avalie/guarde a melhor ordem em vez de imprimir todas.
Se um prefixo já viola regras, [backtracking](backtracking.md#mapeamento) pode descartá-lo cedo; o pior caso continua exponencial/fatorial.

</details>
