# Padrões: qual operação o enunciado esconde?

[Consulta geral](../../README.md) · [Exemplos executáveis](README.md)

[Sort](#sort) · [Comparator](#custom-comparator) · [Lower bound](#lower-bound) ·
[Upper bound](#upper-bound) · [Binary search](#binary-search) ·
[Two pointers](#two-pointers) · [Monotonic stack](#monotonic-stack) · [Monotonic deque](#monotonic-deque)

[Prefix sum e sliding window](prefix-and-window.md) têm um guia próprio.
Snippets dentro de `main()`, com o [template](../template.cpp), sem ler entrada.

<a id="sort"></a>

## Sort

**Use quando:** Depois de agrupar iguais, consultar vizinhos ou buscar fica fácil; Os dados não mudam: posso ordenar uma vez.

**Precisa:** ordenar não pode destruir informação exigida; preserve (valor,id) se necessário.

### Template / operações

<!-- example: sort -->
```cpp
vector<int> v{8, 3, 1, 3};
sort(v.begin(), v.end());
for (int x : v) cout << x << ' '; // 1 3 3 8
sort(v.rbegin(), v.rend()); // decrescente
```

### Complexidade

O(N log N). Vector guarda O(N) itens; sort modifica a sequência.

### Não confundir com

Set/multiset mantêm ordem durante inserções/remoções. Sort não preserva a ordem
anterior dos empates; `stable_sort` preserva. Para só um extremo, min/max_element
custam O(N), sem ordenar. [sorting.cpp](sorting.cpp).

Quer ordenar um trecho, uma coluna, pelo second ou só uma lista de índices?
Abra [Sort: variantes e índices](sorting.md). Se begin/end ainda confundem,
leia [Iteradores: posição, valor ou índice?](../basics/iterators.md).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Organiza a sequência por valor. Pague a ordenação uma vez e aproveite a ordem
nas consultas seguintes; não ordene de novo em cada pergunta.

### Exemplo de contest

[8,3,1,3] vira [1,3,3,8]. Os dois 3 ficam juntos, e bounds encontram seu intervalo.
Se precisa responder índices originais, carregue pares (valor,índice).

</details>

<a id="custom-comparator"></a>

## Custom comparator — qual item vem antes?

**Use quando:** Maior pontuação primeiro; empate → menor id; Quero ordenar pelo segundo campo, não pelo primeiro.

**Precisa:** comparação coerente, estrita; a vs a retorna false.

### Template / operações

<!-- example: comparator -->
```cpp
vector<pair<int, int>> v{{10, 2}, {10, 1}, {8, 0}};
sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
    if (a.first != b.first) return a.first > b.first; // pontuação maior
    return a.second < b.second; // id menor
});
for (auto p : v) cout << p.first << ':' << p.second << ' ';
```

### Complexidade

Sort O(N log N) com comparação de dois inteiros O(1).

### Não confundir com

`<=`/`>=` não servem como desempate: comparar um item consigo deve dar false.
A regra deve ser coerente/transitiva: não crie um ciclo a antes de b, b antes de c,
c antes de a. Pair já ordena first e depois second, ambos crescentes, sem lambda.
Bounds precisam usar a mesma ordem da ordenação; os recortes abaixo são crescentes.

[Ordenar pela coluna j](sorting.md#column) · [Ordenar índices do vetor](sorting.md#indices).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

A comparação responde: **a deve vir antes de b?** A lambda abaixo é uma regra
curta colocada no sort, não um algoritmo novo. Em empate total, responda false.

### Exemplo de contest

Pares (pontuação,id): (10,2), (10,1), (8,0).
Maior pontuação e menor id no empate → (10,1), (10,2), (8,0).

</details>

<a id="lower-bound"></a>

## Lower_bound — primeiro >= X

**Use quando:** Quero o primeiro preço que chega a X; Quero pular diretamente para a primeira posição ativa >= L.

**Precisa:** vector ordenado crescente ou método de set/map; conferir end antes de ler.

### Template / operações

<!-- example: lower-bound -->
```cpp
vector<int> v{1, 3, 3, 8}; // ordenado
auto it = lower_bound(v.begin(), v.end(), 3);
if (it != v.end()) cout << *it << ' ' << (it - v.begin()); // 3 1
```

Set/multiset/map: `s.lower_bound(X)`, não a função genérica com iteradores.
Presença exata: `it != v.end() && *it == X`. Nunca leia `*end()`.

### Complexidade

O(log N) no vector ordenado ou no método do conjunto/mapa.
O genérico em iteradores de set pode avançar O(N).

### Não confundir com

Upper_bound exige > X. Find procura exatamente X. Vector tem índice por
`it - begin()`; set/multiset não têm essa subtração nem acesso por índice.
[bounds.cpp](bounds.cpp), [set](../basics/maps-and-sets.md#set).

Busca em pares (valor,índice): procure `(X,-1)` quando todos os índices são >= 0.
Assim o limite fica antes de qualquer cópia com valor X:

<!-- example: pair-bound -->
```cpp
vector<pair<int, int>> v{{8, 0}, {3, 1}, {3, 2}};
sort(v.begin(), v.end());
auto it = lower_bound(v.begin(), v.end(), make_pair(3, -1));
if (it != v.end() && it->first == 3) cout << it->second; // índice original 1
```

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Devolve um iterador para o primeiro candidato >= X na ordem crescente.
Pode apontar para um valor maior que X; igualdade exige outra conferência.

### Exemplo de contest

[1,3,3,8], X=3 → primeiro 3, índice 1. X=4 → 8. X=20 → end, sem candidato.

</details>

<a id="upper-bound"></a>

## Upper_bound — primeiro > X

**Use quando:** Preciso pular todas as cópias de X; Tenho muitas perguntas: quantos valores são <= X?.

**Precisa:** vector ordenado crescente ou método de set/map; conferir end antes de ler.

### Template / operações

<!-- example: upper-bound -->
```cpp
vector<int> v{1, 3, 3, 8};
auto it = upper_bound(v.begin(), v.end(), 3);
if (it != v.end()) cout << *it << ' '; // 8
cout << (it - v.begin()); // 3 valores <= 3, mesmo se it == end()
```

Contar em [L,R]: `upper_bound(R) - lower_bound(L)`, usando os iteradores do vector.
No conjunto, use `s.upper_bound(X)`; contar a distância entre iteradores é linear.

### Complexidade

O(log N) por busca; diferença de iteradores de vector O(1).
Ordenar antes custa O(N log N), uma vez. Conte Q buscas: O(N log N + Q log N).

### Não confundir com

Lower_bound aceita igualdade; upper não. Se o resultado é end, não pode ler
o valor, mas ainda pode calcular o índice no vector. [bounds.cpp](bounds.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Devolve o primeiro valor estritamente maior. Num vector ordenado, o índice desse
iterador é justamente a quantidade de elementos <= X.

### Exemplo de contest

[1,3,3,8], X=3 → aponta para 8, índice 3: três elementos são <= 3.
Quantidade de 3 = índice upper - índice lower = 3 - 1 = 2.

</details>

<a id="binary-search"></a>

## Binary search — uma mudança de falso para verdadeiro

**Use quando:** Primeiro valor/limite que satisfaz a condição; Se a resposta X funciona, qualquer resposta maior também funciona.

**Precisa:** teste monotônico FFFTTT; este recorte usa [l,r), não intervalo fechado.

### Template / operações

<!-- example: binary-search -->
```cpp
vector<int> v{1, 3, 3, 8}; int x = 3;
int l = 0, r = int(v.size()); // intervalo [l,r), r exclusivo
while (l < r) {
    int m = l + (r-l)/2;
    if (v[m] >= x) r = m;
    else l = m + 1;
}
cout << l; // 1; se l == size(), não existe candidato
```

### Complexidade

O(log N) testes. Na busca sobre uma resposta, se cada teste custa T,
o total é O(T log U), com U candidatos inteiros; não é automaticamente O(log N).

### Não confundir com

N grande não prova monotonicidade. `binary_search` da STL devolve bool de presença;
lower/upper_bound devolvem limites. Não misture intervalo fechado com [l,r).
[binary-search.cpp](binary-search.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

O teste precisa ter uma única transição: falso, falso, verdadeiro, verdadeiro.
Teste o meio e descarte a metade que não pode conter o primeiro verdadeiro.

### Exemplo de contest

[1,3,3,8], condição valor >= 3 → F,V,V,V. O primeiro V fica no índice 1.
Em [3,1,8], o teste V,F,V não permite esse descarte: falta monotonicidade.

</details>

<a id="two-pointers"></a>

## Two pointers — dois índices, sem testar todos os pares

**Use quando:** Dois valores somam um alvo e a sequência está ordenada; Consigo avançar cada índice sem precisar voltar atrás.

**Precisa:** vector crescente; índices distintos. Negativos são permitidos.

### Template / operações

<!-- example: two-pointers -->
```cpp
vector<int> v{1, 3, 4, 7}; int l = 0, r = 3, alvo = 10;
while (l < r) {
    long long soma = 1LL*v[l] + v[r];
    if (soma == alvo) { cout << l << ' ' << r; break; }
    if (soma < alvo) l++; else r--;
}
```

### Complexidade

O(N) depois de ordenar; sort prévio custa O(N log N). Estado O(1).

### Não confundir com

Aqui escolhemos dois elementos, não somamos um trecho inteiro.
Sliding window também usa dois índices, com outra regra. Esse exemplo aceita
negativos, encontra um par e não conta todos os pares. Preserve índices antes de ordenar
se a saída exige posições originais. [two-pointers.cpp](two-pointers.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Use a ordem para descartar pares: soma pequena → aumentar o menor;
soma grande → diminuir o maior. É preciso justificar qual movimento é seguro.

### Exemplo de contest

[1,3,4,7], alvo 10. Pontas: 1+7=8; avance esquerda → 3+7=10.

</details>

<a id="monotonic-stack"></a>

## Monotonic stack — próximo menor/maior de um lado

**Use quando:** Para cada posição, qual é o primeiro menor à esquerda/direita?; Até onde este elemento pode ser o mínimo de um subarray?.

**Precisa:** preservar posições; este recorte procura menor estrito à esquerda.

### Template / operações

<!-- example: monotonic-stack -->
```cpp
vector<int> v{3, 1, 2}, anterior(3, -1); stack<int> st;
for (int i = 0; i < int(v.size()); i++) {
    while (!st.empty() && v[st.top()] >= v[i]) st.pop();
    if (!st.empty()) anterior[i] = st.top();
    st.push(i);
}
for (int i : anterior) cout << i << ' '; // -1 -1 1: índices
```

Menor à direita: percorra ao contrário com pilha vazia.
Maior estrito: descarte `<=`; menor ou igual: descarte `>`;
maior ou igual: descarte `<`.

### Complexidade

O(N) tempo e memória: cada índice entra e sai no máximo uma vez,
apesar do while dentro do for.

### Não confundir com

Sort perde esquerda/direita. Não é consulta arbitrária de mínimo em [L,R].
Para somar mínimos de subarrays, trate empates: menor estrito de um lado,
menor ou igual do outro, evitando contar o mesmo trecho duas vezes.
[monotonic-stack.cpp](monotonic-stack.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Guarde índices de candidatos numa pilha com valores em ordem. Descarte do topo
os que não servem; o topo restante é o vizinho mais próximo procurado.

### Exemplo de contest

[3,1,2]: para o último 2, o menor mais próximo à esquerda é 1, no índice 1.
Para o 1, não há menor à esquerda: descarte o 3.

</details>

<a id="monotonic-deque"></a>

## Monotonic deque — mínimo/máximo de cada janela

**Use quando:** Qual é o máximo dos K últimos elementos, a cada avanço?; Sai o mais antigo, entra um novo, e quero só o extremo da janela.

**Precisa:** 1 <= K <= N; este recorte calcula máximo e guarda índices.

### Template / operações

<!-- example: monotonic-deque -->
```cpp
vector<int> v{2, 1, 5, 1, 3}; int k = 3; deque<int> d;
for (int r = 0; r < int(v.size()); r++) {
    while (!d.empty() && d.front() <= r-k) d.pop_front(); // expirou
    while (!d.empty() && v[d.back()] <= v[r]) d.pop_back(); // dominado
    d.push_back(r);
    if (r >= k-1) cout << v[d.front()] << ' '; // 5 5 5
}
```

Para mínimo, descarte do fim valores `>=` ao novo. Exige 1 <= K <= N.
Usar índices permite saber se o candidato saiu, inclusive com valores repetidos.

### Complexidade

O(N) tempo total, O(K) memória da deque. Cada índice entra e sai uma vez.

### Não confundir com

Deque comum não faz esses descartes sozinho. Mediana precisa de outros candidatos
e não funciona com esta regra. Heap pode resolver extremos com expiração controlada,
mas custa O(log N) por operação e pode acumular entradas antigas.
[monotonic-deque.cpp](monotonic-deque.cpp), [janela e sua consulta](prefix-and-window.md#sliding-window).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Guarde índices de candidatos, não todos os itens. Para máximo, os valores ficam
decrescentes. Retire da frente os expirados e do fim os dominados pelo novo item.
O maior válido fica na frente; o novo candidato dura mais que os antigos.

### Exemplo de contest

[2,1,5,1,3], K=3 → máximos 5,5,5. Ao entrar 5, descarte 1 e 2:
o 5 é maior e também sairá mais tarde da janela. Um 1 novo não descarta o 5.

</details>
