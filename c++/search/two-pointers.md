# TWO POINTERS — pontas opostas OU janela

[Índice](README.md) · [Par](#par) · [Janela](#janela)

## NECESSIDADE / RECONHECIMENTO

| Pedido | Variante | Hipótese |
|---|---|---|
| Dois elementos somam um alvo | Pontas opostas | vetor ordenado crescente |
| Maior trecho consecutivo com soma <= S | Sliding window | valores não negativos, S >= 0 |

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
