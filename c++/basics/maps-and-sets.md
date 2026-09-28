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

## Custos para N elementos

| Operação | map / set / multiset | unordered_map |
|---|---|---|
| Inserir / buscar | O(log N) | O(1) médio, O(N) pior caso |
| Remover por chave | O(log N); multiset soma custo das ocorrências removidas | O(1) médio, O(N) pior caso |
| Percorrer tudo | O(N), ordenado | O(N), sem ordem de classificação |
| count(x) | map/set: O(log N); multiset: O(log N + ocorrências) | O(1) médio |

Chaves longas também custam para comparar/calcular hash. Para frequências de
valores pequenos de 0 até M, um vector<int>(M+1) pode ser mais simples.
