# Fila, pilha, deque ou heap?

[Consulta geral](../../README.md) · [Stack](#stack) · [Queue](#queue) ·
[Deque](#deque) · [Max-heap](#max-heap) · [Min-heap](#min-heap) · [Mediana](#median)

Recortes dentro de `main()`, com o [template](../template.cpp).
Antes de ler/remover uma ponta ou topo, garanta `!empty()`.
`pop()` remove, mas não retorna o valor: leia antes se precisar dele.

<a id="stack"></a>

## Stack — último entra, primeiro sai

**Use quando:** Resolvo primeiro a última pendência aberta; Preciso desfazer a última operação / fechar delimitadores.

**Precisa:** não vazio antes de top/pop; pop não retorna o elemento.

### Template / operações

<!-- example: stack -->
```cpp
stack<char> s;
s.push('('); s.push('[');
cout << s.top(); // [
s.pop();
cout << ' ' << s.top(); // (
```

### Complexidade

Push/pop/top O(1) com deque padrão; memória O(N).

### Não confundir com

Queue retira o mais antigo. Monotonic stack usa a mesma pilha, mas descarta
candidatos para manter uma ordem de valores; veja [o padrão](../algorithms/patterns.md#monotonic-stack).
Vector também funciona como pilha com `push_back/pop_back/back`.
[Delimitadores: stack.cpp](stack.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Guarda pendências em uma pilha. A única que você vê diretamente é a do topo,
a mais recente: ordem LIFO.

### Exemplo de contest

Abriu '(' e depois '['. O próximo fechamento deve ser ']', não ')'.
Ao retirar '[', '(' volta a ser a última pendência.

</details>

<a id="queue"></a>

## Queue — primeiro entra, primeiro sai

**Use quando:** Atender na ordem de chegada; Processar itens pendentes do mais antigo para o mais novo.

**Precisa:** não vazio antes de front/pop; pop não retorna o elemento.

### Template / operações

<!-- example: queue -->
```cpp
queue<string> fila;
fila.push("Ana"); fila.push("Bia");
cout << fila.front(); fila.pop();
cout << ' ' << fila.front(); // Ana Bia
```

### Complexidade

Push/pop/front O(1) com deque padrão; memória O(N).

### Não confundir com

Priority_queue atende por prioridade, não chegada. Não use vector + erase(begin())
repetidamente para simular fila: cada remoção desloca O(N).
[Aplicação: queue.cpp](queue.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Insere no fim e retira da frente. Quem chegou antes é atendido antes: FIFO.
Não reorganiza por prioridade.

### Exemplo de contest

Chegam Ana e Bia. Atende Ana; depois a frente passa a ser Bia.

</details>

<a id="deque"></a>

## Deque — mexer nas duas pontas

**Use quando:** Posso colocar/retirar pelo começo ou pelo fim; Preciso das duas extremidades sem deslocar a sequência inteira.

**Precisa:** não vazio antes de ler/remover pontas; índice válido.

### Template / operações

<!-- example: deque -->
```cpp
deque<int> d{2};
d.push_front(1); d.push_back(3);
cout << d.front() << ' ' << d.back(); // 1 3
d.pop_front(); d.pop_back();
cout << ' ' << d[0]; // 2
```

### Complexidade

Pontas e índice O(1); inserir/remover no meio O(N); memória O(N).
Não reutilize iteradores antigos após mutações sem conferir a validade.

### Não confundir com

Deque comum não mantém mínimo/máximo. Para máximo de cada janela, precisa
da regra da [monotonic deque](../algorithms/patterns.md#monotonic-deque).
Não garante memória contígua como vector; deque Python tem acesso ao meio O(N).
[Aplicação: deque.cpp](deque.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

É uma sequência com inserção/remoção eficiente nas duas pontas.
Em C++, também acessa índices, mas não deixa o meio rápido para inserir/remover.

### Exemplo de contest

Fila [2]. Entra 1 pela frente e 3 pelo fim → [1,2,3].
Retirar as duas pontas deixa [2].

</details>

<a id="max-heap"></a>

## Priority_queue — max-heap

**Use quando:** Novos itens chegam e sempre retiro o maior disponível; Preciso da maior prioridade escolhida até agora.

**Precisa:** não vazio antes de top/pop; só retira o topo.

### Template / operações

<!-- example: max-heap -->
```cpp
priority_queue<int> h; // maior por padrão
for (int x : {5, 2, 9}) h.push(x);
cout << h.top(); h.pop();
cout << ' ' << h.top(); // 9 5
```

### Complexidade

Top O(1); push/pop O(log N); memória O(N).

### Não confundir com

Min-heap retira o menor. Set/multiset permitem apagar um item específico e usar
bounds; heap não tem `erase(x)`, `find`, `begin` nem `lower_bound`.
Se todos os dados são fixos e só quer listar em ordem, sort é mais simples.
[Aplicação: priority-queue.cpp](priority-queue.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Deixa o maior no topo. O restante não fica disponível como uma lista ordenada;
o acesso direto é só ao topo.

### Exemplo de contest

Prioridades 5,2,9: retira 9; o próximo topo é 5, mesmo que 5 tenha chegado antes.

</details>

<a id="min-heap"></a>

## Priority_queue — min-heap

**Use quando:** Preciso retirar repetidamente o menor escolhido; Quando a escolha fica inválida, descarto o valor mais prejudicial.

**Precisa:** não vazio antes de top/pop; use greater no tipo.

### Template / operações

<!-- example: min-heap -->
```cpp
priority_queue<int, vector<int>, greater<int>> h;
for (int x : {5, 2, 9}) h.push(x);
cout << h.top(); h.pop();
cout << ' ' << h.top(); // 2 5
```

Para acumular contribuições grandes, use `long long` na soma e no tipo dos itens.

### Complexidade

Top O(1); push/pop O(log N); memória O(N).

### Não confundir com

Ter o menor acessível não prova uma solução greedy: justifique por que retirá-lo
é a melhor correção. Se também sai um valor arbitrário, considere multiset.
Remoção preguiçosa em heap exige controle de entradas inválidas; não vem pronta.
[Aplicação: priority-queue.cpp](priority-queue.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Com `greater`, a menor prioridade vai ao topo. Bom quando retirar o pior significa
retirar o menor valor, como uma contribuição muito negativa.

### Exemplo de contest

Escolhidos 4,-4,1 têm soma 1. Entra -3 → soma -2.
Retirar -4 recupera mais soma que retirar -3: -2 - (-4) = 2.

</details>

<a id="median"></a>

## Dois multisets — mediana dinâmica

**Use quando:** Entra um, sai um, e preciso da mediana da janela atual; Preciso do meio, não só do mínimo/máximo.

**Precisa:** manter ordem e tamanhos dos lados; abaixo é só inserção, não solução completa.

### Template / operações

Recorte só de inserção, partindo de uma divisão válida — não é solução completa:

<!-- example: median -->
```cpp
multiset<int> baixo{1, 3}, alto{5, 8};
baixo.insert(2);
alto.insert(*baixo.rbegin()); baixo.erase(prev(baixo.end()));
if (baixo.size() < alto.size()) {
    baixo.insert(*alto.begin());
    alto.erase(alto.begin());
}
cout << *baixo.rbegin(); // 3
```

Inserir em baixo e mover seu maior para alto preserva a ordem dos lados.
Na remoção, use `find` + `erase(it)` e mova extremos até recuperar os tamanhos.
Consulte só com M > 0 e após rebalancear. Para M par, confira se pedem mediana
inferior ou média (some em long long, divida por 2.0).

### Complexidade

Inserir/remover/rebalancear O(log M); consultar mediana O(1); memória O(M).
N janelas de tamanho K: O(N log K), com custo constante para K=1.

### Não confundir com

Um multiset ordena, mas avançar de begin ao meio anda O(M), não O(log M).
Dois heaps também podem servir, porém apagar o item que sai exige tratamento extra.
Estatísticas de ordem são outra opção, ainda sem implementação nesta biblioteca.
[Operações de multiset](../basics/multiset.cpp).

<details>
<summary>Entender melhor: ideia e exemplo</summary>

### Ideia simples

Divida os M itens entre `baixo` e `alto`: tudo de baixo <= tudo de alto.
Mantenha `(M+1)/2` itens em baixo e `M/2` em alto (divisão inteira). A mediana inferior é o maior
de baixo. Após inserir/remover, mova extremos para recuperar esses tamanhos.

### Exemplo de contest

[1,3,5,8] → baixo={1,3}, alto={5,8}, mediana inferior=3.
Entra 2 → baixo={1,2,3}, alto={5,8}; mediana continua 3.
Se sai um 3, apague só uma cópia no lado que o contém e rebalanceie.

</details>
