# Estruturas C++

Ainda não sabe qual escolher? Consulte [QUAL ESTRUTURA USAR?](../../QUAL-ESTRUTURA-USAR.md):
operação → candidata, custo e limitações.

Aprendendo agora? Comece pela [comparação map, unordered_map, set e multiset](maps-and-sets.md).
Fila/pilha/deque/heap ficam em [data-structures](../data-structures/), sem subpastas.

[Vector](#vector) · [Array](#array) · [Pair](#pair) · [Frequências](#frequency-counting)

Confundiu posição, valor e índice? [Iteradores: begin/end, *it e it->](iterators.md),
com [exemplo executável](iterators.cpp).

Snippets independentes, dentro de `main()`, com o [template](../template.cpp).
Antes de `front/back/pop`, confira que não está vazio; nunca leia `*end()`.

<a id="vector"></a>

## Vector

### Quando pensar nisso?

- “Preciso ler/alterar a posição i.”
- “Preciso guardar a sequência e preservar a ordem original.”

### Ideia simples

Guarda uma sequência indexada e pode crescer no fim. É a primeira opção para
dados de entrada que serão revisitados. Não torna busca por valor rápida.

### Exemplo de contest

Notas [3,1,3]: a posição 1 contém 1. Alterar essa posição para 7 produz [3,7,3];
não é uma busca pelo valor 1.

### Operações que preciso lembrar

<!-- example: vector -->
```cpp
vector<int> v{3, 1, 3};
v[1] = 7; v.push_back(8);
cout << v[1] << ' ' << v.back(); // 7 8
v.pop_back(); // remove o último, não retorna o valor
```

`vector<int>(N,0)` cria N posições. `reserve(N)` só reserva capacidade,
não permite acessar posições que ainda não existem.

### Complexidade

Índice O(1); `push_back` O(1) amortizado; `pop_back` O(1).
Busca/contagem por valor e inserção/remoção no meio O(N); memória O(N).

### Não confundir com

Set ordena por valor e perde duplicatas; vector mantém posições e duplicatas.
Deque é melhor para retirar frequentemente da frente.
[Aplicação executável](vector.cpp).

<a id="array"></a>

## Array

### Quando pensar nisso?

- “Tenho sempre 26 letras ou 10 dígitos.”
- “O tamanho é conhecido antes de executar.”

### Ideia simples

`array<T,K>` é uma sequência de tamanho fixo, conhecido ao compilar.
Útil para domínios pequenos; não pode crescer com `push_back`.

### Exemplo de contest

Contar as letras de “aba”: posição 0 representa 'a', posição 1 representa 'b'.
Resultado: duas letras 'a' e uma 'b'.

### Operações que preciso lembrar

<!-- example: array -->
```cpp
array<int, 26> freq{}; // zeros; inclui <array>
for (char c : string("aba")) freq[c - 'a']++;
cout << freq[0] << ' ' << freq[1]; // 2 1
freq.fill(0); // zera tudo para outro caso
```

### Complexidade

Índice O(1); preencher/percorrer O(K); memória O(K).

### Não confundir com

Vector aceita N lido na entrada. `int a[N]` com N variável não é C++17 padrão;
`int a[26]{}` é válido, mas `array` oferece `size/begin/end/fill`.
O exemplo supõe caracteres entre 'a' e 'z'.

<a id="pair"></a>

## Pair

### Quando pensar nisso?

- “Preciso ordenar valores sem perder o índice original.”
- “Cada item tem duas informações: fim/início, custo/id...”

### Ideia simples

Junta dois campos em um item. Por padrão, compara `first` e desempata com `second`.
Não armazena uma coleção sozinho: costuma ficar dentro de vector, set ou heap.

### Exemplo de contest

Valores [8,3,3] viram pares (8,0), (3,1), (3,2).
Depois de ordenar, o primeiro par é (3,1): valor 3, índice original 1.

### Operações que preciso lembrar

<!-- example: pair -->
```cpp
vector<pair<int, int>> v{{8, 0}, {3, 1}, {3, 2}};
sort(v.begin(), v.end());
cout << v.front().first << ' ' << v.front().second; // 3 1
```

### Complexidade

Acessar/comparar os dois campos inteiros O(1); ordenar N pares O(N log N).

### Não confundir com

Map associa uma chave a um valor; pair só junta campos e aceita pares repetidos
quando usado em vector. Para ordenar por outro critério, veja
[custom comparator](../algorithms/patterns.md#custom-comparator).
[Aplicação executável](../data-structures/pair.cpp).

<a id="frequency-counting"></a>

## Frequency counting

### Quando pensar nisso?

- “Quantas vezes cada valor apareceu?”
- “Quantos valores diferentes existem dentro do trecho atual?”

### Ideia simples

Guarde uma contagem por valor em vez de recontar a sequência a cada pergunta.
Domínio pequeno/denso → vector/array; chaves enormes/esparsas → mapa.

### Exemplo de contest

[3,3,8] dá frequência(3)=2 e frequência(8)=1. Se um 3 sai da janela, fica 1.
`freq.size()` conta distintos apenas se não houver chaves com frequência zero.

### Operações que preciso lembrar

<!-- example: frequency -->
```cpp
unordered_map<int, int> freq;
for (int x : {3, 3, 8}) freq[x]++;
int sai = 8;
if (--freq[sai] == 0) freq.erase(sai); // sai deve estar presente
cout << freq[3] << ' ' << freq.size(); // 2 1
```

### Complexidade

Vector/array: O(1) por alteração/consulta. Unordered_map: O(1) médio,
O(N) pior caso; map: O(log D), com D distintos. Memória depende do domínio/D.

### Não confundir com

Set responde presença, não frequência. `multiset.count(x)` anda pelas C cópias:
O(log N + C), não é O(log N) sozinho. Para consultar ausente sem inserir,
use `find` no mapa. [Mapas](maps-and-sets.md),
[janela com frequências](../algorithms/sliding-window-distinct.cpp).

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
[Exemplos](../README.md) · [Deque](../data-structures/deque.cpp) ·
[Pair](../data-structures/pair.cpp).
