# BUSCAS — linear, binária, bounds e resposta

[Índice](README.md) · [Linear](#linear) · [Tradicional](#tradicional) · [Bounds](#bounds) ·
[FIRST TRUE](#first-true) · [LAST TRUE](#last-true) · [verify](#verify) · [Limites](#limites) · [Armadilhas](#armadilhas)

## RECONHEÇA EM UMA FRASE

| Preciso... | Vá direto |
|---|---|
| Procurar valor, sem ordem útil | [Linear](#linear) |
| Procurar valor em dados ordenados | [Tradicional](#tradicional) |
| Existe / primeiro >= / primeiro > / contar iguais | [STL e bounds](#bounds) |
| Menor candidato viável: FFFTTT | [FIRST TRUE](#first-true) |
| Maior candidato viável: TTTFFF | [LAST TRUE](#last-true) |

Os blocos com main são programas independentes: copie um por vez.
Índices começam em 0; -1 sinaliza ausência nos exemplos de busca.

<a id="linear"></a>
## 1. BUSCA LINEAR

### NECESSIDADE / RECONHECIMENTO

“Existe x?”, “qual a primeira posição com essa propriedade?”; os dados não têm uma
ordem útil, ou basta uma consulta. Não precisa ordenar.

### IDEIA

Visite um elemento por vez; pare no primeiro que satisfaz a condição.
Para contar ou listar todas as ocorrências, não pare no primeiro acerto.

### TEMPLATE C++

Entrada: N, alvo e N valores. Saída: primeiro índice (base 0), ou -1 se ausente.

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

### EXEMPLO

```text
Entrada: 5 7
         4 7 1 7 9
Saída:   1
```

### COMPLEXIDADE

Busca: O(N) no pior caso, O(1) de memória extra. O vetor de entrada ocupa O(N).
Q buscas independentes custam O(QN); se Q = N, vira **O(N²)**.

Muitas consultas no mesmo conjunto? Pense em ordenar uma vez + [busca binária](binary-search.md)
(O(N log N + Q log N)), ou em `set` / `unordered_set` para presença
(O(log N) / O(1) médio por consulta; hash pode chegar a O(N) no pior caso).
Se a posição original importa, preserve-a antes de ordenar.

### ARMADILHAS

- Não acesse `v[answer]` se answer = -1.
- Vetor vazio: o loop não executa; a resposta continua -1.
- Uma condição arbitrária serve para busca linear; para busca binária, precisa da propriedade adequada.


<a id="tradicional"></a>
## 2. BINARY SEARCH TRADICIONAL

### NECESSIDADE / RECONHECIMENTO

Coleção **ordenada crescente** e busca por um valor exato.

| Busca | Pergunta |
|---|---|
| Tradicional | **“X está aqui?”** — compara X com elementos do vetor. |
| Na resposta | **“Se a resposta fosse X, funcionaria?”** — testa viabilidade; pode nem existir vetor de respostas. |

### IDEIA

`left` e `right` delimitam o trecho ainda possível, **ambos inclusivos**.
`mid` é o índice do meio. Cada comparação descarta metade desse trecho.

| Comparação | Ação |
|---|---|
| v[mid] < target | `left = mid + 1`: alvo só pode estar à direita. |
| v[mid] > target | `right = mid - 1`: alvo só pode estar à esquerda. |
| v[mid] == target | Achou; salve mid e pare. |

### TEMPLATE C++

Entrada: N, alvo e N valores **já ordenados**. Saída: um índice com esse valor, ou -1.

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

### EXEMPLO

```text
Entrada: 6 5
         1 2 2 2 5 8
Saída:   4
```

`left + (right - left) / 2` evita somar dois índices grandes, como em `(left + right) / 2`.
`while (left <= right)` ainda testa o último candidato; terminou quando left > right.
Use índices com sinal: para N = 0, right = -1 e o loop não executa.

### COMPLEXIDADE

Busca: O(log N), O(1) de memória extra; armazenamento do vetor: O(N).
Se precisar de `sort(v.begin(), v.end())`, some O(N log N) de preparação.

### ARMADILHAS

- Não use em vetor desordenado. Ordenar muda os índices e pode destruir a ordem exigida pelo problema.
- Com repetidos, esse template acha **uma** ocorrência, não necessariamente a primeira.
  Para primeira ocorrência, use [lower_bound + teste de igualdade](binary-search.md#lower-bound).
- `<` e `>` indicam o lado; igualdade resolve a busca tradicional, mas **não** resolve busca na resposta.
- Só precisa saber se existe? `std::binary_search` já devolve bool; não é índice.
- O arquivo antigo `c++/algorithms/binary-search.cpp` procura primeiro >= alvo;
  não é este template de igualdade.


<a id="bounds"></a>
## 3. STL — binary_search / lower_bound / upper_bound

### NECESSIDADE / RECONHECIMENTO

Vetor **ordenado crescente**; quero presença, primeiro >=, primeiro > ou número de repetições.
Os limites descrevem posições de inserção: **não garantem igualdade com o alvo**.

### IDEIA / EXEMPLO

```text
índice: 0  1  2  3  4  5     6 = end()
vetor: [1, 2, 2, 2, 5, 8]

alvo 2: lower → índice 1; upper → índice 4; quantidade → 4 - 1 = 3
alvo 3: lower → índice 4; upper → índice 4; quantidade → 0
alvo 9: lower → índice 6; upper → índice 6; nenhum elemento válido
```

#### binary_search — existe x?

Retorna **bool**, não iterador nem índice.

<a id="lower-bound"></a>
#### lower_bound — primeiro elemento >= x

Retorna um **iterador**, uma posição na coleção. `*it` lê o valor;
em vector, `it - v.begin()` converte para índice. Para igualdade: confira
`it != v.end() && *it == x`. Se não houver >= x, retorna `v.end()`.

<a id="upper-bound"></a>
#### upper_bound — primeiro elemento > x

Também retorna iterador; passa por todas as ocorrências iguais a x.
Se não houver > x, retorna `v.end()`.

<a id="contar"></a>
#### Contar ocorrências

O intervalo dos iguais é **[lower_bound(x), upper_bound(x))**:
inclui o início e exclui o fim. Em vector, quantidade = upper − lower.

### TEMPLATE C++

Exemplo completo; troque v e x pelos seus dados. A saída confirma as posições acima.

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

### COMPLEXIDADE

Em vector ordenado: O(log N) por chamada, O(1) de memória extra.
Contar com duas chamadas continua O(log N). Ordenar, se necessário: O(N log N) uma vez.

### ARMADILHAS

- **Nunca leia `*v.end()`**. Índice N significa ausência de limite válido, não elemento N.
- Não confunda iterador com valor: `lower` é posição; `*lower` é o valor (se válido).
- Em `set`, `multiset` e `map`, use `s.lower_bound(x)` / `s.upper_bound(x)`:
  são O(log N). As versões genéricas podem percorrer O(N) iteradores nesses containers.
- Não subtraia iteradores de set/map. `distance(s.begin(), it)` é O(N);
  `distance(lower, upper)` custa O(quantidade de elementos percorridos).
- A regra desta página assume ordem crescente padrão. Comparador diferente exige ordenação e busca coerentes.
- Só precisa da última ocorrência? Se lower != upper, o índice é `(upper - v.begin()) - 1`.


<a id="resposta"></a>
## 4. BINARY SEARCH NA RESPOSTA

Binary Search na resposta **NÃO procura necessariamente algo dentro de um vetor**.
Ela pergunta: **SE A RESPOSTA FOSSE mid, ISSO FUNCIONARIA?**
O intervalo contém candidatos, não necessariamente elementos existentes.

### NECESSIDADE / RECONHECIMENTO

Quero otimizar um valor e consigo testar se um candidato é **viável**.
O teste precisa ser monotônico: ao aumentar mid, muda de false para true
ou de true para false no máximo uma vez. Não precisa ordenar o vetor de entrada;
quem precisa dessa propriedade é o **intervalo de respostas**.

### IDEIA — ANTES DE CODAR

1. Defina o que mid representa: tempo, capacidade, tamanho, distância…
2. Escreva a pergunta `verify(mid)` com resposta true/false.
3. Se mid funciona, o que acontece com mid + 1 e mid - 1? Justifique.
4. Escolha FIRST TRUE (menor viável) ou LAST TRUE (maior viável).
5. Defina l/r que contêm a resposta, e uma saída para “não existe”.
6. Execute a busca, descartando mid com `+1` ou `-1` após testá-lo.

Os dois templates abaixo são **programas independentes**, não devem ser colados juntos.
Usam intervalo inteiro inclusivo [l, r], `ll = long long` e ans = -1 para ausência.
Para copiar só a busca, adapte l/r e troque verify: o movimento dos limites fica igual.
Assumimos candidatos não negativos e r <= LLONG_MAX - 1, para que mid ± 1 caiba em ll.

<a id="first-true"></a>
### A) FIRST TRUE — MENOR VALOR SUFICIENTE

```text
mid aumentando → F F F F T T T T
                         ^
                      primeiro true
```

Gatilhos: menor tempo necessário, menor capacidade suficiente, menor velocidade necessária, menor limite máximo,
**minimizar o máximo** — desde que aumentar mid preserve a viabilidade.

| verify(mid) | O que concluo | Movimento |
|---|---|---|
| true | mid funciona: salvo e tento MENOR | ans = mid; r = mid - 1 |
| false | mid é insuficiente: preciso aumentar | l = mid + 1 |

#### TEMPLATE C++ — capacidade de grupos consecutivos

Exemplo genérico: dividir N valores **não negativos**, sem mudar a ordem, em **no máximo K**
grupos não vazios, minimizando a maior soma de um grupo.
mid = capacidade; verify = “consigo acomodar tudo em até K grupos?”.
Se cabe em capacidade x, cabe em qualquer capacidade maior: **FFF → TTT**.

Entrada: N K e N valores; N >= 1, K >= 1 e soma <= LLONG_MAX - 1.

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

```text
Entrada: 3 2
         2 3 5
Saída:   5  (grupos [2,3] e [5])
```

O verify preenche cada grupo até o próximo elemento não caber. Com valores não negativos,
terminar o grupo mais cedo não permite usar menos grupos: essa escolha gulosa produz
a menor quantidade de grupos para a capacidade testada. Não serve com negativos sem nova justificativa.

<a id="last-true"></a>
### B) LAST TRUE — MAIOR VALOR AINDA POSSÍVEL

```text
mid aumentando → T T T T F F F F
                       ^
                     último true
```

Gatilhos: maior distância mínima, maior tamanho possível, **maximizar o mínimo** —
desde que diminuir mid preserve a viabilidade.

| verify(mid) | O que concluo | Movimento |
|---|---|---|
| true | mid funciona: salvo e tento MAIOR | ans = mid; l = mid + 1 |
| false | exigi demais: preciso diminuir | r = mid - 1 |

#### TEMPLATE C++ — tamanho inteiro de pedaços

Exemplo genérico: cortar comprimentos não negativos em pelo menos K pedaços do mesmo
tamanho inteiro positivo; sobras são permitidas, mas não se juntam comprimentos distintos.
mid = tamanho; verify = “consigo produzir pelo menos K pedaços desse tamanho?”.
Se consigo tamanho x, consigo qualquer tamanho positivo menor: **TTT → FFF**.

Entrada: N K e N comprimentos; N >= 1, K >= 1 e cada comprimento <= LLONG_MAX - 1.
Saída: maior tamanho, ou -1 se nenhum tamanho positivo funcionar.

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

```text
Entrada: 2 3
         5 8
Saída:   4  (5/4 + 8/4 = 1 + 2 pedaços)
```

<a id="verify"></a>
### COMO PENSAR NO verify(mid)

Ele **não** pergunta “mid é a resposta?”. Pergunta **“mid é viável?”**.
Mais de um candidato pode funcionar; a busca encontra o extremo desejado.

| mid representa | Pergunta de verify | Se mid aumenta… |
|---|---|---|
| Tempo | Consigo produzir pelo menos X nesse tempo? | tende a facilitar → first true |
| Capacidade | Consigo dividir tudo respeitando esse limite? | tende a facilitar → first true |
| Distância mínima | Consigo posicionar K elementos com essa separação? | tende a dificultar → last true |
| Velocidade | Termino dentro do prazo com essa velocidade? | tende a facilitar → first true |
| Tamanho | Consigo produzir pelo menos K pedaços desse tamanho? | tende a dificultar → last true |

“Tende” é pista, não prova: confira as regras do seu enunciado.
O formato é `bool verify(ll mid)`: calcule a viabilidade e devolva true/false;
os dois programas acima mostram implementações completas, sem `...` para preencher.
Dados fixos não precisam ser copiados ou reordenados a cada teste.

### COMPLEXIDADE

Com R candidatos, há O(log(R+1)) testes, usualmente escrito **O(log R)**.
Se verify = O(N), o total é **O(N log R)**, não apenas O(log R).
Os dois exemplos usam O(1) de memória extra no teste/busca e O(N) para os dados.
Se verify custar O(N log N), o total vira O(N log N · log R).

<a id="limites"></a>
### COMO ESCOLHER L E R

| Cenário (com hipóteses do enunciado) | l | r | Justificativa |
|---|---|---|---|
| Grupos consecutivos de não negativos, K >= 1 | maior elemento | soma | não pode dividir um elemento; tudo cabe em um grupo |
| Distância mínima entre posições, 2 <= K <= N | 0 | max_position − min_position | separação não ultrapassa a extensão disponível |
| Tempo, quando mais tempo não atrapalha | 0 | algum tempo comprovadamente suficiente | construir uma solução lenta fornece um teto |
| Tamanho positivo de pedaços | 1 | maior comprimento | evita zero; não se juntam comprimentos |

O limite superior **não precisa ser a resposta**; o intervalo precisa conter a resposta.
Para first true com resposta garantida, costuma ser fácil escolher um r que já funciona.
Para last true, r pode não funcionar: basta não excluir a resposta real.
Não é necessário criar um vetor de todos os valores possíveis: l/r já representam o intervalo.
Produtos, somas e diferenças usados nos limites também precisam caber em long long.

ans = -1 significa “não achei candidato viável”. Se todos funcionam, first true devolve
o l inicial e last true devolve o r inicial. Se l > r desde o início, não há candidatos.
Se respostas negativas forem permitidas, use outro marcador ou um bool `found`.
Estes templates são para **inteiros**; busca real usa tolerância/iterações e outros movimentos.

<a id="armadilhas"></a>
### ARMADILHAS — CONFIRA ANTES DE SUBMETER

- Inverter first/last ou mandar true para o lado errado: primeiro → menor; último → maior.
- Usar `l = mid` / `r = mid` nestes templates inclusivos: pode não avançar e dar loop infinito.
  Não misture com templates de intervalo semiaberto que têm outras regras.
- Esquecer `mid + 1` / `mid - 1`, ou não salvar ans antes de tentar melhorar.
- Usar int para tempo/capacidade/soma grandes; `(l + r) / 2` pode estourar.
  `l + (r - l) / 2` evita essa soma, mas exige que r - l caiba no tipo;
  aqui l/r são não negativos. Com extremos negativos/positivos, adapte o cálculo.
- Permitir r = LLONG_MAX sem proteger `mid + 1`; este material limita r a LLONG_MAX - 1.
- verify lento demais, com cópias ou preparação repetida; conte o custo multiplicado por log R.
- Um limite que exclui a resposta torna a busca incorreta, mesmo se o loop estiver perfeito.
- Confundir “exatamente K” com “no máximo K”: o primeiro exemplo pode ser subdividido
  até exatamente K **se K <= N**, os grupos forem não vazios e os valores não negativos.
  Outras restrições podem impedir essa equivalência.
- Esquecer elemento individual maior que a capacidade: rejeite no verify, antes de somar.
- Usar piso quando precisa de teto: para a >= 0 e b > 0, `(a + b - 1) / b` arredonda para cima,
  mas só se a + b - 1 couber no tipo. Alternativa segura:

<!-- search-example: ceiling -->
```cpp
long long a = 10, b = 3;
long long ceiling = a / b + (a % b != 0); // 4, sem somar a + b
```

Na produção de pedaços usamos **piso** (`x / mid`): sobras não formam outro pedaço.
Para calcular quantas viagens/caixas atendem uma demanda, geralmente precisamos de **teto**.
