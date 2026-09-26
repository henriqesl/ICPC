# Estruturas C++

## Vector: índice e remoção

```cpp
vector<int> v = {3,1,3};
auto it = find(v.begin(), v.end(), 3);
int index = it == v.end() ? -1 : int(it - v.begin()); // 0
v.erase(v.begin() + 1); // índice válido: remove 1
it = find(v.begin(), v.end(), 3);
if (it != v.end()) v.erase(it); // primeira ocorrência
v.erase(remove(v.begin(), v.end(), 3), v.end()); // todas
vector<vector<int>> matrix(2, vector<int>(3, 0));
```

Acesso O(1); push_back O(1) amortizado; pop_back O(1), exige não vazio.
insert/erase no meio O(N); find/count O(N); clear O(N); size/empty O(1).
`v.insert(v.begin()+i,x)` permite i==size; erase não permite.
`vector<int> copy = v` copia O(N); const vector<int>& evita cópia em funções.
Iterador aponta para elemento: *it lê valor, ++it avança; end NÃO é elemento.
Realocação por push_back invalida todos os iteradores; erase invalida a partir
da posição removida. Obtenha o iterador novamente após modificar o vetor.

Arrays: `int a[10]{};` tamanho fixo; `int a[n]` com n lido não é C++17 padrão.
Use vector para tamanho de entrada. Para somar ou testar crescimento consecutivo,
processe durante a leitura; armazene se for reordenar, revisitar ou consultar posições.

## Escolha da estrutura

| Estrutura | Operações e custos | Aplicação / cuidado |
|---|---|---|
| stack<int> | push/pop/top O(1) com deque padrão | LIFO, delimitadores; verifique empty |
| queue<int> | push/pop/front O(1) | FIFO; pop não retorna elemento |
| deque<int> | push/pop_front/back O(1); índice O(1) | duas pontas; meio O(N) |
| pair<int,int> | first/second O(1) | dois valores; comparação lexicográfica |
| set<int> | insert/find/erase/lower_bound O(log N) | únicos ordenados; sem índice |
| map<int,int> | consulta/inserção O(log N) | chaves ordenadas; m[x] cria chave se ausente |
| unordered_set/map | O(1) médio, O(N) pior caso | hash; sem ordem garantida |
| priority_queue<int> | push/pop O(log N), top O(1) | máximo no topo; não percorre ordenado sem remover |

```cpp
map<int,int> freq;
for (int x : vector<int>{3,3,8}) ++freq[x];
if (freq.find(7) != freq.end()) { /* existe sem inserir */ }
priority_queue<int, vector<int>, greater<int>> minimum;
set<int> a{1,2}, b{2,3}; // união/interseção precisam dos algoritmos abaixo
vector<int> common, united, difference;
set_intersection(a.begin(),a.end(),b.begin(),b.end(),back_inserter(common));
set_union(a.begin(),a.end(),b.begin(),b.end(),back_inserter(united));
set_difference(a.begin(),a.end(),b.begin(),b.end(),back_inserter(difference));
```

Operações entre conjuntos acima: O(N+M); exigem entradas ordenadas.
Vector preserva ordem e duplicatas; set perde duplicatas; map associa valores.
[Exemplos](../README.md) · [Deque](../data-structures/deque/deque-example.cpp) ·
[Pair](../data-structures/pair/pair-example.cpp).
