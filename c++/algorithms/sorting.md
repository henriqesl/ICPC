# Sort: qual parte e qual critério?

[Consulta geral](../../README.md) · [Iteradores: begin/end e *it](../basics/iterators.md) ·
[Exemplo básico](sorting.cpp) · [Variantes executáveis](sorting-variants.cpp)

[Trecho](#range) · [Pair/second](#pairs) · [Coluna](#column) · [Índices](#indices) · [Stable_sort](#stable)

Os snippets são independentes e vão dentro de `main()`, com o [template](../template.cpp).
O comparator responde **“a vem antes de b?”**, não “a é maior?”.

**Custo:** sort O(N log N); muda a sequência. Comparator usa `<`/`>`, nunca `<=`/`>=`.
**Índice original na saída?** Carregue (valor,id) ou ordene só os índices.

## Escolha rápida

| Preciso... | Use |
|---|---|
| Crescente | `sort(v.begin(), v.end())` |
| Decrescente | `sort(v.rbegin(), v.rend())` ou comparator `greater<int>()` |
| Só posições [L,R], inclusivas | `sort(v.begin()+L, v.begin()+R+1)` |
| Guardar posição original junto do valor | vector de pair(valor,índice) |
| Ordenar pela coluna j de cada registro | comparator que usa `a[j]` e `b[j]` |
| Ordenar índices sem modificar os valores | vector de índices + comparator que consulta os valores |
| Manter a ordem original de itens empatados | `stable_sort` com comparação só pela chave desejada |

Sort exige iteradores de acesso aleatório: vector, array, string e deque servem.
Não faça `sort(s.begin(),s.end())` em set/map: seus iteradores não servem para sort;
as chaves já são mantidas em ordem. Hash não tem ordem; copie para vector se precisar ordenar.

<a id="ascending-descending"></a>

## 1. Crescente ou decrescente

<!-- example: sort-directions -->
```cpp
vector<int> v{8, 3, 1};
sort(v.begin(), v.end()); // 1 3 8
sort(v.begin(), v.end(), greater<int>()); // 8 3 1
for (int x : v) cout << x << ' ';
```

`sort(v.rbegin(),v.rend())` também produz decrescente no vetor.
`reverse(v.begin(),v.end())` só inverte o que já existe: não ordena um vetor qualquer.
Ex.: [3,1,8] invertido dá [8,1,3], que não está ordenado.

<a id="range"></a>

## 2. Ordenar só um trecho do vetor

Situação: [9,4,2,3,8], ordenar posições 1 até 3 → [9,2,3,4,8].

<!-- example: sort-range -->
```cpp
vector<int> v{9, 4, 2, 3, 8};
int l = 1, r = 3; // base zero; ambos inclusivos
sort(v.begin() + l, v.begin() + r + 1);
for (int x : v) cout << x << ' '; // 9 2 3 4 8
```

Os algoritmos recebem **[início,fim)**: incluem início, excluem fim.
Por isso usamos R+1. Exige `0 <= L <= R < size()`; o limite final pode ser end,
mas nunca depois dele. Um trecho vazio [L,L) também pode ser passado a sort.
Ordenar M posições custa O(M log M), não necessariamente O(N log N).

<a id="pairs"></a>

## 3. Pair: primeiro campo, depois segundo

Para [8,3,3], carregar o índice gera (8,0), (3,1), (3,2).
Ordenação padrão → (3,1), (3,2), (8,0). O índice original continua junto do valor.

<!-- example: sort-pairs -->
```cpp
vector<int> valores{8, 3, 3}; vector<pair<int,int>> itens;
for (int i = 0; i < int(valores.size()); i++) itens.push_back({valores[i], i});
sort(itens.begin(), itens.end());
for (auto p : itens) cout << p.first << ':' << p.second << ' '; // 3:1 3:2 8:0
```

Para ordenar pelo **second** e desempatar pelo first:

<!-- example: sort-second -->
```cpp
vector<pair<int,int>> v{{10, 2}, {8, 1}, {5, 1}};
sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
});
for (auto p : v) cout << p.first << ':' << p.second << ' '; // 5:1 8:1 10:2
```

Maior first, menor second no empate: troque a primeira comparação por
`a.first > b.first`, depois compare `a.second < b.second`.
[Exemplo de pontuação/id](patterns.md#custom-comparator).

<a id="column"></a>

## 4. Vector de registros: ordenar pela coluna j

Registros [id,nota]: [0,7], [1,9], [2,7].
Maior nota (coluna 1), menor id (coluna 0) no empate → [1,9], [0,7], [2,7].

<!-- example: sort-column -->
```cpp
vector<vector<int>> v{{0, 7}, {1, 9}, {2, 7}};
sort(v.begin(), v.end(), [](const vector<int>& a, const vector<int>& b) {
    if (a[1] != b[1]) return a[1] > b[1]; // coluna 1: nota
    return a[0] < b[0]; // coluna 0: id
});
for (const auto& linha : v) cout << linha[0] << ':' << linha[1] << ' ';
```

Todos os registros precisam ter as colunas acessadas. `const ...&` lê sem copiar
o registro em cada comparação; não é para modificar a ou b.
Sem comparator, vector compara as linhas lexicograficamente, começando pela coluna 0,
**não** pela coluna 1. Com exatamente dois campos, pair costuma ser mais simples.

<a id="indices"></a>

## 5. Ordenar índices, mantendo o vetor original intacto

Valores [8,3,3]. Quer visitar do menor ao maior, mas continuar consultando as
posições originais? Ordene índices [0,1,2] → [1,2,0], sem alterar valores.

<!-- example: sort-indices -->
```cpp
vector<int> valores{8, 3, 3}; vector<int> ordem(valores.size());
iota(ordem.begin(), ordem.end(), 0); // 0 1 2; inclui <numeric>
sort(ordem.begin(), ordem.end(), [&valores](int i, int j) {
    if (valores[i] != valores[j]) return valores[i] < valores[j];
    return i < j; // empate: menor índice original
});
for (int i : ordem) cout << i << ':' << valores[i] << ' '; // 1:3 2:3 0:8
```

Aqui i/j são ÍNDICES; em um sort direto de valores, a/b são VALORES.
`[&valores]` permite à comparação consultar o vetor externo sem copiá-lo.
Não altere valores durante o sort; depois de alterá-los, a lista de índices
pode deixar de estar ordenada pelos valores. Não confunda índice original com rank
(posição depois de ordenar).

<a id="stable"></a>

## 6. Stable_sort: empates continuam na ordem de chegada

Chegam (nota,id): (7,4), (9,1), (7,2). Ordene por nota crescente,
mas mantenha a chegada entre notas iguais → (7,4), (7,2), (9,1).

<!-- example: sort-stable -->
```cpp
vector<pair<int,int>> v{{7, 4}, {9, 1}, {7, 2}};
stable_sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.first < b.first; // empates não comparam id
});
for (auto p : v) cout << p.first << ':' << p.second << ' '; // 7:4 7:2 9:1
```

Adicionar desempate por id mudaria essa regra. Sort normal não garante a ordem
original dos empates. Stable_sort costuma usar memória auxiliar O(N): com ela,
O(N log N) comparações; sem memória suficiente, pode usar O(N log² N).

## 7. Array e string usam o mesmo padrão

<!-- example: sort-array-string -->
```cpp
array<int, 3> a{8, 1, 3}; string texto = "cab";
sort(a.begin(), a.end()); sort(texto.begin(), texto.end());
for (int x : a) cout << x << ' '; // 1 3 8
cout << texto; // abc
```

Array C: `int a[3]{8,1,3}; sort(a,a+3);` também funciona; o fim fica após o último.
String é ordenada por caracteres, não por números representados em texto:
"10" vem antes de "2" numa ordenação lexicográfica de strings.

## Pegadinhas e custo

- Comparator usa `<`/`>`, nunca `<=`/`>=` como desempate. Comparar um item consigo dá false.
- O critério precisa ser coerente: não pode formar ciclos de “vem antes”.
- Sort não mantém cópia da entrada; preserve índices/valores antes se precisar.
- Iteradores de vector continuam indicando posições após sort, não os mesmos valores!
- Busca binária/bounds só funcionam com uma ordem compatível com o comparator.
- Sort: O(N log N) comparações; os exemplos com campos inteiros comparam em O(1).
  Comparar strings/linhas inteiras pode custar mais. Guardar índices/pares usa O(N) extra.
