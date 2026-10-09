# TWO POINTERS — janela, soma, diferença e merge

[Índice](README.md) · [Janela](#janela) · [Two sum](#par) · [Two difference](#diferenca) · [Merge](#merge) · [Não confundir](#nao-confundir)

**Two Pointers NÃO é um único algoritmo.** É uma família de técnicas:
dois índices se movem de forma controlada, sem refazer todo o trabalho.

## NECESSIDADE / RECONHECIMENTO

| Pedido | Variante | Hipótese |
|---|---|---|
| Dois elementos somam um alvo | Pontas opostas | vetor ordenado crescente |
| Maior trecho consecutivo com soma <= S | Sliding window | valores não negativos, S >= 0 |
| Dois elementos têm diferença absoluta D | Mesma direção | vetor ordenado, D >= 0 |
| Juntar dois arrays em ordem | Merge | cada array já ordenado |

Gatilhos de janela: **subarray contínuo**, maior/menor segmento com uma condição,
limite de soma ou frequência. É preciso provar que expandir/contrair ajusta a validade
monotonicamente: nem toda condição permite uma janela de dois ponteiros.
Os templates de soma/diferença acham um par; o de janela abaixo maximiza o tamanho.
Para minimizar o tamanho com soma >= S (positivos), a atualização da resposta ocorre
enquanto a janela ainda é suficiente, antes de contrair — não copie a regra do máximo sem adaptar.

Não são a mesma implementação. Os ponteiros só dão O(N) quando avançam sem precisar voltar.

<a id="par"></a>
## A) PAR COM SOMA ALVO

### IDEIA

left começa no menor valor e right no maior.
Soma pequena → aumente left; soma grande → diminua right; igualdade → achou.
Como está ordenado, o lado descartado não poderia formar a soma desejada com as opções restantes.

### TEMPLATE C++

Entrada: N, alvo e N valores **já ordenados**. Saída: dois índices distintos (base 0), ou -1.
Valores e alvo podem ser negativos; assuma que a soma de qualquer par cabe em long long.

<!-- search-example: two-pointers-pair -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    int left = 0, right = n - 1;
    while (left < right) { // não pode usar o mesmo elemento duas vezes
        long long sum = v[left] + v[right];
        if (sum == target) {
            cout << left << ' ' << right << '\n';
            return 0;
        }
        if (sum < target) left++;
        else right--;
    }
    cout << -1 << '\n';
}
```

```text
Entrada: 4 9
         1 3 5 8
Saída:   0 3
```

### COMPLEXIDADE / ARMADILHAS

O(N) na busca, O(1) extra; ordenar antes custa O(N log N).
O vetor ocupa O(N). Para devolver índices originais, ordene pares (valor, índice),
como no [guia de ordenação](../algorithms/sorting.md).
Esse template acha **um par**; contar todos exige tratar repetições.

<a id="janela"></a>
## B) MAIOR JANELA COM SOMA LIMITADA

### IDEIA

right expande o trecho [left, right]. Se a soma ultrapassar S,
left remove elementos até a janela ficar válida. Registre seu tamanho.
Com não negativos, expandir nunca reduz a soma e remover nunca aumenta: por isso funciona.
**r expande; l contrai; ambos só avançam.** Em condições de frequência, mantenha
as contagens ao adicionar/remover; o critério de janela inválida muda, não o movimento.

### TEMPLATE C++

Entrada: N, S >= 0 e N valores não negativos; a soma total deve caber em long long.
Saída: tamanho do maior trecho com soma <= S (0 se nenhum elemento couber).

<!-- search-example: two-pointers-window -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long limit;
    cin >> n >> limit;
    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    long long sum = 0;
    int left = 0, answer = 0;
    for (int right = 0; right < n; right++) {
        sum += v[right];
        while (sum > limit) {
            sum -= v[left];
            left++;
        }
        answer = max(answer, right - left + 1);
    }
    cout << answer << '\n';
}
```

```text
Entrada: 5 5
         2 1 3 1 1
Saída:   3  (trecho [3,1,1])
```

### COMPLEXIDADE / ARMADILHAS

O(N), mesmo com o while: cada elemento entra uma vez e sai no máximo uma vez.
O(1) extra, além do vetor O(N).

- **Não ordene:** isso destruiria a ideia de trecho consecutivo original.
- **Com negativos, este template não serve.** Em [5,-4] e S = 1, ele elimina 5
  antes de ver -4 e perde o trecho inteiro, que teria soma 1.
- “Dois elementos quaisquer” não é “trecho consecutivo”: escolha a variante correta.
- Para janela de tamanho fixo ou outras condições, veja [prefix sum e sliding window](../algorithms/prefix-and-window.md).

Os executáveis anteriores continuam disponíveis: [par](../algorithms/two-pointers.cpp)
e [janela](../algorithms/sliding-window-variable.cpp). Não é necessário duplicá-los.

<a id="diferenca"></a>
## C) TWO DIFFERENCE — DIFERENÇA ALVO

### RECONHECIMENTO / IDEIA

Procuro dois índices distintos com diferença absoluta D >= 0 em um vetor ordenado.
Use l = 0, r = 1 e compare v[r] - v[l]. Diferença pequena → avance r;
grande → avance l; igual → achou. Se l alcançou r, avance r antes de comparar.
Para l fixo, aumentar r não diminui a diferença; para r fixo, aumentar l não a aumenta.

### TEMPLATE C++

Entrada: N, D >= 0 e N valores já ordenados. Saída: l r (base 0), ou -1.
Valores negativos são permitidos; **toda diferença testada precisa caber em long long**.
D = 0 exige dois elementos iguais em índices distintos, não o mesmo índice duas vezes.

<!-- search-example: two-pointers-difference -->
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll target;
    cin >> n >> target;
    vector<ll> v(n);
    for (ll &x : v) cin >> x;

    int l = 0, r = 1;
    while (l < n && r < n) {
        if (l == r) {
            r++;
            continue;
        }
        ll difference = v[r] - v[l];
        if (difference == target) {
            cout << l << ' ' << r << '\n';
            return 0;
        }
        if (difference < target) r++;
        else l++;
    }
    cout << -1 << '\n';
}
```

```text
Entrada: 4 3
         1 2 4 8
Saída:   0 2
```

### COMPLEXIDADE / ARMADILHAS

O(N) na busca, O(1) extra; sort prévio custa O(N log N). O vetor ocupa O(N).
Se o problema exige uma diferença **orientada por índices originais**, ordenar pode
destruir essa regra: este template trata valores/diferença absoluta, não a ordem original.
Não use a regra de two sum: aqui os dois ponteiros caminham na mesma direção.

<a id="merge"></a>
## D) MERGE — DOIS ARRAYS ORDENADOS

### IDEIA / TEMPLATE C++

Cada ponteiro pertence a um array. Copie o menor valor atual e avance só seu ponteiro;
quando um array acabar, copie o resto do outro. Não há subarray/janela nesse caso.
Entrada: N M, N valores de a e M valores de b, ambos já ordenados. Saída: união com repetições em ordem.

<!-- search-example: two-pointers-merge -->
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m), result;
    for (ll &x : a) cin >> x;
    for (ll &x : b) cin >> x;

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < n) result.push_back(a[i++]);
    while (j < m) result.push_back(b[j++]);

    for (ll x : result) cout << x << ' ';
    cout << '\n';
}
```

```text
Entrada: 3 2
         1 4 4
         2 4
Saída:   1 2 4 4 4
```

O(N+M), memória O(N+M) para o resultado; ponteiros usam O(1).
Não elimina repetidos automaticamente.

<a id="nao-confundir"></a>
## VARIANTES / NÃO CONFUNDIR

| Variante | Movimento | O que não esquecer |
|---|---|---|
| Two sum | extremidades se aproximam | ordenar; l < r |
| Two difference | ambos para a direita | ordenar; l != r |
| Janela variável | r expande, l contrai | preservar ordem; justificar validade monotônica |
| Janela fixa | entra um, sai um; tamanho K | [template existente](../algorithms/sliding-window-fixed.cpp), 1 <= K <= N |
| Merge | um índice por array | tratar a sobra de ambos |

Two pointers movimenta índices; **sliding window é um caso focado em segmento contínuo**.
Binary search [descarta metade do espaço](binary-search.md#tradicional); não avança um índice por vez.
Mover o ponteiro errado, esquecer sort no par ou usar janela com negativos são os erros mais comuns.
