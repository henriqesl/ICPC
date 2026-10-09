# SWEEP LINE — receita, eventos e estado ativo

[Índice](README.md) · [Receita/base](#receita) · [Prefix sum](#prefix-events) ·
[START/END/QUERY](#query-events) · [Empates](#empates) · [Estado ativo](#estado) ·
[Compressão](#compression) · [Armadilhas](#sweep-armadilhas)

## RECONHECIMENTO

Muitos intervalos no tempo/posição, algo começa/termina ou consultas sobre o estado atual.
Descubra **onde muda**, não visite cada coordenada. O exemplo é 1D;
sweep line em geometria pode exigir outras estruturas.

<a id="receita"></a>
## RECEITA UNIVERSAL — ANTES DE ESCOLHER A ESTRUTURA

1. Descubra o eixo: tempo, posição ou coordenada.
2. Descubra onde alguma coisa muda.
3. Transforme cada mudança em evento.
4. Coloque os eventos em um vetor.
5. Ordene por posição **e pela prioridade dos empates**.
6. Defina o estado atual: quantidade? soma? conjunto? frequências?
7. Percorra: atualize o estado, consulte e atualize a resposta.

### TEMPLATE BASE — SOMENTE O ESTADO CORRENTE

`pair.first` = **ONDE**; `pair.second` = **O QUE muda**.
Para intervalos [L,R), +1 em L e -1 em R. Este exemplo usa pares ordenados
por posição e delta: -1 antes de +1 nos empates, com intervalos vazios ignorados.

<!-- search-example: sweep-base -->
```cpp
using ll = long long;
vector<pair<ll, int>> events = {{1, +1}, {4, -1}, {3, +1}, {6, -1}};
sort(events.begin(), events.end());

ll active = 0;
for (auto event : events) {
    active += event.second;
    cout << active << '\n'; // 1, 2, 1, 0: prefix sum das mudanças
}
```

Para registrar o estado **exato na coordenada**, não consulte entre eventos empatados:
agrupe os deltas antes de consultar (programa abaixo), ou ordene mudanças e QUERY por tipo.

## INTERVALOS — MÁXIMO E CONSULTAS POR POSIÇÃO

### IDEIA

Para intervalos **[l, r)**: +1 em l, -1 em r. Ordene os eventos por coordenada
e acumule os deltas (prefix sum). Após processar todos os eventos em x,
active é a quantidade válida em x e até antes da próxima coordenada.

```text
[1,4) e [3,6)
posição:  1   3   4   6
delta:   +1  +1  -1  -1
ativos:   1   2   1   0
máximo: 2; no ponto 4, apenas o segundo intervalo está ativo.
```

### TEMPLATE C++

Entrada: N intervalos l r (l <= r), depois Q e Q pontos de consulta.
Saída: máximo simultâneo, depois a quantidade ativa em cada ponto.
Coordenadas negativas/grandes funcionam: não existe um vetor até MAX_COORD.

<!-- search-example: sweep-line -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<long long, int>> events;
    for (int i = 0; i < n; i++) {
        long long l, r;
        cin >> l >> r;
        if (l == r) continue; // [l,l) é vazio
        events.push_back({l, +1});
        events.push_back({r, -1});
    }
    sort(events.begin(), events.end());

    vector<long long> positions, counts;
    long long active = 0, maximum = 0;
    size_t i = 0;
    while (i < events.size()) {
        long long x = events[i].first;
        // Agrupa empates: não registra estados intermediários em x.
        while (i < events.size() && events[i].first == x) {
            active += events[i].second;
            i++;
        }
        positions.push_back(x);
        counts.push_back(active);
        maximum = max(maximum, active);
    }
    cout << maximum << '\n';

    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;
        auto it = upper_bound(positions.begin(), positions.end(), x);
        if (it == positions.begin()) cout << 0 << '\n';
        else {
            auto index = (it - positions.begin()) - 1; // último evento <= x
            cout << counts[index] << '\n';
        }
    }
}
```

```text
Entrada: 2
         1 4
         3 6
         3
         0 3 4
Saída:   2
         0
         2
         1
```

### COMPLEXIDADE

O(N log N) para ordenar + O(N) para acumular; O(log N) por consulta,
total O(N log N + Q log N). Memória O(N). Para zero/um elemento, leia log como log(N+1).
Só precisa do máximo? Remova consultas e os vetores positions/counts.
Coordenadas inteiras pequenas em [0,U]? Um vetor de diferenças permite O(U+N+Q),
como na referência de study/, mas usa O(U) de memória.

### ARMADILHAS

- **[l,r) não inclui r.** [1,3) e [3,5) não se sobrepõem; empates precisam dessa convenção.
- Para intervalos fechados [l,r], l = r não é vazio: não copie este código sem adaptar.
  Em pontos inteiros, evento -1 em r+1 é uma opção **somente se r+1 couber no tipo**.
- Ordenar coordenadas não basta: mantenha o delta associado ao evento.
- Para comprimento da união, use distâncias **originais** entre eventos quando active > 0;
  a quantidade de índices comprimidos não mede comprimento.
- Eventos são a ideia; prefix sum é a acumulação. Não confunda com testar todo par O(N²).

<a id="prefix-events"></a>
## PREFIX SUM DE EVENTOS — VETOR OU ESCALAR?

`active += event.second` é a soma acumulada das mudanças, não uma soma dos intervalos.
O template base guarda só o corrente. Para manter o histórico por evento, após ordenar events:

<!-- search-example: prefix-events -->
```cpp
vector<long long> accumulated(events.size());
for (size_t i = 0; i < events.size(); i++) {
    accumulated[i] = (i == 0 ? 0 : accumulated[i - 1]) + events[i].second;
}
```

O vetor é desnecessário se cada resposta puder ser obtida durante a varredura (máximo,
soma corrente ou QUERY intercalada). Para consultas posteriores, o programa anterior
guarda posições e contagens **por coordenada**, agrupando empates: não confunda com o estado
intermediário por evento. Ordenação O(N log N); acumulação O(N); histórico usa O(N).

<a id="query-events"></a>
## START / END / QUERY — TUDO NO MESMO VETOR

Não precisa de um vetor por tipo. Um evento pode ser uma mudança ou uma consulta.
Para preservar a ordem de saída das consultas, acrescente seu id ao evento.
O pair aninhado abaixo tem **posição, tipo, id**; não precisa de uma classe.

### TEMPLATE C++ — CONSULTAS OFFLINE EM [L,R)

Entrada: N intervalos L R (L <= R), depois Q e Q posições.
Saída: quantos intervalos contêm cada posição, na **ordem original das consultas**.
END acontece antes de START e ambos antes de QUERY, incluindo L e excluindo R.

<!-- search-example: sweep-query -->
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    enum { END = 0, START = 1, QUERY = 2 };
    // first = posição; second.first = tipo; second.second = id
    vector<pair<ll, pair<int, int>>> events;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        if (l == r) continue; // [l,l) é vazio
        events.push_back({l, {START, i}});
        events.push_back({r, {END, i}});
    }

    int q;
    cin >> q;
    vector<ll> answer(q);
    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        events.push_back({x, {QUERY, i}});
    }
    sort(events.begin(), events.end());

    ll active = 0;
    for (auto event : events) {
        int type = event.second.first;
        int id = event.second.second;
        if (type == START) active++;
        else if (type == END) active--;
        else answer[id] = active;
    }
    for (ll count : answer) cout << count << '\n';
}
```

```text
Entrada: 2
         1 3
         3 5
         3
         5 3 1
Saída:   0
         1
         1
```

Com E = 2N + Q eventos, tempo O(E log E), memória O(E).
Offline = conhece as consultas antes da varredura; respostas podem ser reordenadas internamente.
Se chegam online, use o histórico + bounds anterior ou uma estrutura adequada.

<a id="empates"></a>
## EVENTOS NA MESMA COORDENADA — A PRIORIDADE FAZ PARTE DA SOLUÇÃO

| Semântica | Ordem na mesma coordenada | Por quê? |
|---|---|---|
| [L,R) | END → START → QUERY | exclui R e inclui L |
| [L,R] | START → QUERY → END | inclui os dois extremos |

No template, o número do tipo define a prioridade via `sort` do pair.
Para **[L,R]**, mude para `enum { START = 0, QUERY = 1, END = 2 };`
e **não ignore L == R**: um intervalo pontual deve contar na consulta desse ponto.
Um comparador explícito é outra opção, mas não é necessário com esses códigos de tipo.

Para o máximo em [L,R), fins antes de inícios ou agrupamento evitam um pico falso.
Para [L,R], registre o máximo depois dos START e antes dos END.
Em pontos inteiros, remover em R+1 é alternativa para fechado, **só se R+1 couber no tipo**;
a ordenação por tipo acima dispensa essa soma. Não confunda delta -1 com tipo END:
no vetor tipado, END = 0 identifica a ação; a ação é `active--`.

<a id="estado"></a>
## ESTADO ATIVO — QUANTOS OU QUAIS?

| Preciso | Estado | Exemplo neutro / operações |
|---|---|---|
| Apenas QUANTOS | contador | três entradas e uma saída → 2; ++ / -- |
| QUAIS entidades únicas | set de ids | ids 2 e 7; insert(id), erase(id) |
| Valores com duplicatas | multiset | prioridades 2, 2, 7; saída de um 2 deixa 2, 7 |
| Menor / maior atual | set ou multiset | begin() / rbegin(), somente se não vazio |
| Apenas soma de pesos | long long active_sum | entram pesos 5 e 9 → 14; sai 5 → 9 |
| Frequência de cada valor | map, unordered_map ou vetor | três ativos de valor 7 → frequency[7] = 3 |

**Não use set só porque o enunciado diz “ativos”.** Contagem/soma podem ser escalares.
Set de valores perde duplicatas; se precisa distinguir entidades com o mesmo valor,
use ids ou pares (valor,id), ou multiset quando bastar distinguir ocorrências.

### OPERAÇÕES C++ — COPIE SÓ O BLOCO DO ESTADO NECESSÁRIO

Cada bloco abaixo é independente; a atualização substitui o ++/-- na varredura.
Para uma saída real, o evento precisa carregar o id, valor ou peso correspondente.

<!-- search-example: active-structures -->
```cpp
using ll = long long;
{
    ll active = 0;
    active++; active++; active++;
    active--;
    cout << active << '\n'; // 2
}
{
    set<int> active;
    active.insert(2);
    active.insert(7);
    active.erase(2);
    if (!active.empty())
        cout << *active.begin() << ' ' << *active.rbegin() << '\n'; // 7 7
}
{
    multiset<int> active = {2, 2, 7};
    auto it = active.find(2);
    if (it != active.end()) active.erase(it); // remove só UMA ocorrência
    if (!active.empty())
        cout << active.size() << ' ' << *active.begin() << ' ' << *active.rbegin() << '\n'; // 2 2 7
}
{
    ll active_sum = 0;
    active_sum += 5; active_sum += 9;
    active_sum -= 5;
    cout << active_sum << '\n'; // 9
}
{
    map<int, int> frequency;
    frequency[7]++; frequency[7]++; frequency[7]++;
    auto it = frequency.find(7);
    if (it != frequency.end() && --it->second == 0) frequency.erase(it);
    cout << frequency.at(7) << '\n'; // 2 ocorrências restantes
}
```

Em multiset, **erase(value) remove TODAS as ocorrências desse valor**;
`erase(iterator)` remove uma. Não leia extremos de estrutura vazia.
Insert/find/remoção por chave em set/map custam O(log A), onde A é o tamanho ativo;
multiset.erase(value) custa O(log A + removidos). Extremos custam O(1).
Contador/soma/vetor de frequências: O(1) por atualização. Map: O(log A);
unordered_map: O(1) médio, O(A) no pior caso. Vetor só quando o domínio indexável é pequeno
ou comprimido; mantenha soma/frequências dentro do tipo.

<a id="compression"></a>
## QUANDO PRECISO DE COMPRESSÃO?

**Coordinate Compression NÃO é Sweep Line; é uma técnica auxiliar.**
Use quando há poucas coordenadas relevantes, mas valores até 1e9/1e18,
e você precisa de índices para array/vector, Fenwick ou Segment Tree.
100, 500000000, 1000000000 podem virar 0, 1, 2.

**Não precisa de compressão** para guardar eventos nas coordenadas originais, ordenar
e varrer: os dois programas acima já fazem isso sem um vetor de tamanho 1e9.
Está prestes a alocar um vector pelo tamanho da coordenada? Pergunte:
preciso representar cada posição, posso só varrer eventos, ou preciso de índices pequenos?

### NECESSIDADE / RECONHECIMENTO

Valores chegam a 10^9, 10^18 ou são negativos, mas existem poucos valores distintos.
Preciso de índices para frequências, eventos ou estruturas indexadas — não de um vetor até o maior valor.
É um **pré-processamento**, não um algoritmo de busca por resposta.

### IDEIA

1. Copie os valores para não destruir a ordem de entrada.
2. Ordene a cópia.
3. Remova repetidos: cada valor distinto ganha um índice.
4. `lower_bound` encontra o índice do valor original na cópia ordenada.

```text
original:    [100, 5, 100, 1000000000]
distintos:   [5, 100, 1000000000]
comprimido:  [1, 0, 1, 2]
```

### TEMPLATE C++

Entrada: N e N valores. Saída: valor original -> índice (base 0), na ordem de entrada.

<!-- search-example: coordinate-compression -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> values(n);
    for (long long &x : values) cin >> x;

    vector<long long> compressed = values;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

    for (long long x : values) {
        auto index = lower_bound(compressed.begin(), compressed.end(), x) - compressed.begin();
        cout << x << " -> " << index << '\n';
        // compressed[index] recupera o valor original desse índice.
    }
}
```

```text
Entrada: 4
         100 5 100 1000000000
Saída:   100 -> 1
         5 -> 0
         100 -> 1
         1000000000 -> 2
```

### COMPLEXIDADE

Ordenar O(N log N), remover repetidos O(N), mapear N valores O(N log M),
onde M <= N é o número de distintos. Total O(N log N), memória O(N).
Uma conversão posterior por lower_bound custa O(log M).

### ARMADILHAS

- Preserva **igualdade e ordem**: a < b implica índice(a) < índice(b).
  **Não preserva distância**: 1000000000 − 100 não vira 2 − 1.
- `unique` sozinho não encolhe o vetor; use `erase`. Ordene antes para juntar todos os iguais.
- O índice comprimido **não é a posição original** na entrada.
- `lower_bound` só representa um ID exato se o valor estiver na lista.
  Para um valor novo, pode retornar posição de inserção ou end(); confira igualdade.
- Precisa incluir limites de consultas? Reúna as coordenadas necessárias antes de comprimir,
  ou use bounds para localizar intervalos entre coordenadas existentes.
- Em dados online, inserir novas coordenadas pode mudar IDs; não suponha que a compressão inicial basta.


<a id="sweep-armadilhas"></a>
## ARMADILHAS / NÃO CONFUNDIR

- Esquecer sort ou a prioridade de eventos empatados muda o estado consultado.
- Esquecer END mantém entidades ativas para sempre. L = R é vazio apenas em [L,R).
- R versus R+1 depende dos extremos e do domínio; nunca some 1 sem verificar overflow.
- Um vector gigante por coordenada é desnecessário: eventos esparsos ou compressão bastam.
- Set é para guardar quais; contador é para quantos. Multiset precisa remover uma ocorrência por iterador.
- Sweep line organiza mudanças pelo eixo; prefix sum acumula deltas; compressão só cria índices.
- Comprimento da união usa distância entre **coordenadas originais**, não entre IDs comprimidos.
