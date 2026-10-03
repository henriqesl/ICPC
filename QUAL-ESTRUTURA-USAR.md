# QUAL ESTRUTURA USAR?

[Índice](README.md) · [Mapa de resolução](MAPA-DE-RESOLUCAO.md) · [Operações da STL](c++/basics/collections.md)

**Qual operação vou repetir? → Qual estrutura faz isso sem percorrer tudo?**
Leia a tabela, abra o caso e confira a limitação antes de copiar código.
N é o número de itens guardados; K é o tamanho da janela. Custos assumem
comparações e hash de chaves pequenas, como `int`.

## Procure pela operação

| Preciso... | Candidata | Caso |
|---|---|---|
| Acessar por índice | vector / array | [01](#op01) |
| Saber se um valor existe | unordered_set / set | [02](#op02) |
| Contar frequências | vector / unordered_map / map | [03](#op03) |
| Manter valores únicos | set / unordered_set | [04](#op04) |
| Manter valores ordenados dinamicamente | set / multiset | [05](#op05) |
| Inserir/remover e continuar ordenado | multiset / set | [06](#op06) |
| Encontrar o primeiro >= x | lower_bound | [07](#op07) |
| Encontrar o primeiro > x | upper_bound | [08](#op08) |
| Pegar repetidamente menor/maior | min-heap / max-heap | [09](#op09) |
| Remover um valor arbitrário | multiset / set / hash | [10](#op10) |
| Processar por chegada | queue | [11](#op11) |
| Processar o último inserido | stack | [12](#op12) |
| Mexer nas duas pontas | deque | [13](#op13) |
| Testar existência em [L,R] | set + lower_bound | [14](#op14) |
| Manter os K itens de uma janela | depende da consulta: soma, mapa, multiset... | [15](#op15) |
| Consultar mediana dinâmica | dois multisets | [16](#op16) |
| Achar próximo menor/maior à esquerda/direita | monotonic stack | [17](#op17) |
| Somar intervalos sem alterações | prefix sum | [18](#op18) |
| Intercalar atualizações e consultas | Fenwick / segment tree | [19](#op19) |
| Ordenar uma vez e só consultar | vector + sort + bounds | [20](#op20) |

## Comparação curta

"Ordenada" abaixo significa **por valor/chave**, não ordem de chegada.
A busca é por valor/chave; não confunda `map[chave]` com acesso por posição.

| Estrutura | Ordenada? | Duplicatas? | Índice? | Busca | Inserir | Remover | Melhor uso |
|---|---|---|---|---|---|---|---|
| vector | só se ordenar | sim | O(1) | O(N); ordenado: O(log N) | fim: O(1) amort.; meio: O(N) | fim: O(1); meio: O(N) | sequência/indexação |
| array | só se ordenar | sim | O(1) | O(N); ordenado: O(log N) | tamanho fixo | tamanho fixo | tamanho conhecido ao compilar |
| set | sim | não | não | O(log N) | O(log N) | por chave: O(log N) | únicos + vizinhos |
| multiset | sim | sim | não | O(log N) | O(log N) | uma cópia: O(log N)¹ | ordem + repetidos |
| unordered_set | não | não | não | O(1) médio | O(1) médio | O(1) médio | presença |
| map | por chave | chave única | não | O(log N) | O(log N) | O(log N) | chave → dado em ordem |
| unordered_map | não | chave única | não | O(1) médio | O(1) médio | O(1) médio | frequência/associação |
| priority_queue | só topo extremo | sim | não | arbitrária: sem API | O(log N) | só topo: O(log N) | retirar menor/maior |
| stack / queue | não | sim | não | sem API | O(1)² | topo/frente: O(1)² | LIFO / FIFO |
| deque | não | sim | O(1) | O(N) | pontas: O(1); meio: O(N) | pontas: O(1); meio: O(N) | duas pontas |

Hash: O(N) no pior caso por operação. ¹Multiset: `find` + `erase(it)` custa
O(log N); `erase(x)` apaga TODAS as C cópias em O(log N + C).
²Custos com os containers padrão: stack usa deque; queue usa deque.
`pair` não é um container: só junta dois campos, como valor e índice.
[Regras dos containers associativos no padrão C++](https://eel.is/c++draft/associative.reqmts).

## Casos rápidos — C++17

Os recortes abaixo vão **dentro de `main()`**, com os includes do
[template GCC C++17](c++/template.cpp) e `using namespace std;`.
Cada recorte é independente e usa valores pequenos de exemplo; adapte a entrada.
`end()` é ausência, nunca um elemento. Antes de `front`, `back`, `top`,
`pop` ou `*begin()`, garanta que a estrutura não está vazia.

<a id="op01"></a>

### 01. Acessar um elemento por índice

**Use vector** para tamanho definido na execução; **array** para tamanho fixo
conhecido ao compilar. Acesso O(1), memória O(N); `push_back` de vector é O(1)
amortizado. Não use para retirar frequentemente do meio: desloca O(N).
Alternativa: deque para índice + operações nas pontas.
**Reconheça:** “Preciso ler/alterar a posição i, não procurar a chave i.”

```cpp
vector<int> v(5, 0); // cinco posições já existem; reserve não faz isso
v[2] = 7;
array<int, 3> fixo{4, 5, 6}; // tamanho 3 faz parte do tipo
cout << v[2] << ' ' << fixo[0]; // 7 4
```

[Arquivo: vector.cpp](c++/basics/vector.cpp).

<a id="op02"></a>

### 02. Saber se um valor existe

**Use unordered_set** se não precisa de ordem: busca/inserção/remoção O(1) médio,
O(N) pior caso. Funciona bem com muitas consultas de presença. Não guarda frequência
nem encontra vizinhos. Alternativa: set, O(log N), ou busca linear para poucas consultas.
**Reconheça:** “Só quero responder se x está entre os valores.”

```cpp
unordered_set<int> presentes{3, 8};
presentes.insert(5);
cout << (presentes.find(5) != presentes.end()); // 1
presentes.erase(8); // ausente também seria permitido
```

[Referência: conjuntos](c++/basics/maps-and-sets.md).

<a id="op03"></a>

### 03. Contar frequência de valores

**Use unordered_map** para chaves esparsas sem ordem: atualização/consulta O(1)
médio, O(N) pior caso. **Map** dá O(log N) e percorre chaves em ordem.
Não use set: perde contagens. Alternativa: vector de contagens, O(1), se as chaves
cabem num domínio pequeno; não aloque até 10^9 só para contar poucos valores.
**Reconheça:** “Preciso saber quantas cópias de x estão presentes.”

```cpp
unordered_map<int, int> freq;
for (int x : {3, 3, 8}) freq[x]++; // [] cria contagem zero se ausente
auto it = freq.find(7); // consulta sem criar a chave 7
cout << (it == freq.end() ? 0 : it->second); // 0
```

[Arquivos: map.cpp](c++/basics/map.cpp), [unordered-map.cpp](c++/basics/unordered-map.cpp).

<a id="op04"></a>

### 04. Manter só valores únicos

**Use set** se também quer ordem: inserir/buscar/remover O(log N), `size()` O(1).
Funciona para distintos dinâmicos; não preserva quantidades nem sequência original.
Alternativa: unordered_set sem ordem; vector + sort + unique para dados fixos.
**Reconheça:** “Repetir x não deve aumentar a quantidade guardada.”

```cpp
set<int> distintos{3, 1, 3};
distintos.insert(8);
cout << distintos.size() << '\n'; // 3
for (int x : distintos) cout << x << ' '; // 1 3 8
```

[Arquivo: set.cpp](c++/basics/set.cpp).

<a id="op05"></a>

### 05. Manter valores ordenados dinamicamente

**Use set ou multiset**: busca/inserção O(log N); consultar extremos O(1).
Use multiset se cópias importam. Bom para ordem/vizinhos com novas entradas.
Não use para “o item de índice i”: avançar i posições é O(i).
Alternativa: vector ordenado para dados que não mudam.
**Reconheça:** “Chegam novos valores, mas preciso dos extremos/vizinhos agora.”

```cpp
multiset<int> s{5, 2, 5}; // duas cópias de 5
s.insert(1);
if (!s.empty()) cout << *s.begin() << ' ' << *s.rbegin(); // 1 5
// end() fica depois do último; rbegin() aponta para o último
```

[Arquivo: multiset.cpp](c++/basics/multiset.cpp).

<a id="op06"></a>

### 06. Inserir/remover e continuar ordenado

**Use multiset**: inserir O(log N), encontrar + apagar uma cópia O(log N).
Bom quando os dados mudam e é preciso manter vizinhos/extremos. Não trate
`erase(x)` como “apagar um”: ele apaga todas as cópias.
Alternativa: set sem repetidos; vector ordenado tem inserção/remoção O(N).
**Reconheça:** “Depois de tirar um valor, ainda preciso consultar a ordem.”

```cpp
multiset<int> s{1, 3, 3, 8};
s.insert(5);
auto it = s.find(3);
if (it != s.end()) s.erase(it); // fica uma cópia de 3
for (int x : s) cout << x << ' '; // 1 3 5 8
```

[Guia: remoção e duplicatas](c++/basics/maps-and-sets.md).

<a id="op07"></a>

### 07. lower_bound — encontrar o primeiro valor >= x

**Use lower_bound**: O(log N) no vector ordenado ou em `s.lower_bound(x)`.
Bom para saltar ao primeiro candidato, inclusive x. Não use no vector desordenado
nem a versão genérica com iteradores de set: pode percorrer O(N).
Alternativa: busca linear se há poucas consultas; set se os dados mudam.
**Reconheça:** “Quero o menor valor que já atinge x.”

```cpp
vector<int> v{1, 3, 3, 8}; // já ordenado
auto it = lower_bound(v.begin(), v.end(), 3);
if (it != v.end()) cout << *it << ' ' << (it - v.begin()); // 3 1
// set/multiset: s.lower_bound(3), sem índice por subtração
```

[Arquivo: bounds.cpp](c++/algorithms/bounds.cpp).

<a id="op08"></a>

### 08. upper_bound — encontrar o primeiro valor > x

**Use upper_bound**: O(log N) em vector ordenado ou no método de set/multiset.
Bom para pular todas as cópias de x. Não use se x também é aceito: aí é lower_bound.
Alternativa: varrer se poucos dados/consultas; usar bounds no conjunto dinâmico.
**Reconheça:** “Preciso passar de x, não apenas chegar nele.”

```cpp
vector<int> v{1, 3, 3, 8};
auto it = upper_bound(v.begin(), v.end(), 3);
if (it != v.end()) cout << *it; // 8
// upper - lower conta cópias em vector; em multiset, distance é linear
```

[Arquivo: bounds.cpp](c++/algorithms/bounds.cpp).

<a id="op09"></a>

### 09. Pegar repetidamente o menor ou maior

**Use priority_queue**: max-heap por padrão; `greater` cria min-heap.
`top()` O(1), `push/pop` O(log N). Bom com inserções entre retiradas.
Não tem busca/remoção arbitrária nem percurso ordenado sem consumir o heap.
Alternativa: multiset para remoção arbitrária; sort se só vai listar dados fixos.
**Reconheça:** “Preciso retirar a menor/maior prioridade disponível agora.”

```cpp
priority_queue<int> maior;
priority_queue<int, vector<int>, greater<int>> menor;
for (int x : {5, 2, 9}) { maior.push(x); menor.push(x); }
cout << maior.top() << ' ' << menor.top(); // 9 2
maior.pop(); menor.pop(); // pop remove, não retorna o valor
```

[Arquivo: priority-queue.cpp](c++/data-structures/priority-queue.cpp).

<a id="op10"></a>

### 10. Remover um valor arbitrário já inserido

**Use multiset** para remover uma cópia e manter ordem: `find` + `erase(it)`
O(log N). Não use heap puro: só remove o topo. Se a identidade importa,
guarde `(valor,id)` em set, não só o valor.
Alternativa: unordered_set/unordered_map sem ordem; vector para poucas remoções.
**Reconheça:** “Sai este valor específico, não necessariamente o menor.”

```cpp
multiset<int> escolhidos{2, 5, 5, 9};
int sai = 5;
auto it = escolhidos.find(sai);
if (it != escolhidos.end()) escolhidos.erase(it);
cout << escolhidos.size(); // 3: um dos 5 continua
```

[Arquivo: multiset.cpp](c++/basics/multiset.cpp).

<a id="op11"></a>

### 11. Processar em ordem de chegada

**Use queue (FIFO)**: `push`, `front`, `pop` O(1) com deque padrão.
Bom quando o mais antigo sai primeiro. Não use se a regra é maior prioridade
ou se precisa acessar o meio. Alternativa: deque para duas pontas; heap para prioridade.
**Reconheça:** “Quem entrou antes deve sair antes.”

```cpp
queue<string> fila;
fila.push("Ana"); fila.push("Bia");
cout << fila.front(); // Ana
fila.pop(); // agora Bia é a primeira
```

[Arquivo: queue.cpp](c++/data-structures/queue.cpp).

<a id="op12"></a>

### 12. Processar o último inserido

**Use stack (LIFO)**: `push`, `top`, `pop` O(1) com deque padrão.
Bom para desfazer e resolver a última abertura pendente. Não use para atender
o mais antigo. Alternativa: vector como pilha; queue para chegada.
**Reconheça:** “A última pendência aberta é a primeira que preciso fechar.”

```cpp
stack<char> pendentes;
pendentes.push('('); pendentes.push('[');
cout << pendentes.top(); // [
pendentes.pop(); // ( volta ao topo
```

[Arquivo: stack.cpp](c++/data-structures/stack.cpp).

<a id="op13"></a>

### 13. Inserir/remover nas duas pontas

**Use deque**: operações nas pontas e acesso por índice O(1) em C++.
Bom quando ambas as extremidades importam. Não torna inserção/remoção no meio
rápida: O(N). Alternativa: queue/stack para uma regra só; vector se só cresce no fim.
**Reconheça:** “Preciso mexer no começo e no fim sem deslocar todo mundo.”

```cpp
deque<int> d{2};
d.push_front(1); d.push_back(3);
cout << d.front() << ' ' << d.back(); // 1 3
d.pop_front(); d.pop_back(); // sobra 2
```

[Arquivo: deque.cpp](c++/data-structures/deque.cpp).

<a id="op14"></a>

### 14. Saber se existe algum valor dentro de [L,R]

**Use set + lower_bound(L)**, O(log N). Funciona com valores/posições ativos
dinâmicos: se o primeiro >= L passou de R, não existe nenhum dentro.
Não confunda com soma ou quantidade: contar iteradores do set pode ser O(N).
Alternativa: vector ordenado + bounds se fixo; prefixos de 0/1 se domínio fixo e pequeno.
**Reconheça:** “Só preciso de um ativo no intervalo, não visitar todos.”

```cpp
set<int> ativos{2, 8, 1000000};
int l = 5, r = 9; // l <= r
auto it = ativos.lower_bound(l);
bool existe = it != ativos.end() && *it <= r;
cout << existe; // 1, por causa do 8
```

[Arquivo: bounds.cpp](c++/algorithms/bounds.cpp) para consultas em ordem.

<a id="op15"></a>

### 15. Manter os K elementos de uma sliding window

**Escolha o estado pela consulta**: soma → acumulador O(1) por avanço;
frequências → mapa O(1) médio; ordem/remoção → multiset O(log K).
Bom quando sai o mais antigo e entra o próximo. Não reordene a entrada: destrói as
janelas. Alternativa: prefix sum para somas fixas; deque monotônica para min/max em O(N).
**Reconheça:** “O trecho muda só retirando um da esquerda e incluindo outro à direita.”

```cpp
vector<int> v{2, 1, 5, 1}; int k = 3; // 1 <= k <= v.size()
long long soma = accumulate(v.begin(), v.begin() + k, 0LL);
cout << soma << ' '; // 8: primeira janela
for (int r = k; r < int(v.size()); r++) {
    soma += v[r]; soma -= v[r-k]; cout << soma << ' '; // 7
}
```

[Soma: janela fixa](c++/algorithms/sliding-window-fixed.cpp),
[frequências: até K distintos](c++/algorithms/sliding-window-distinct.cpp).
Janela variável usa **two pointers** que avançam; o critério precisa permitir
descartar a esquerda com segurança. Para soma <= limite, a
[versão existente](c++/algorithms/sliding-window-variable.cpp) exige não negativos.
Dois ponteiros também podem buscar um par, não um trecho:
[two-pointers.cpp](c++/algorithms/two-pointers.cpp) usa vetor ordenado, O(N).

<a id="op16"></a>

### 16. Achar mediana dinamicamente

**Use dois multisets**: menores em `baixo`, maiores em `alto`.
Mantenha todos de baixo <= todos de alto e tamanhos ceil(M/2), floor(M/2),
com M itens atuais. Inserir/remover/rebalancear O(log M); mediana inferior O(1)
em `*baixo.rbegin()`. Não avance ao meio de um único multiset: O(M).
Alternativa: estrutura com estatísticas de ordem (não disponível na biblioteca).
**Reconheça:** “Entra um, sai outro, e eu preciso do meio depois de cada mudança.”

Recorte **só da inserção**, partindo de uma divisão válida; não é solução completa:
insira em baixo, mova seu maior para alto para preservar a ordem, e devolva
o menor de alto se baixo ficou com poucos itens.

```cpp
multiset<int> baixo{1, 3}, alto{5, 8};
baixo.insert(2);
alto.insert(*baixo.rbegin()); baixo.erase(prev(baixo.end()));
if (baixo.size() < alto.size()) {
    baixo.insert(*alto.begin()); alto.erase(alto.begin()); }
cout << *baixo.rbegin(); // 3, mediana de 1 2 3 5 8
```

Na retirada, encontre/apague **uma cópia** no lado que a contém; depois mova
extremos entre os lados até recuperar os tamanhos. Só consulte após rebalancear,
com M > 0. Para M par, confira se o enunciado quer a inferior ou a média dos dois
extremos (soma em long long e divisão por 2.0).
[Operações de multiset](c++/basics/multiset.cpp); não há solução completa de mediana aqui.

<a id="op17"></a>

### 17. Próximo menor/maior à esquerda ou direita

**Use monotonic stack de índices**: cada índice entra/sai uma vez, O(N) tempo e
O(N) memória. Bom para o vizinho mais próximo que satisfaz uma comparação,
preservando posições. Não use sort: perde a relação esquerda/direita.
Alternativa: varrer cada lado, O(N²), apenas para N pequeno/testar.
**Reconheça:** “Para cada posição, quero o primeiro menor/maior quando olho para um lado.”

```cpp
vector<int> v{3, 1, 2}, anterior(3, -1); stack<int> st;
for (int i = 0; i < int(v.size()); i++) {
    while (!st.empty() && v[st.top()] >= v[i]) st.pop();
    if (!st.empty()) anterior[i] = st.top();
    st.push(i);
} // anterior: -1 -1 1; são ÍNDICES do menor estrito à esquerda
```

Para menor à direita, percorra de N-1 até 0 com pilha vazia.
Para maior estrito, descarte `<=` em vez de `>=`. Para aceitar iguais,
descarte só `>` (menor ou igual) ou `<` (maior ou igual).
O recorte é a referência da técnica; [stack.cpp](c++/data-structures/stack.cpp)
mostra as operações da pilha, não implementa esses vizinhos.

<a id="op18"></a>

### 18. Responder somas de intervalos

**Use prefix sum** se valores não mudam: construção O(N), consulta O(1),
memória O(N). Funciona inclusive com negativos. Não serve para consultas
de mínimo pela mesma subtração, nem fica correto após alterar o vetor.
Alternativa: Fenwick para somas dinâmicas; janela fixa se só consulta K consecutivos.
**Reconheça:** “Estou somando de novo trechos sobrepostos de dados fixos.”

```cpp
vector<int> v{2, -1, 4}; vector<long long> p(v.size() + 1, 0);
for (int i = 0; i < int(v.size()); i++) p[i+1] = p[i] + v[i];
int l = 1, r = 2; // índices base zero, intervalo inclusivo
cout << p[r+1] - p[l]; // 3
```

[Arquivo: prefix-sum.cpp](c++/algorithms/prefix-sum.cpp).

<a id="op19"></a>

### 19. Fazer muitas atualizações + consultas

**Use Fenwick** para somar incremento numa posição + consultar somas:
O(log N) por operação, O(N) memória. Para substituir valor, use delta = novo - antigo.
**Segment tree** atende também mínimo/máximo com atualização pontual, O(log N).
Não use prefixo estático para consultas intercaladas sem reconstruir.
Alternativa: vetor simples se pequeno; diferenças O(N+Q) se só consulta no final.
**Reconheça:** “O valor mudou, mas a próxima consulta já precisa enxergar a mudança.”

Recorte Fenwick: começa com todos os valores zero; índices **1 até N**:

```cpp
int n = 5; vector<long long> bit(n + 1, 0);
int pos = 3; long long delta = 7; // adicionar 7 na posição 3
for (int i = pos; i <= n; i += i & -i) bit[i] += delta;
int r = 4; long long soma = 0;
for (int i = r; i > 0; i -= i & -i) soma += bit[i];
cout << soma; // soma [1,4] = 7
```

`i & -i` é o menor bit ligado; os saltos visitam os blocos que guardam somas.
Exige 1 <= pos <= N e 0 <= r <= N; pos=0 faria o loop travar.
Soma [L,R] = prefixo(R) - prefixo(L-1), repetindo a consulta acima nos dois limites.
Fenwick/segment tree ainda não têm arquivos completos aqui; este é um recorte
de reconhecimento. [difference-array.cpp](c++/algorithms/difference-array.cpp)
resolve **adições em intervalos com resultado só no final**, não consultas online.

<a id="op20"></a>

### 20. Ordenar uma vez e depois só consultar

**Use vector + sort + bounds**: sort O(N log N), buscas O(log N), índice O(1).
Bom para dados fixos, contagem em [L,R] e vizinhos. Não ordene sem preservar
índices se a saída precisa da posição original; use pair(valor,índice).
Alternativa: set/multiset para mudanças online; dois ponteiros para buscar soma de um par.
**Reconheça:** “Os dados não mudam; posso pagar a ordenação uma única vez.”

```cpp
vector<pair<int, int>> v{{8, 0}, {3, 1}, {3, 2}}; // valor, índice original
sort(v.begin(), v.end()); // compara first e depois second
auto it = lower_bound(v.begin(), v.end(), make_pair(3, -1));
if (it != v.end() && it->first == 3) cout << it->second; // 1
```

O -1 funciona porque os índices originais são >= 0. Para contar valores em
[L,R] num vector de inteiros, use `upper_bound(R) - lower_bound(L)`, O(log N).
[sort](c++/algorithms/sorting.cpp), [pair](c++/data-structures/pair.cpp),
[bounds](c++/algorithms/bounds.cpp), [dois ponteiros](c++/algorithms/two-pointers.cpp).

## NÃO ESCOLHA A ESTRUTURA PELO NOME DO PROBLEMA

| Palavra/pensamento | Pergunta que decide |
|---|---|
| “Intervalo” | Soma fixa → prefixo; existe ativo → set + bound; mínimo com alterações → segment tree. |
| “Menor/maior” | Consultar extremo → heap/set; escolher uma ação ótima → justificar greedy, não só pegar o extremo. |
| “Ordenado” | Dados fixos → sort; chegam/saem itens → set/multiset; só extremo → heap. |
| “Janela” | Qual resposta dentro dela? Soma → acumulador; mediana → dois multisets. Janela não garante algoritmo linear. |
| “Achar valor” | Só presença → set/hash; chave → dado → map/hash; índice i → vector. |

**Vector de 0/1 × set de posições ativas:** se posições vão de 0 até um N pequeno,
vector é simples e testa/atualiza uma posição em O(1). Já “há algum ativo em [L,R]?”
por varredura custa O(R-L+1). Com set, `lower_bound(L)` pula direto para o próximo
ativo em O(log A), com A posições ativas, mesmo se coordenadas forem enormes.
Se os bits são fixos, prefix sum de 0/1 também responde existência em O(1).

**`map<int,int>` só para índice → 0/1:** em domínio pequeno/denso, costuma gastar
mais memória e O(log N) por acesso onde vector faz O(1). Se o domínio é enorme
ou esparso, não aloque um vector gigante; considere set/hash conforme a consulta.

**Heap × multiset:** heap é bom para retirar sempre o extremo, mas não tem
`erase(x)`. Remoção preguiçosa existe, porém exige controle extra e descarte de
entradas antigas. Multiset remove um valor arbitrário e mantém ordem; não oferece
acesso por rank/índice. `advance(it, K)` e `distance` andam K itens, não O(log N).

## Quatro problemas: descreva a operação antes da estrutura

### Sliding Window Median

**Operações:** entra valor → sai o mais antigo → consultar mediana.
**Candidata:** dois multisets com o particionamento do [caso 16](#op16), O(N log K).
Um único multiset mantém ordem, mas ir de begin até o meio a cada janela é O(K),
levando a O(NK). Nos dois, a mediana fica num extremo acessível em O(1).
Apague apenas uma cópia do valor que sai e rebalanceie antes de consultar.
No [enunciado CSES](https://cses.fi/problemset/task/1076), K par pede a mediana inferior.

### Potions

**Operações:** percorrer esquerda → direita, tentar incluir; soma ficou negativa
→ desfazer a pior poção escolhida, a de menor valor (mais negativa).
**Candidata:** min-heap de `long long`, `priority_queue<long long, vector<long long>, greater<long long>>`.
Ao desfazer, subtraia o topo da soma e retire-o; subtrair negativo aumenta a soma.
Custo O(N log N). A escolha é gulosa porque descartar o menor recupera mais saúde
removendo um item e não piora os prefixos anteriores. Não ordene as poções:
a ordem e a saúde dos prefixos importam no [problema original](https://codeforces.com/problemset/problem/1526/C2).
[Operações de heap](c++/data-structures/priority-queue.cpp).

### Laser Tag — posições ativas e parede [x1,x2]

**Operações no cenário descrito:** ativar/desativar x → testar existência no intervalo.
**Candidata:** set + `lower_bound(x1)` e comparar com x2, como no [caso 14](#op14).
Um vector de 0/1 pode testar um x em O(1), mas procurar algum ativo dentro da
parede pode percorrer o intervalo inteiro. Set salta os espaços vazios.
Se vários lasers podem ocupar o mesmo x, preserve contagens: só remova a posição
do set quando o último sair, ou use multiset. Outras regras do enunciado podem
exigir guardar mais que x; esta associação cobre apenas essa consulta.

### Minimum Sum / sum of subarray minimums

**Operações:** para cada posição, achar onde um menor bloqueia a expansão à
esquerda e à direita. **Candidata:** monotonic stack, como no [caso 17](#op17), O(N).
Não procure o mínimo de cada subarray separadamente. Os limites permitem contar
em quantos trechos um elemento é o mínimo: distâncias à esquerda × à direita.
**Empates importam:** para somar contribuições sem duplicar, use menor **estrito**
de um lado e menor **ou igual** do outro (ou o inverso). Em [2,2], usar estrito nos
dois lados atribuiria o trecho inteiro aos dois elementos. Não é uma receita
para qualquer problema chamado Minimum Sum: confirme o objetivo do enunciado.

## CHECKLIST DE 20 SEGUNDOS ANTES DE CODAR

- O que vou repetir muitas vezes? Ordem? Duplicatas? Índice?
- Sai um item arbitrário ou sempre o menor/maior? Ou por chegada?
- Os dados mudam? Posso ordenar sem destruir a ordem original?
- Qual custo cabe para N **e Q**? Há limite para a **soma de N** nos testes?
- Testei vazio, repetidos, ausência e limites? Preciso de `long long`?

## Equivalentes Python já existentes

Presença: [set](python/collections/sets.py); frequências:
[Counter](python/collections/frequency.py); fila/duas pontas:
[deque](python/collections/queue.py); limites ordenados:
[bisect](python/algorithms/README.md#bisect-limite-não-é-presença);
[prefix sum](python/algorithms/prefix_sum.py) e
[janela fixa](python/algorithms/sliding_window_fixed.py).
`set` Python não é ordenado; `bisect` em lista não torna inserção O(log N).
Não há equivalente pronto de dois multisets ordenados nesta trilha Python.
