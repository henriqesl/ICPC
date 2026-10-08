# BINARY SEARCH NA RESPOSTA

Binary Search na resposta não procura necessariamente algo dentro de um vetor.
Ela procura dentro de um intervalo de possíveis respostas.

[Índice](README.md) · [FIRST TRUE](#first-true) · [LAST TRUE](#last-true) ·
[verify](#verify) · [Limites](#limites) · [Armadilhas](#armadilhas)

## NECESSIDADE / RECONHECIMENTO

Quero otimizar um valor e consigo testar se um candidato é **viável**.
O teste precisa ser monotônico: ao aumentar mid, muda de false para true
ou de true para false no máximo uma vez. Não precisa ordenar o vetor de entrada;
quem precisa dessa propriedade é o **intervalo de respostas**.

## IDEIA — ANTES DE CODAR

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
## A) FIRST TRUE — MENOR VALOR SUFICIENTE

```text
mid aumentando → F F F F T T T T
                         ^
                      primeiro true
```

Gatilhos: menor tempo necessário, menor capacidade suficiente, menor limite máximo,
**minimizar o máximo** — desde que aumentar mid preserve a viabilidade.

| verify(mid) | O que concluo | Movimento |
|---|---|---|
| true | mid funciona: salvo e tento MENOR | ans = mid; r = mid - 1 |
| false | mid é insuficiente: preciso aumentar | l = mid + 1 |

### TEMPLATE C++ — capacidade de grupos consecutivos

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
## B) LAST TRUE — MAIOR VALOR AINDA POSSÍVEL

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

### TEMPLATE C++ — tamanho inteiro de pedaços

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
## COMO PENSAR NO verify(mid)

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

## COMPLEXIDADE

Com R candidatos, há O(log(R+1)) testes, usualmente escrito **O(log R)**.
Se verify = O(N), o total é **O(N log R)**, não apenas O(log R).
Os dois exemplos usam O(1) de memória extra no teste/busca e O(N) para os dados.
Se verify custar O(N log N), o total vira O(N log N · log R).

<a id="limites"></a>
## LIMITES DA BUSCA — COMO ESCOLHER l E r?

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
## ARMADILHAS — CONFIRA ANTES DE SUBMETER

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
