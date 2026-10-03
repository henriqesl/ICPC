# Map, unordered_map, set ou multiset?

[Mapa](../../MAPA-DE-RESOLUCAO.md) · [Set](#set) · [Multiset](#multiset) ·
[Unordered_set](#unordered-set) · [Map](#map) · [Unordered_map](#unordered-map)

Os recortes marcados são independentes e vão dentro de `main()`, com o
[template](../template.cpp). Nos conjuntos, `*it` é o valor;
nos mapas, `it->first` é a chave e `it->second` é a informação associada.

| O que guardar | Ordenado? | Estrutura | Arquivo |
|---|---|---|---|
| Chave e valor: número → frequência | Por chave | map | [map.cpp](map.cpp) |
| Chave e valor, sem precisar de ordem | Não | unordered_map | [unordered-map.cpp](unordered-map.cpp) |
| Apenas valores, sem repetição | Sim | set | [set.cpp](set.cpp) |
| Apenas valores, com repetição | Sim | multiset | [multiset.cpp](multiset.cpp) |
| Apenas presença, sem precisar de ordem | Não | unordered_set | [exemplo abaixo](#unordered-set) |

Imagine os valores **3, 1, 3, 8, 3**:

- set guarda **1, 3, 8**.
- multiset guarda **1, 3, 3, 3, 8**.
- map de frequência guarda **1 → 1, 3 → 3, 8 → 1**.
- unordered_map guarda as mesmas associações, sem ordem de percurso garantida.

<a id="map"></a>

## Map

### Quando pensar nisso?

- “Chave → informação, e quero percorrer as chaves em ordem.”
- “Preciso do primeiro código >= X e da informação dele.”

### Ideia simples

Guarda uma informação por chave, mantendo as chaves ordenadas.
Alterar uma chave existente substitui a informação; não cria uma segunda cópia.

### Exemplo de contest

Cadastro: Ana → 20. Atualizar Ana → 21 mantém uma chave.
Consultar Bia com `find` pode informar ausência sem cadastrar Bia por acidente.

### Operações que preciso lembrar

<!-- example: map -->
```cpp
map<string, int> idade;
idade["Ana"] = 20; // chave "Ana", valor 20
idade["Ana"] = 21; // substitui o valor; não cria outra Ana
cout << idade["Ana"]; // 21
auto it = idade.find("Bia");
if (it != idade.end()) cout << it->second; // não insere Bia
```

Em contagem, `frequencia[x]++` cria zero se necessário e incrementa.
Mas uma consulta `frequencia[x]` também insere se x estiver ausente.
Para não modificar, use `find` como no recorte.

`auto` pede que o compilador descubra o tipo. `it` é um iterador que aponta
para a associação encontrada. `end()` significa “não encontrou” nesse contexto.
`it->first` é a chave e `it->second` é o valor. Nunca acesse end.
`idade.erase("Ana")` remove a chave. `size()` conta chaves, não soma frequências.

### Complexidade

Consultar/inserir/remover por chave e `lower_bound/upper_bound`: O(log N).
Percorrer O(N); memória O(N), com N chaves. Comparar strings pode custar mais.

### Não confundir com

Unordered_map não ordena chaves. Set guarda só a chave, não uma informação.
Map de índice → 0/1 pode ser desperdício se um vector pequeno resolver em O(1).
O menor de um map é a menor CHAVE, não a menor idade/frequência.
[Aplicação executável](map.cpp).

<a id="unordered-map"></a>

## Unordered_map

### Quando pensar nisso?

- “Preciso contar/consultar por chave, mas a ordem não importa.”
- “Os valores são enormes e só alguns aparecem.”

### Ideia simples

Associa chave → informação como map, mas usa hash, sem ordenar as chaves.
A sintaxe de contagem é a mesma; não oferece vizinhos por ordem.

### Exemplo de contest

[3,3,8] gera 3 → 2 e 8 → 1. Perguntar por 7 deve retornar zero
sem criar mais uma chave se estamos contando distintos com `size()`.

### Operações que preciso lembrar

<!-- example: unordered-map -->
```cpp
unordered_map<int, int> freq;
for (int x : {3, 3, 8}) freq[x]++;
auto it = freq.find(7);
cout << (it == freq.end() ? 0 : it->second); // 0
freq.erase(8);
```

### Complexidade

Busca/inserção/remoção O(1) médio, O(N) pior caso; memória O(N).
`reserve` pode reduzir realocações, não elimina o pior caso do hash.

### Não confundir com

Unordered_set guarda só presença; unordered_map guarda uma informação/contagem.
`begin()` não é a menor chave e não existem `lower_bound/upper_bound`.
Se precisa de ordem/garantia O(log N), use map.
[Aplicação executável](unordered-map.cpp).

<a id="set"></a>

## Set

### Quando pensar nisso?

- “Valores ativos entram e saem.”
- “Preciso de únicos ordenados, do primeiro >= X ou de um ativo em [L,R].”

### Ideia simples

Mantém valores únicos e ordenados, mesmo após inserir/remover.
É útil para pular diretamente para o próximo valor relevante sem varrer posições vazias.

### Exemplo de contest

Ativos {1,4,5,9}. Existe alguém em [3,7]?
`lower_bound(3)` aponta para 4. Como 4 <= 7, existe; para [6,8], aponta para 9 e falha.

### Operações que preciso lembrar

<!-- example: set -->
```cpp
set<int> s{1, 4, 5, 9};
s.insert(4); s.erase(9); // repetir 4 não cria outro
auto it = s.lower_bound(3);
cout << (it != s.end() && *it <= 7); // 1: existe em [3,7]
```

`s.find(x)` testa presença exata; `*s.begin()` / `*s.rbegin()` consultam extremos
somente se não vazio. [Todos os vizinhos](#extremos-e-vizinhos).

### Complexidade

`insert`, `erase(x)`, `find`, `lower_bound`, `upper_bound`: O(log N).
Extremos/size O(1); memória O(N). Contar iteradores no intervalo pode ser O(N).

### Não confundir com

Unordered_set: presença O(1) médio, sem ordem/bounds. Multiset preserva repetidos.
Vector de bits testa uma posição em O(1), mas varrer [L,R] custa O(R-L+1);
se os bits são fixos, prefixos de contagem também resolvem existência.
Set não permite `s[i]`. [Aplicação executável](set.cpp).

<a id="multiset"></a>

## Multiset

### Quando pensar nisso?

- “Valores repetem, entram/saem, e preciso manter ordem.”
- “Preciso apagar um valor específico, não necessariamente o menor.”

### Ideia simples

É como set, mas preserva cada cópia. Permite retirar um valor arbitrário
e continuar consultando extremos/vizinhos; não dá acesso rápido ao item do meio.

### Exemplo de contest

[1,3,3,8]: sai UM 3 e entra 5 → [1,3,5,8].
Usar `erase(3)` apagaria os dois 3, o que é errado se saiu só um item da janela.

### Operações que preciso lembrar

<!-- example: multiset -->
```cpp
multiset<int> s{1, 3, 3, 8};
s.insert(5);
auto it = s.find(3);
if (it != s.end()) s.erase(it); // uma cópia
for (int x : s) cout << x << ' '; // 1 3 5 8
```

`s.erase(3)` apaga TODAS as cópias; `s.erase(s.lower_bound(3),s.upper_bound(3))`
também. Confirme `it != end()` para apagar uma cópia encontrada.

### Complexidade

Inserir/buscar e `find` + apagar uma cópia O(log N). Apagar C cópias por valor:
O(log N + C). Extremos O(1); avançar K posições O(K); memória O(N).

### Não confundir com

Priority_queue retira só o topo. Multiset permite remoção arbitrária, mas
`advance(it,size()/2)` não consulta mediana em O(log N): anda O(N).
Para mediana dinâmica, veja [dois multisets](../data-structures/README.md#median).
[Aplicação executável](multiset.cpp).

<a id="unordered-set"></a>

## Unordered_set

### Quando pensar nisso?

- “Só preciso saber se um código já apareceu.”
- “Preciso de únicos, mas não quero vizinhos nem percurso ordenado.”

### Ideia simples

Guarda presença usando hash. Repetir o valor não cria cópia nem contagem.
Não mantém ordem por valor e não oferece bounds.

### Exemplo de contest

Chegam códigos 3,8,3: o segundo 3 já estava presente; ficam dois distintos.

### Operações que preciso lembrar

<!-- example: unordered-set -->
```cpp
unordered_set<int> vistos{3, 8};
cout << (vistos.find(3) != vistos.end()); // 1
vistos.insert(3); vistos.erase(8);
cout << ' ' << vistos.size(); // 1
```

### Complexidade

Insert/find/erase O(1) médio, O(N) pior caso; memória O(N).

### Não confundir com

Unordered_map responde quantas vezes apareceu. Set mantém ordem e tem
`lower_bound` em O(log N). `begin()` de unordered_set não significa menor valor.

## Extremos e vizinhos

Para set/multiset/map ordenados crescentes:

| Objetivo | Expressão | Verificação antes de ler |
|---|---|---|
| Primeiro/menor | begin() | !empty() |
| Último/maior | rbegin(), ou prev(end()) | !empty() |
| Primeiro >= X | lower_bound(X) | it != end() |
| Primeiro > X | upper_bound(X) | it != end() |
| Último < X | prev(lower_bound(X)) | lower_bound(X) != begin() |
| Último <= X | prev(upper_bound(X)) | upper_bound(X) != begin() |

set/multiset: leia *it. map: it->first é a chave e it->second é o valor.
begin/rbegin dão extremos pela ordem das CHAVES, não pela frequência armazenada.
end não é o último elemento: é a posição após ele. Nunca leia *end nem prev(begin).
Inclua <iterator> para prev. Em vazio, begin == end, e nenhum extremo pode ser lido.

[bounds.cpp](../algorithms/bounds.cpp) executa as consultas de limites e vizinhos.
No vector ordenado, use lower_bound(v.begin(),v.end(),x); it-v.begin() dá índice.
No set/multiset/map, use s.lower_bound(x), que usa a árvore em O(log N).
O algoritmo genérico com iteradores de set pode avançar O(N) vezes.
Em multiset, distance(lower,upper) custa O(quantidade), e upper-lower não compila.

Ex.: [1,3,3,8] com X=3: lower aponta para o primeiro 3, upper para 8.
O intervalo [lower,upper) contém os dois 3; em vector, upper-lower vale 2.
Para X=20, ambos são end: isso é uma resposta válida da busca, não um valor acessível.
Em unordered_map não existem bounds nem extremos por chave.

## Custos para N elementos

| Operação | map / set / multiset | unordered_map |
|---|---|---|
| Inserir / buscar | O(log N) | O(1) médio, O(N) pior caso |
| Remover por chave | O(log N); multiset soma custo das ocorrências removidas | O(1) médio, O(N) pior caso |
| Percorrer tudo | O(N), ordenado | O(N), sem ordem de classificação |
| count(x) | map/set: O(log N); multiset: O(log N + ocorrências) | O(1) médio |

Chaves longas também custam para comparar/calcular hash. Para frequências de
valores pequenos de 0 até M, um vector<int>(M+1) pode ser mais simples.
