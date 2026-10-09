# BUSCA EXAUSTIVA — tente todas as escolhas

[Índice](README.md) · [Pares/trios](#pares) · [Subconjuntos/bitmask](#subconjuntos) · [Permutações](#permutacoes)

## NECESSIDADE / RECONHECIMENTO

N pequeno e não vejo como descartar escolhas com segurança. Estime o número de estados antes de codar.
Também serve como solução lenta para testar uma solução mais rápida em entradas pequenas.
**Complete search / exhaustive search** significa explorar todas as possibilidades relevantes;
loops, máscaras e permutações são formas diferentes de fazer isso.

| Escolhas | Técnica | Custo deste template |
|---|---|---|
| Dois índices distintos | Dois loops, i < j | O(N²) |
| Três índices distintos | Três loops, i < j < k | O(N³) |
| K posições fixas | K loops (K constante) | O(N^K) |
| Pegar ou não cada elemento | Máscara de bits | O(N · 2^N) |
| Todas as ordens | next_permutation | O(N · P), P <= N! |

N = 20 já dá cerca de 21 milhões de verificações de bits; 10! = 3.628.800 ordens.
São estimativas, não garantias de tempo: o trabalho por estado e a saída também contam.

<a id="pares"></a>
## A) LOOPS ANINHADOS — PARES

### IDEIA / TEMPLATE C++

Teste cada par de índices uma vez: j começa em i+1.
Entrada: N, alvo e N valores. Saída: quantidade de pares cuja soma é o alvo.
Não precisa ordenar; a soma de qualquer par deve caber em long long.

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

```text
Entrada: 3 4
         2 2 2
Saída:   3  (pares de índices: 0/1, 0/2, 1/2)
```

### COMPLEXIDADE / ARMADILHAS

O(N²), O(1) extra além do vetor O(N). Com j = 0, você contaria i/j e j/i e poderia usar i = j.
Só precisa achar um par e pode ordenar? [Two pointers](two-pointers.md#par) reduz a busca a O(N).

Para trios, acrescente um terceiro loop começando em j+1; por exemplo, com quatro índices,
há quatro trios distintos. Este trecho é independente do template de soma acima:

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

Loops escolhem uma **quantidade fixa** de índices/posições. Subconjuntos deixam cada elemento
entrar ou não e podem ter tamanhos diferentes. Se posições puderem repetir ou a ordem importar,
a regra i < j < k também precisa mudar.

<a id="subconjuntos"></a>
## B) SUBCONJUNTOS — MÁSCARA DE BITS

### IDEIA / TEMPLATE C++

Cada bit decide se um índice entra (1) ou não (0). Existem 2^N máscaras, inclusive o conjunto vazio.

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

Entrada: N, alvo e N valores; **0 <= N <= 20** neste exemplo, soma dos valores absolutos cabe em long long.
Saída: quantidade de subconjuntos de índices cuja soma é o alvo. Aceita valores negativos.

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

```text
Entrada: 3 3
         1 2 3
Saída:   2  ([1,2] e [3])
```

### COMPLEXIDADE / ARMADILHAS

O(N · 2^N), O(1) extra além do vetor O(N).
`1ULL` evita o limite de int, mas **não** permite shift >= 64 nem torna 2^N viável para N grande.
`1LL << n` também amplia o tipo, mas é signed: mantenha n <= 62 para esse limite positivo.
O template usa unsigned (`1ULL`) e N <= 20. Não confunda ampliar o tipo com reduzir o custo.
Valores iguais em posições distintas geram escolhas distintas. Para alvo 0, o vazio também conta;
se não puder, comece em mask = 1. Subconjunto não precisa ser consecutivo — não é janela.

<a id="permutacoes"></a>
## C) PERMUTAÇÕES — TODAS AS ORDENS

### IDEIA / TEMPLATE C++

Ordene primeiro; next_permutation visita as próximas ordens lexicográficas.
Use do/while para não perder a primeira. Entrada: string não vazia sem espaços.
Saída: uma permutação distinta por linha; para vetor, use a mesma ideia com v.begin()/v.end().

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

```text
Entrada: aba
Saída:   aab
         aba
         baa
```

### COMPLEXIDADE / ARMADILHAS

Para comprimento N e P permutações distintas, O(N · P) incluindo geração/saída;
no pior caso, **O(N · N!)**. A geração usa O(1) extra, além da string O(N).
Sort inicial: O(N log N).

- Sem ordenar primeiro, só visita as ordens seguintes e perde as anteriores.
- Repetidos reduzem P; next_permutation não repete a mesma sequência de valores.
- Imprimir todas as ordens pode custar mais do que avaliá-las. Geralmente o contest pede guardar a melhor.
- Se restrições permitem podar escolhas antes de completar uma ordem, considere backtracking;
  veja [como mapear retorno + escolhas](backtracking.md) e as [receitas C++](backtracking-templates.cpp).
  Poda não elimina automaticamente o pior caso exponencial/fatorial.
