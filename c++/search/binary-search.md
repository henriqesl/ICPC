# BUSCAS — escolha e copie um template

[Índice](README.md) · [Linear](#linear) · [Tradicional](#tradicional) · [Bounds](#bounds) · [FIRST TRUE](#first-true) · [LAST TRUE](#last-true) · [verify](#verify) · [Limites](#limites) · [Armadilhas](#armadilhas)

## RECONHEÇA EM UMA FRASE

| Pedido | Template | Condição |
|---|---|---|
| X está nos dados, sem ordem útil? | [Linear](#linear) | qualquer ordem |
| X está nos dados ordenados? | [Tradicional](#tradicional) | crescente |
| Primeiro >= / primeiro > / quantos iguais? | [Bounds](#bounds) | crescente |
| Menor X viável? | [FIRST TRUE](#first-true) | FFFTTT: maiores continuam viáveis |
| Maior X viável? | [LAST TRUE](#last-true) | TTTFFF: menores continuam viáveis |

Programas independentes: copie um por vez. Índices base 0; -1 = ausência nos exemplos.

<a id="linear"></a>
## 1. BUSCA LINEAR

**Use:** achar a primeira ocorrência de X.

**Precisa:** nenhuma ordenação.

**Ideia:** percorra; encontrou, salve e pare.

Entrada: N, alvo, N valores. Saída: primeiro índice ou -1.

<!-- search-example: linear -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;

    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    int answer = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] == target) {
            answer = i; // primeira ocorrência
            break;
        }
    }

    cout << answer << '\n';
}
```

**Custo:** O(N) por busca; O(1) extra, além do vetor O(N).

**Cuidado:** não leia v[-1]. Muitas buscas custam O(QN); considere ordenar uma vez + bounds ou guardar presença em set/hash.

<details>
<summary>Entender melhor: exemplo</summary>

Entrada: `5 7` e valores `4 7 1 7 9` → índice `1`.
Para contar todas as ocorrências, não pare no primeiro acerto.

</details>

<a id="tradicional"></a>
## 2. BINARY SEARCH TRADICIONAL

**Use:** achar uma ocorrência exata de X.

**Precisa:** vetor já ordenado crescente.

**Ideia:** compare o meio; alvo menor → esquerda; maior → direita.

Entrada: N, alvo, N valores ordenados. Saída: um índice ou -1.

<!-- search-example: binary -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;

    vector<long long> v(n);
    for (long long &x : v) cin >> x;

    int left = 0;
    int right = n - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (v[mid] == target) {
            answer = mid;
            break;
        } else if (v[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << '\n';
}
```

**Custo:** O(log N) na busca; O(1) extra, vetor O(N). Sort prévio soma O(N log N).

**Cuidado:** com repetidos, não garante a primeira ocorrência. Ordenar muda índices: preserve (valor,id) se precisar da posição original.

<details>
<summary>Entender melhor: limites e exemplo</summary>

`left/right` são inclusivos; `left <= right` testa o último candidato.
`left + (right-left)/2` evita somar dois índices grandes.
Entrada: `6 5` e valores `1 2 2 2 5 8` → índice `4`.

Busca tradicional pergunta “X está aqui?”. Na resposta pergunta “X é viável?”.
O arquivo [algorithms/binary-search.cpp](../algorithms/binary-search.cpp) procura primeiro >=, não igualdade.

</details>

<a id="bounds"></a>
## 3. STL — binary_search / lower_bound / upper_bound

**Use:** presença, vizinhos ou quantidade em vetor **ordenado crescente**.

| Preciso | Chamada / resultado |
|---|---|
| X existe? | `binary_search(begin,end,x)` → bool |
| <a id="lower-bound"></a>Primeiro >= X | `lower_bound(begin,end,x)` → iterador |
| <a id="upper-bound"></a>Primeiro > X | `upper_bound(begin,end,x)` → iterador |
| <a id="contar"></a>Quantos X? | `upper - lower` no vector |
| Quantos <= X? | `upper - begin` no vector |
| Quantos em [L,R], L <= R? | `upper_bound(R) - lower_bound(L)` no vector |

**Leia:** `*it` = valor; `it - v.begin()` = índice. Para igualdade: `it != end && *it == x`.

<!-- search-example: bounds -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> v = {1, 2, 2, 2, 5, 8};
    long long x = 2;

    bool exists = binary_search(v.begin(), v.end(), x);
    auto lower = lower_bound(v.begin(), v.end(), x);
    auto upper = upper_bound(v.begin(), v.end(), x);

    cout << exists << '\n';                 // 1 (true)
    cout << lower - v.begin() << '\n';      // 1
    cout << upper - v.begin() << '\n';      // 4
    cout << upper - lower << '\n';          // 3 ocorrências

    if (lower != v.end()) cout << *lower << '\n'; // 2
    if (upper != v.end()) cout << *upper << '\n'; // 5

    bool exact = lower != v.end() && *lower == x;
    cout << exact << '\n';                  // 1 (true)
}
```

**Custo:** O(log N) por chamada; O(1) extra. Sort inicial, se necessário: O(N log N).

**Cuidado:** `end()` não é elemento. Em set/multiset/map use `s.lower_bound(x)` e `s.upper_bound(x)` em O(log N); não subtraia seus iteradores.

<details>
<summary>Entender melhor: posições, ausência e repetidos</summary>

```text
índice: 0  1  2  3  4  5     6 = end()
vetor: [1, 2, 2, 2, 5, 8]
X=2 → lower=1, upper=4; quantidade=3
X=3 → lower=4, upper=4; quantidade=0
X=9 → lower=6, upper=6; nenhum valor para ler
```

Última ocorrência de X: se lower != upper, índice `(upper - begin) - 1`.
Em set/map, `distance` percorre elementos e pode custar O(N); a função genérica
`lower_bound(s.begin(),s.end(),x)` também pode avançar O(N) vezes.
Comparador diferente exige ordenação e busca compatíveis.

</details>

<a id="resposta"></a>
## 4. BINARY SEARCH NA RESPOSTA

Você não precisa ter um vetor de respostas. `mid` é um **valor candidato**;
`verify(mid)` responde **se dá para cumprir o pedido com esse valor**.
Antes de copiar, prove a direção da viabilidade e escolha [l,r] que contenha a resposta.

| Ao aumentar mid... | Quero | Se verify(mid) é true | Se false |
|---|---|---|---|
| F F F T T T | primeiro true / menor viável | salvar; `r = mid - 1` | `l = mid + 1` |
| T T T F F F | último true / maior viável | salvar; `l = mid + 1` | `r = mid - 1` |

Os programas usam inteiros, intervalo inclusivo, candidatos não negativos e r <= LLONG_MAX-1. Não misture com templates [l,r).

<a id="first-true"></a>
## A) FIRST TRUE — MENOR VALOR SUFICIENTE

**Use:** minimizar X quando aumentar X mantém a viabilidade (FFFTTT).

**Precisa:** um verify correto e monotônico; aqui N >= 1, K >= 1, valores não negativos e soma <= LLONG_MAX-1.

**Ideia:** funcionou → salve e tente MENOR.

Exemplo completo: dividir valores consecutivos em **no máximo K grupos**, minimizando a maior soma.
`mid` = capacidade; verify = cabe tudo em até K grupos?
Entrada: N K e N valores. Saída: menor capacidade.

<!-- search-example: first-true -->
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> values;
ll k;

bool verify(ll mid) {
    ll groups = 1;
    ll current = 0;

    for (ll x : values) {
        if (x > mid) return false; // nem um grupo sozinho comporta x

        if (current > mid - x) { // current + x > mid, sem overflow
            if (groups == k) return false;
            groups++;
            current = x;
        } else {
            current += x;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n >> k;
    values.resize(n);

    ll l = 0;
    ll r = 0;
    for (ll &x : values) {
        cin >> x;
        l = max(l, x);
        r += x;
    }
    ll ans = -1;

    // Queremos o PRIMEIRO true: F F F T T T.
    while (l <= r) {
        ll mid = l + (r - l) / 2;

        if (verify(mid)) {
            ans = mid;
            r = mid - 1; // funciona: tenta menor
        } else {
            l = mid + 1; // insuficiente: precisa de mais capacidade
        }
    }

    cout << ans << '\n';
}
```

**Custo:** O(N log R), R = quantidade de capacidades candidatas; vetor O(N), teste O(1) extra.

**Cuidado:** o verify guloso abaixo exige não negativos. Um item maior que mid não cabe nem sozinho.

<details>
<summary>Entender melhor: grupos e exemplo</summary>

Valores `2 3 5`, K=2 → capacidade mínima `5`: grupos [2,3] e [5].

O teste enche o grupo até o próximo item não caber. Com não negativos, fechar mais cedo não permite usar menos grupos.
Os limites são maior item e soma total.
“No máximo K” só pode virar “exatamente K” aqui se K <= N, grupos não vazios e nenhuma outra restrição impedir subdivisões.

</details>

<a id="last-true"></a>
## B) LAST TRUE — MAIOR VALOR AINDA POSSÍVEL

**Use:** maximizar X quando diminuir X mantém a viabilidade (TTTFFF).

**Precisa:** um verify correto e monotônico; aqui N >= 1, K >= 1 e comprimentos não negativos <= LLONG_MAX-1.

**Ideia:** funcionou → salve e tente MAIOR.

Exemplo completo: cortar pelo menos K pedaços de tamanho inteiro positivo, permitindo sobras.
`mid` = tamanho; verify = saem pelo menos K pedaços?
Entrada: N K e N comprimentos. Saída: maior tamanho ou -1.

<!-- search-example: last-true -->
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> lengths;
ll k;

bool verify(ll mid) {
    ll pieces = 0;
    for (ll x : lengths) {
        ll made = x / mid;
        if (made >= k - pieces) return true; // atingiu K, sem estourar a soma
        pieces += made;
    }
    return false;
}

int main() {
    int n;
    cin >> n >> k;
    lengths.resize(n);

    ll l = 1; // tamanho zero causaria divisão por zero
    ll r = 0;
    for (ll &x : lengths) {
        cin >> x;
        r = max(r, x);
    }
    ll ans = -1;

    // Queremos o ÚLTIMO true: T T T F F F.
    while (l <= r) {
        ll mid = l + (r - l) / 2;

        if (verify(mid)) {
            ans = mid;
            l = mid + 1; // funciona: tenta maior
        } else {
            r = mid - 1; // exigiu demais: tenta menor
        }
    }

    cout << ans << '\n';
}
```

**Custo:** O(N log R), R = quantidade de tamanhos candidatos; vetor O(N), teste O(1) extra.

**Cuidado:** l começa em 1 para não dividir por zero. Não é permitido juntar sobras de comprimentos diferentes.

<details>
<summary>Entender melhor: exemplo</summary>

Comprimentos `5 8`, K=3 → tamanho `4`: `5/4 + 8/4 = 1+2` pedaços.
A divisão é piso: uma sobra menor que mid não forma outro pedaço.

</details>

<a id="verify"></a>
## COMO PENSAR NO verify(mid)

| mid é... | Pergunta de viabilidade | Direção a provar |
|---|---|---|
| Tempo | Produzo pelo menos X nesse tempo? | mais tempo facilita → first |
| Capacidade | Cabe tudo respeitando esse limite? | mais capacidade facilita → first |
| Distância mínima | Posiciono K itens com essa separação? | maior distância dificulta → last |
| Tamanho do pedaço | Produzo pelo menos K pedaços? | maior tamanho dificulta → last |

São pistas, não provas. `verify` muda conforme a questão; o movimento da busca não.
Se verify custa T, o total é **O(T log R)**. Prepare dados fixos uma vez, fora do teste.

<a id="limites"></a>
## COMO ESCOLHER L E R

| Exemplo | l | r |
|---|---|---|
| Grupos consecutivos não negativos | maior item | soma total |
| Tamanho positivo de pedaço | 1 | maior comprimento |
| Distância entre K posições, 2 <= K <= N | 0 | maior posição − menor posição |
| Tempo, quando mais tempo não atrapalha | 0 | tempo comprovadamente suficiente |

Todos os limites e cálculos intermediários devem caber em long long. Ans=-1 indica ausência;
se -1 puder ser resposta, use outro marcador ou bool found.

<a id="armadilhas"></a>
## ARMADILHAS — CONFIRA ANTES DE SUBMETER

- Salvar ans antes de tentar melhorar; usar **mid ± 1** neste intervalo inclusivo.
- Não usar `l=mid` / `r=mid`: pode travar. First → tente menor; last → tente maior.
- Manter l/r não negativos e r <= LLONG_MAX-1 nestes templates; busca real/negativa exige adaptação.
- Monotonicidade e limites precisam de prova; “menor/maior” no texto não basta.
- Contar o custo de verify e evitar overflow em soma, produto e divisão.

Divisão teto para a >= 0, b > 0 (sem somar a+b):

<!-- search-example: ceiling -->
```cpp
long long a = 10, b = 3;
long long ceiling = a / b + (a % b != 0); // 4, sem somar a + b
```

<details>
<summary>Entender melhor: extremos e divisão</summary>

Se todos os candidatos funcionam, first devolve o l inicial e last devolve o r inicial.
Se nenhum funciona, ans permanece -1. Se l > r no início, não há candidatos.

`l + (r-l)/2` exige que r-l caiba no tipo; com candidatos não negativos isso vale nas hipóteses acima.
Pedaços usam piso (`x/mid`); viagens/caixas para atender uma demanda costumam usar teto.

</details>
