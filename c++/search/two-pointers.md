# TWO POINTERS — escolha a variante

[Índice](README.md) · [Par](#par) · [Janela](#janela) · [Diferença](#diferenca) · [Merge](#merge) · [Comparação](#nao-confundir)

| Pedido | Movimento | Condição obrigatória |
|---|---|---|
| Dois valores somam alvo | pontas se aproximam | ordenado crescente |
| Maior trecho com soma <= S | direita expande, esquerda contrai | não negativos; S >= 0 |
| Dois valores têm diferença absoluta D | ambos avançam | ordenado; D >= 0 |
| Juntar arrays ordenados | um índice por array | ambos ordenados |

Dois ponteiros não são uma solução única: copie a variante certa. Programas separados;
índices base 0. O(N) vale porque cada ponteiro avança no máximo N vezes.

<a id="par"></a>
## A) PAR COM SOMA ALVO

**Use:** encontrar dois elementos cuja soma seja alvo.

**Precisa:** vetor crescente; soma de qualquer par cabe em long long. Negativos são permitidos.

**Ideia:** soma pequena → left++; soma grande → right--; igual → achou.

Entrada: N, alvo, N valores ordenados. Saída: dois índices distintos, ou -1.

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

**Custo:** O(N), O(1) extra; vetor O(N). Sort prévio: O(N log N).

**Cuidado:** left < right impede repetir o mesmo índice. Acha um par, não conta todos. Para índices originais, ordene (valor,id).

<details>
<summary>Entender melhor: exemplo</summary>

`1 3 5 8`, alvo 9 → índices `0 3`.
A ordem prova o descarte: se a soma é pequena, diminuir o maior não ajudaria.

</details>

<a id="janela"></a>
## B) MAIOR JANELA COM SOMA LIMITADA

**Use:** maior trecho consecutivo com soma <= S.

**Precisa:** valores não negativos, S >= 0 e soma total cabe em long long.

**Ideia:** some o que entra; enquanto inválida, retire pela esquerda; registre tamanho.

Entrada: N, S, N valores. Saída: maior tamanho; 0 se nenhum elemento couber.

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

**Custo:** O(N), mesmo com while; O(1) extra, vetor O(N).

**Cuidado:** não ordene e não use com negativos. Janela fixa aceita negativos; esta variável por soma não.

<details>
<summary>Entender melhor: exemplo</summary>

`2 1 3 1 1`, S=5 → tamanho `3` ([3,1,1]).

Contraexemplo com negativos: [5,-4], S=1. Descartar 5 antes de ver -4 perde o trecho inteiro válido.
Para minimizar tamanho com soma >= S (positivos), registre a resposta enquanto suficiente, antes de contrair.
[Janela fixa/frequências](../algorithms/prefix-and-window.md#sliding-window).

</details>

<a id="diferenca"></a>
## C) TWO DIFFERENCE — DIFERENÇA ALVO

**Use:** par com diferença absoluta D.

**Precisa:** vetor crescente, D >= 0; toda diferença calculada cabe em long long. Negativos são permitidos.

**Ideia:** diferença pequena → r++; grande → l++; l==r → avance r antes de comparar.

Entrada: N, D, N valores ordenados. Saída: l r distintos, ou -1.

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

**Custo:** O(N), O(1) extra; vetor O(N). Sort prévio: O(N log N).

**Cuidado:** D=0 precisa de dois valores iguais em posições distintas. Não resolve diferença orientada pela ordem original.

<details>
<summary>Entender melhor: exemplo</summary>

`1 2 4 8`, D=3 → índices `0 2`.
Aqui os dois ponteiros vão para a direita, diferente do par por soma.

</details>

<a id="merge"></a>
## D) MERGE — DOIS ARRAYS ORDENADOS

**Use:** juntar duas sequências em ordem.

**Precisa:** ambas crescentes.

**Ideia:** copie o menor atual; avance seu índice; ao acabar uma, copie a sobra.

Entrada: N M, N valores de a, M de b. Saída: todos os valores em ordem.

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

**Custo:** O(N+M); resultado O(N+M), ponteiros O(1).

**Cuidado:** mantém duplicatas. Não é união de conjuntos nem janela.

<details>
<summary>Entender melhor: exemplo</summary>

`a=[1,4,4]`, `b=[2,4]` → `1 2 4 4 4`.

</details>

<a id="nao-confundir"></a>
## VARIANTES / NÃO CONFUNDIR

**Par:** dois elementos quaisquer, pode ordenar preservando ids.
**Janela:** um trecho consecutivo original, não pode ordenar.

**Janela fixa:** entra um/sai um, tamanho K; [código](../algorithms/sliding-window-fixed.cpp).
**Binary search:** descarta metade do espaço, não avança um índice por vez.

Não basta ter dois índices: é preciso provar que o movimento não perde respostas.
