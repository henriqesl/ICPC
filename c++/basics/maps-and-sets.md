# Map, unordered_map, set ou multiset?

| O que guardar | Ordenado? | Estrutura | Arquivo |
|---|---|---|---|
| Chave e valor: número → frequência | Por chave | map | [map.cpp](map.cpp) |
| Chave e valor, sem precisar de ordem | Não | unordered_map | [unordered-map.cpp](unordered-map.cpp) |
| Apenas valores, sem repetição | Sim | set | [set.cpp](set.cpp) |
| Apenas valores, com repetição | Sim | multiset | [multiset.cpp](multiset.cpp) |

Imagine os valores **3, 1, 3, 8, 3**:

- set guarda **1, 3, 8**.
- multiset guarda **1, 3, 3, 3, 8**.
- map de frequência guarda **1 → 1, 3 → 3, 8 → 1**.
- unordered_map guarda as mesmas associações, sem ordem de percurso garantida.

## Map: uma coisa associada a outra

```cpp
map<string, int> idade;
idade["Ana"] = 20; // chave "Ana", valor 20
idade["Ana"] = 21; // substitui o valor; não cria outra Ana
cout << idade["Ana"]; // 21
```

Em contagem, `frequencia[x]++` cria zero se necessário e incrementa.
Mas uma consulta `frequencia[x]` também insere se x estiver ausente.
Para não modificar:

```cpp
auto it = idade.find("Bia");
if (it != idade.end()) cout << it->second;
```

`auto` pede que o compilador descubra o tipo. `it` é um iterador que aponta
para a associação encontrada. `end()` significa “não encontrou” nesse contexto.
`it->first` é a chave e `it->second` é o valor. Nunca acesse end.
`idade.erase("Ana")` remove a chave. `size()` conta chaves, não soma frequências.

## Unordered_map: mesma ideia, outra organização

Troque o tipo por `unordered_map<string, int>` e inclua <unordered_map>.
A sintaxe principal é a mesma. Use se não precisar de chaves ordenadas.
Não é automaticamente melhor: usa hash, tem custo de memória e pior caso ruim.

## Set e multiset: somente valores

```cpp
set<int> unicos;
unicos.insert(3);
unicos.insert(3); // continua com um elemento
bool existe = unicos.count(3) > 0;
unicos.erase(3);

multiset<int> repetidos = {3, 3, 8};
auto it = repetidos.find(3);
if (it != repetidos.end()) repetidos.erase(it); // agora {3,8}
repetidos.erase(3); // remove TODOS os 3 restantes; agora {8}
```

Essas estruturas não têm acesso por índice. `*s.begin()` lê o menor,
somente se não vazio. `s.lower_bound(x)` aponta para o primeiro >= x:
confira se o resultado é diferente de end antes de usar `*it`.

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
