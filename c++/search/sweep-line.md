# SWEEP LINE — eventos, empates e compressão

[Índice](README.md) · [Receita](#receita) · [Histórico](#prefix-events) · [Consultas](#query-events) · [Empates](#empates) · [Estado](#estado) · [Compressão](#compression) · [Armadilhas](#sweep-armadilhas)

**Use:** intervalos começam/terminam, e preciso saber o estado ao longo do tempo/posição.

**Ideia:** visite apenas onde muda, não cada coordenada. Exemplos abaixo são 1D.

<a id="receita"></a>
## RECEITA — O QUE MUDA E ONDE?

1. Crie eventos de entrada/saída (e consultas, se necessário).
2. Ordene por posição **e prioridade no empate**.
3. Percorra atualizando o estado; consulte na hora certa.

**[L,R):** +1 em L, -1 em R; L incluído, R excluído. Ignore L=R.
`event.first` = posição; `event.second` = mudança. Recorte dentro do main:

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

**Custo:** E eventos → O(E log E) para ordenar; contador O(1) por evento; memória O(E).

**Cuidado:** em empates, o estado intermediário não é necessariamente o estado válido no ponto.

## INTERVALOS — MÁXIMO E CONSULTAS POR POSIÇÃO

**Use:** máximo simultâneo e quantidade em vários pontos, com intervalos [L,R).

**Ideia:** agrupe mudanças na mesma coordenada e guarde a contagem final; consulta usa último evento <= X.

Entrada: N intervalos L R (L <= R), depois Q e Q pontos.
Saída: máximo simultâneo, depois a quantidade em cada ponto. Coordenadas negativas/grandes funcionam.

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

**Custo:** O(N log N + Q log N), memória O(N). Só máximo? Não precisa guardar histórico.

**Cuidado:** [1,3) e [3,5) não se sobrepõem. Para [L,R], adapte os extremos; não ignore L=R.

<details>
<summary>Entender melhor: exemplo e alternativa com diferenças</summary>

`[1,4)` e `[3,6)` → contagens em 1,3,4,6: `1,2,1,0`; máximo `2`.
Consultas em 0,3,4 → `0,2,1`.

Coordenadas inteiras pequenas [0,U]: vetor de diferenças permite O(U+N+Q), mas usa O(U) de memória.
Comprimento da união usa distâncias originais entre eventos quando active > 0.

</details>

<a id="prefix-events"></a>
## PREFIX SUM DE EVENTOS — PRECISO GUARDAR?

**Só resposta durante a varredura:** use o contador `active += delta`.
**Histórico por evento:** após ordenar events, o recorte abaixo guarda todos os prefixos.

<!-- search-example: prefix-events -->
```cpp
vector<long long> accumulated(events.size());
for (size_t i = 0; i < events.size(); i++) {
    accumulated[i] = (i == 0 ? 0 : accumulated[i - 1]) + events[i].second;
}
```

**Custo:** O(E) para acumular, O(E) memória adicional.

**Cuidado:** esse histórico é por evento, não por coordenada; para consultar um ponto, agrupe empates como acima.

<a id="query-events"></a>
## START / END / QUERY — CONSULTAS OFFLINE

**Use:** conhece as consultas antes de processar; quer responder na ordem original.

**Precisa:** escolher [L,R) ou [L,R] e aplicar a [prioridade correta](#empates).

**Ideia:** um vetor com posição, tipo, id. Ao chegar em QUERY, salve answer[id].

Entrada: N intervalos L R (L <= R), depois Q e Q pontos.
Saída: quantidade de intervalos contendo cada ponto, na ordem das consultas.

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

**Custo:** E=2N+Q → O(E log E), memória O(E).

**Cuidado:** conhece todas as consultas antes (offline). Consultas posteriores podem usar histórico + bounds.

<details>
<summary>Entender melhor: exemplo</summary>

Intervalos [1,3), [3,5); consultas `5 3 1` → `0 1 1`.
O id da consulta permite ordenar internamente sem mudar a ordem da saída.

</details>

<a id="empates"></a>
## EMPATES — CONFIRA ANTES DE COPIAR

| Intervalo | Ordem no mesmo ponto | Ajuste no template |
|---|---|---|
| [L,R) | END → START → QUERY | `END=0, START=1, QUERY=2`; ignore L=R |
| [L,R] | START → QUERY → END | `START=0, QUERY=1, END=2`; **não ignore L=R** |

Para máximo em [L,R], consulte após START e antes de END.
Remover em R+1 é alternativa só para coordenadas inteiras e se R+1 couber no tipo.
`END=0` é o tipo da ação; a mudança na contagem é -1, não 0.

<a id="estado"></a>
## ESTADO ATIVO — QUANTOS OU QUAIS?

| Preciso | Guarde | Atualização |
|---|---|---|
| Quantos | contador | ++ / --, O(1) |
| Soma de pesos | long long | += peso / -= peso, O(1) |
| Quais entidades | set de ids | insert / erase, O(log A) |
| Valores com cópias | multiset | insert / find + erase(it), O(log A) |
| Menor/maior | set ou multiset | *begin / *rbegin, O(1), não vazio |
| Frequências | vetor / map / unordered_map | O(1) / O(log A) / O(1) médio |

A = tamanho ativo. Hash pode custar O(A) por operação no pior caso.
Copie só o estado necessário; evento de saída precisa carregar id/valor/peso.

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

**Cuidado:** set de valores perde repetidos; use ids, pares (valor,id) ou multiset.
`multiset.erase(valor)` apaga todas as C cópias em O(log A+C); `erase(it)` apaga uma. Não leia extremos vazios.

<a id="compression"></a>
## COMPRESSÃO — VALORES ENORMES, ÍNDICES PEQUENOS

**Use:** poucas coordenadas relevantes, mas preciso indexar um vetor/Fenwick.
**Não precisa:** só ordenar eventos nas coordenadas originais e varrer.

**Ideia:** copie → sort → unique + erase → lower_bound para obter o id.

Entrada: N e N valores. Saída: valor original → índice comprimido (base 0), na ordem de entrada.

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

**Custo:** O(N log N) para preparar/mapear, O(N) memória; conversão posterior O(log M), M distintos.

**Cuidado:** preserva igualdade/ordem, **não distância** nem posição original. unique sozinho não encolhe o vetor.

<details>
<summary>Entender melhor: exemplo e consultas novas</summary>

`[100,5,100,1000000000]` → distintos `[5,100,1000000000]` → ids `[1,0,1,2]`.

`compressed[id]` recupera o valor. Lower_bound de valor ausente dá posição de inserção, não um ID exato.
Reúna as coordenadas relevantes antes; novas coordenadas online podem mudar IDs.
Para limites de consulta ausentes, use bounds/intervalos entre valores, sem supor igualdade.

</details>

<a id="sweep-armadilhas"></a>
## ARMADILHAS / NÃO CONFUNDIR

- Evento de saída e ordem de empate importam tanto quanto sort.
- [L,R) exclui R; [L,R] inclui. L=R só é vazio no primeiro.
- Contador para **quantos**; set para **quais**; multiset para cópias.
- Sweep organiza mudanças; prefix sum acumula; compressão cria índices.
- Comprimento usa coordenadas originais, não diferenças entre IDs.
