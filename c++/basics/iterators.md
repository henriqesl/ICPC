# Iteradores: posição, valor ou índice?

[Mapa](../../MAPA-DE-RESOLUCAO.md) · [Estruturas](collections.md) ·
[Exemplo executável](iterators.cpp) · [Sort e índices](../algorithms/sorting.md)

## Quando pensar nisso?

- “Find/lower_bound me devolveu um `it`. Como leio o resultado?”
- “Como passo um trecho para sort ou apago o elemento encontrado?”
- “Quero percorrer um set/map, que não tem índice.”

## Ideia simples

Iterador é um **cursor para uma posição** da estrutura. Não é o valor nem,
necessariamente, um índice numérico. Os algoritmos usam esses cursores para
percorrer trechos; a estrutura determina quais movimentos são permitidos.
`auto` apenas deixa o compilador descobrir o tipo do iterador.

## Exemplo: v = [10,20,30]

```text
posição:   0      1      2      3
valor:    10     20     30     não existe
          begin()             end()
```

`end()` é o limite **depois** do último, não o último elemento.
`begin() == end()` significa vazio. `rbegin()` começa pelo último;
`rend()` é o limite da travessia reversa, também não pode ser lido.

## Operações que preciso lembrar

| Expressão | Significado | Cuidado |
|---|---|---|
| `auto it = v.begin()` | cursor no primeiro | em vazio, é end |
| `v.cbegin()` / `v.cend()` | cursores de leitura | não permitem alterar o elemento por *it |
| `*it` | lê o elemento naquela posição | só se apontar para elemento válido |
| `++it` | avança para o próximo | não avance end |
| `--it` | volta um elemento | não volte de begin; hash não suporta |
| `it != v.end()` | ainda há elemento para ler | verifica fim, não corrige iterador invalidado |
| `it->first`, `it->second` | campos de um pair | mesmo que `(*it).first/second` |
| `it - v.begin()` | índice no vector | não funciona em set/map |
| `next(it,K)` / `advance(it,K)` | avança K posições | next retorna outro; advance modifica it; custo depende da estrutura |
| `prev(v.end())` | iterador no último | só se não vazio e permitir voltar |

Não misture cursores de containers diferentes, como `v.begin()` e `w.end()`.
O intervalo e o end usado na comparação precisam corresponder à mesma estrutura.

Recortes independentes, dentro de `main()`, com o [template](../template.cpp).
`next/prev/advance/distance` vêm de `<iterator>`.

### 1. `it` é a posição; `*it` é o valor

<!-- example: iterator-read -->
```cpp
vector<int> v{10, 20, 30};
auto it = v.begin();
cout << *it; ++it; cout << ' ' << *it; // 10 20
*it = 7; // altera v[1], não muda a posição do cursor
cout << ' ' << v[1]; // 7
```

### 2. Percorrer sem usar índices

<!-- example: iterator-loop -->
```cpp
vector<int> v{10, 20, 30};
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << ' '; // 10 20 30
}
```

Só precisa ler? `for (int x : v)` é mais simples.
Quer alterar cada valor? `for (auto& x : v)` usa referência;
`for (auto x : v)` copia o elemento e alterar x não altera v.

### 3. Find/bounds: ler valor e obter índice no vector

<!-- example: iterator-find -->
```cpp
vector<int> v{8, 3, 5};
auto it = find(v.begin(), v.end(), 3);
if (it != v.end()) cout << *it << ' ' << (it - v.begin()); // valor 3, índice 1
it = find(v.begin(), v.end(), 99);
if (it == v.end()) cout << " ausente";
```

Lower/upper_bound retornam o mesmo tipo de resultado, mas exigem ordem compatível.
No vector, end - begin é size(): índice de inserção válido, **não** posição para ler.
Veja [lower_bound](../algorithms/patterns.md#lower-bound).

### 4. Set: há iterador, mas não `it - begin()`

<!-- example: iterator-set -->
```cpp
set<int> s{1, 4, 5, 9};
auto it = s.lower_bound(3);
if (it != s.end()) cout << *it; // 4
if (!s.empty()) cout << ' ' << *s.rbegin(); // 9
cout << ' ' << distance(s.begin(), it); // 1 item antes; percorre, não é O(1)
```

Não existe `s[1]`, `it + 1` ou `it - s.begin()` em set/multiset/map.
Use `++it` para o próximo. `distance` conta passos: ir ao meio de multiset é O(N),
mesmo que encontrar um valor com find seja O(log N).
As chaves não podem ser alteradas por `*it = X`: remova e insira a nova chave.

### 5. Map: o elemento é um pair(chave,informação)

<!-- example: iterator-map -->
```cpp
map<string, int> idade{{"Ana", 20}, {"Bia", 21}};
auto it = idade.find("Ana");
if (it != idade.end()) {
    it->second++; // altera informação, não a chave
    cout << it->first << ':' << it->second; // Ana:21
}
```

`it->first` é a chave, que não pode ser modificada; `it->second` pode ser alterado.
Em vector de pair, a mesma sintaxe funciona, mas os dois campos são modificáveis.
Não leia `it->...` se find retornou end.

### 6. Saltos e intervalo [início,fim)

<!-- example: iterator-range -->
```cpp
vector<int> v{10, 20, 30};
auto it = next(v.begin(), 2);
cout << *it << ' ' << *prev(v.end()); // 30 30
cout << ' ' << distance(v.begin(), v.end()); // 3
```

Em vector, `v.begin()+2` também funciona em O(1).
`advance(it,2)` modificaria it; `next(it,2)` retorna outro cursor.
Não avance além de end nem recue antes de begin. Em hash, next avança;
prev não funciona, pois esses iteradores não voltam.
Sort/find/bounds recebem [início,fim): incluem início, excluem fim.
[Ordenar posições L até R](../algorithms/sorting.md#range).

### 7. Apagar durante a travessia

`erase(it)` invalida o cursor apagado. Em vector/set/multiset/map, o retorno
aponta para o próximo: use-o, sem incrementar de novo naquele passo.

<!-- example: iterator-erase -->
```cpp
set<int> s{1, 2, 3, 4};
for (auto it = s.begin(); it != s.end(); ) {
    if (*it % 2 == 0) it = s.erase(it);
    else ++it;
}
for (int x : s) cout << x << ' '; // 1 3
```

No vector, o mesmo padrão funciona, mas muitas remoções deslocam elementos e
podem custar O(N²). Para remover em lote, prefira
[erase + remove/remove_if](vector.cpp), O(N).
Não apague o elemento atual num range-for e continue usando seu iterador escondido.

## Complexidade e diferenças entre estruturas

| Estrutura | Avançar `++` | Voltar `--` | `it+K` / diferença | `distance/next` por K posições |
|---|---|---|---|---|
| vector / array / string / deque C++ | sim | sim | sim, O(1) | O(1) |
| set / multiset / map | sim | sim | não | O(K) |
| unordered_set / unordered_map | sim | não | não | O(K), só para frente |
| stack / queue / priority_queue | sem begin/end | — | — | use top/front/pop |

Hash não percorre em ordem numérica; `begin()` não significa menor.
Nos conjuntos/mapas crescentes, begin/rbegin dão extremos por valor/chave.
`sort` não aceita iteradores de set/map/hash.

## Não confundir com: iterador válido × mesmo valor

Após sort, um iterador de vector continua válido para aquela posição,
mas pode passar a ler outro valor. Ele não acompanha o item que foi deslocado!

<!-- example: iterator-after-sort -->
```cpp
vector<int> v{30, 10, 20};
auto it = v.begin(); // aqui lê 30
sort(v.begin(), v.end()); // agora [10,20,30], sem mudar o tamanho
cout << *it; // 10: mesma posição, outro valor
```

Para acompanhar identidade, carregue um id/índice original com o item ou
[ordene só uma lista de índices](../algorithms/sorting.md#indices).

### Quando o iterador pode deixar de ser válido?

| Mudança | Cuidado |
|---|---|
| Vector realoca memória ao crescer | invalida todos os iteradores antigos; até push_back pode fazer isso |
| Vector apaga/insere no meio | invalida os cursores na posição afetada e depois; inserção pode realocar tudo |
| Set/multiset/map insere | cursores existentes continuam válidos |
| Set/multiset/map apaga | invalida só os cursores dos itens apagados |
| Hash faz rehash (inclusive ao inserir) | invalida iteradores; obtenha-os novamente |
| Deque muda | validade depende da operação; regra segura: obtenha o cursor novamente |

Mesmo sem realocação, `push_back` no vector muda o end antigo.
Regra prática: depois de modificar a estrutura, não reutilize um cursor antigo
sem saber se ainda vale. Comparar um iterador invalidado com end também não é seguro.
Nunca leia `*end()`, faça `++end()`, `--begin()` ou `prev(begin())`.
