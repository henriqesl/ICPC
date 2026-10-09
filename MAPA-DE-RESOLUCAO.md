# Do enunciado à técnica

[Consulta direta / códigos](README.md) · [Qual estrutura usar?](QUAL-ESTRUTURA-USAR.md)

## O QUE O ENUNCIADO ESTÁ ME PEDINDO?

**Transforme a história em uma operação.** “Computadores ligando” pode ser divisibilidade;
“clientes” pode ser fila ou prioridade. O tema não escolhe o algoritmo.

| Pergunta que você faz | Pista / próximo passo |
|---|---|
| Quero consultar intervalos fixos ou mover um trecho? | [Prefix sum × janela](c++/algorithms/prefix-and-window.md) |
| Escolho dois elementos ou todos os consecutivos? | [Par × janela](c++/search/two-pointers.md#nao-confundir) |
| Procuro X nos dados ou o menor/maior X viável? | [Busca tradicional × na resposta](c++/search/binary-search.md) |
| Os dados mudam? Preciso ordem, repetidos ou só presença? | [Estruturas por operação](QUAL-ESTRUTURA-USAR.md#procure-pela-operação) |
| Só muda em certos instantes/posições? | [Sweep line](c++/search/sweep-line.md#receita) |
| Poucos valores enormes, mas preciso indexar? | [Compressão](c++/search/sweep-line.md#compression) |
| N é pequeno e preciso testar escolhas/ordens? | [Enumeração](c++/search/exhaustive-search.md) · [backtracking com poda](c++/search/backtracking.md#mapeamento) |
| O estado muda sempre do mesmo jeito? Há pares, ciclos ou paridade? | Faça casos pequenos e procure uma propriedade matemática antes de simular tudo. |

Para localizar o código, use a [tabela principal](README.md#algoritmos-o-que-a-questão-pede).
As pistas levantam hipóteses: confirme as condições do template.

## CHECKLIST DE 20 SEGUNDOS ANTES DE CODAR

1. **Pedido:** em uma frase, o que devo devolver? Índice, valor, quantidade, melhor ou existe?
2. **Trabalho:** qual operação se repete? Dados mudam? Posso ordenar? Repetidos/negativos?
3. **Propriedade:** por que posso descartar opções? Ordem, monotonicidade, evento, paridade?
4. **Custo:** conte N, Q, trabalho por estado e soma dos tamanhos entre casos.
5. **Teste:** um item, repetidos, ausente, extremos, negativo quando permitido. Compare com força bruta pequena.

N~10^5 costuma pedir O(N) ou O(N log N), não O(N²). N~20 pode permitir 2^N.
São estimativas: considere tempo, memória e custo das operações.
Travou? Faça um caso pequeno à mão e escreva a solução direta; procure o trabalho repetido.

## PARECE X, MAS É Y

| Parece... | Mas a operação real muda a escolha |
|---|---|
| “Pego o menor várias vezes” → min-heap | “Também apago um valor específico” → set/multiset, não heap puro. |
| “Já apareceu?” → unordered_set | “Quantas vezes?” → unordered_map ou vetor de frequências. |
| “Quero o menor” → heap ou set/multiset | “Também quero lower_bound” → set/multiset. Heap não tem bounds. |
| “Tudo ordenado” → sort | “Chegam/saem valores durante consultas” → set/multiset. |
| “Intervalo” → prefix sum | Só soma/contagem **fixa** combina com a subtração de prefixos; presença dinâmica pode ser set. |
| “Menor/maior” → greedy | Consultar extremo não prova que escolher esse extremo é ótimo. Justifique a escolha. |

**“Tenho uma janela K” descreve a movimentação, não resolve a consulta.**

| O que quero DENTRO da janela? | Estado que mantenho |
|---|---|
| Soma | variável acumulada: subtrai quem sai, soma quem entra |
| Frequência/distintos | map/unordered_map ou vetor; remova chaves com frequência zero |
| Máximo/mínimo | monotonic deque de índices |
| Mediana | dois multisets, removendo uma cópia e rebalanceando |

Não force um encaixe: sequência de operações, construção, matemática, grafos e DP
podem pedir outro raciocínio. A história e o título não escolhem a estrutura.

<details>
<summary>Entender melhor: tabela completa de operações</summary>

| Se você está pensando... | Operação → padrão/estrutura | Por que serve / custo | Abra |
|---|---|---|---|
| “Preciso da posição i” | índice → vector | O(1), preserva a sequência | [Vector](c++/basics/collections.md#vector) |
| “Sempre são 26 letras / 10 dígitos” | domínio fixo → array | índice O(1), tamanho conhecido ao compilar | [Array](c++/basics/collections.md#array) |
| “Ordenar, mas devolver índice original” | juntar valor + índice → pair | guarda os dois campos | [Pair](c++/basics/collections.md#pair) |
| “Primeiro entra, primeiro sai” | chegada → queue | push/front/pop O(1) | [Queue](c++/data-structures/README.md#queue) |
| “Último entra, primeiro sai” | última pendência → stack | push/top/pop O(1) | [Stack](c++/data-structures/README.md#stack) |
| “Adicionar/remover nas duas pontas” | extremidades → deque | pontas O(1), meio não | [Deque](c++/data-structures/README.md#deque) |
| “Só saber se já apareceu” | presença → unordered_set | find O(1) médio, sem ordem | [Unordered_set](c++/basics/maps-and-sets.md#unordered-set) |
| “Únicos E ordenados; entram e saem” | ordem dinâmica → set | insert/erase/bounds O(log N) | [Set](c++/basics/maps-and-sets.md#set) |
| “Repetidos E ordenados; entram e saem” | ordem + cópias → multiset | uma cópia sai em O(log N) | [Multiset](c++/basics/maps-and-sets.md#multiset) |
| “Chave → informação, em ordem” | associação → map | busca O(log N), chaves ordenadas | [Map](c++/basics/maps-and-sets.md#map) |
| “Chave → informação, ordem não importa” | associação → unordered_map | busca O(1) médio | [Unordered_map](c++/basics/maps-and-sets.md#unordered-map) |
| “Quantas vezes cada valor aparece?” | frequência → vector/array/mapa | domínio pequeno → índice; esparso → mapa | [Contagem](c++/basics/collections.md#frequency-counting) |
| “Retirar sempre o maior disponível” | extremo → max-heap | top O(1), push/pop O(log N) | [Max-heap](c++/data-structures/README.md#max-heap) |
| “Retirar sempre o menor disponível” | extremo → min-heap | greater; top O(1), push/pop O(log N) | [Min-heap](c++/data-structures/README.md#min-heap) |
| “Retirar ESTE valor e manter ordem” | remoção arbitrária → set/multiset | find + erase O(log N); NÃO heap puro | [Multiset](c++/basics/maps-and-sets.md#multiset) |
| “Primeiro valor >= X” | limite inclusivo → lower_bound | vector ordenado fixo / método de set dinâmico | [Lower_bound](c++/algorithms/patterns.md#lower-bound) |
| “Primeiro valor > X” | limite estrito → upper_bound | pula iguais, O(log N) | [Upper_bound](c++/algorithms/patterns.md#upper-bound) |
| “Há algum ativo em [L,R]?” | set.lower_bound(L), conferir <= R | pula vazios, O(log N) | [Set](c++/basics/maps-and-sets.md#set) |
| “Ordenar uma vez e só consultar” | sort + bounds | O(N log N) + O(log N)/busca | [Sort](c++/algorithms/patterns.md#sort) |
| “Ordenar só um trecho / por coluna / preservar índices” | intervalo ou comparator + índices/pares | escolha a variante sem perder a informação necessária | [Variantes de sort](c++/algorithms/sorting.md) |
| “Find/bounds me devolveu um it” | cursor → conferir end → ler *it | índice por diferença só em acesso aleatório | [Iteradores](c++/basics/iterators.md) |
| “Maior nota; empate por menor id” | definir quem vem antes → comparator | regra curta dentro de sort | [Comparator](c++/algorithms/patterns.md#custom-comparator) |
| “Muitas perguntas: quantos <= X?” | ordenar + upper_bound - begin | índice do limite é a quantidade; O(log N) | [Upper_bound](c++/algorithms/patterns.md#upper-bound) |
| “Array fixo + muitas somas [L,R]” | prefix sum | O(N) preparo, O(1)/consulta | [Prefix sum](c++/algorithms/prefix-and-window.md#prefix-sum) |
| “Trecho contínuo cresce/encolhe” | sliding window / two pointers | reaproveita estado; justificar o descarte | [Janela](c++/algorithms/prefix-and-window.md#sliding-window) |
| “Dois valores somam um alvo” | two pointers em dados ordenados | soma guia o movimento; O(N) após sort | [Two pointers](c++/algorithms/patterns.md#two-pointers) |
| “Primeiro menor/maior à esquerda/direita” | monotonic stack | candidatos por posição; O(N) | [Pilha monotônica](c++/algorithms/patterns.md#monotonic-stack) |
| “Máximo/mínimo de cada janela” | sliding window + monotonic deque | expirar + descartar dominados; O(N) | [Deque monotônica](c++/algorithms/patterns.md#monotonic-deque) |
| “Mediana de cada janela” | dois multisets | entra/sai/rebalanceia O(log K) | [Mediana](c++/data-structures/README.md#median) |
| “Teste F,F,V,V: primeiro que funciona” | binary search | O(log U) testes × custo do teste | [Busca binária](c++/algorithms/patterns.md#binary-search) |
| “Muitas adições em intervalos; só ver o final” | vetor de diferenças | O(N+Q), não consulta online | [Diferenças](c++/algorithms/difference-array.cpp) |
| “Atualizar e já consultar somas” | Fenwick / segment tree | O(log N); prefixo estático fica velho | [Reconhecimento](QUAL-ESTRUTURA-USAR.md#op19) |
| “Movimentos, sequência ou resposta a construir” | blocos / propriedade / construção | estrutura sofisticada pode nem ser necessária | [Exemplos abaixo](#problemas-estudados) |

</details>

<a id="problemas-estudados"></a>

<details>
<summary>Entender melhor: problemas estudados</summary>

## Exemplos dos problemas estudados

Pequenas situações para reconhecer o padrão, **não soluções completas**.
Sem os enunciados completos de Pop and Insert e XOR Array, os exemplos deles
abaixo são ilustrativos: não presumem operações/restrições específicas.

### Laser Tag

Ativos {1,4,5,9}; parede [3,7]. `lower_bound(3)` → 4; como 4 <= 7, há um ativo.
Operação repetida: atualizar posições + existência num intervalo → **set**, O(log A)
com A ativos. Vector de 0/1 pode precisar varrer [L,R]; set pula os vazios.
Vários lasers no mesmo x? Preserve contagens, retirando a posição só quando o último sair.
[Exemplo e comandos](c++/basics/maps-and-sets.md#set).

### Sliding Window Median

Janela [1,5,3] → baixo={1,3}, alto={5}, mediana=3.
Sai 1, entra 8 → após rebalancear: baixo={3,5}, alto={8}, mediana=5.
Operações: inserir + apagar um valor arbitrário + consultar meio → **dois multisets**,
O(log K) por avanço. Um único multiset precisa andar O(K) até o meio.
No [CSES](https://cses.fi/problemset/task/1076), K par pede a mediana inferior.
[Invariantes e recorte](c++/data-structures/README.md#median).

### Potions

Escolhidos [4,-4,1], soma 1; tenta entrar -3 → soma -2.
Retirar o menor (-4) recupera mais saúde: soma fica 2, mantendo [4,1,-3].
Operação repetida: quando inválido, retirar pior contribuição → **min-heap**, O(N log N).
Subtrair um negativo aumenta a soma. A correção gulosa descarta o menor, recupera
mais saúde removendo um item e não piora os prefixos anteriores.
Não ordene a entrada: o [problema original](https://codeforces.com/problemset/problem/1526/C2)
exige saúde não negativa durante o percurso.
[Comandos](c++/data-structures/README.md#min-heap).

### Minimum Sum / Subarray Minimum

[3,1,2]: o 1 não tem menor em nenhum lado e pode ser mínimo nos quatro trechos
que o contêm. Operação: descobrir os limites de expansão de cada posição →
**monotonic stack**, O(N), não procurar o mínimo de cada trecho separadamente.
Em [2,2], trate empates: menor estrito num lado e menor ou igual no outro;
estrito dos dois lados contaria o trecho [2,2] duas vezes nas contribuições.
[Exemplo e comandos](c++/algorithms/patterns.md#monotonic-stack).

### Pop and Insert — procurar sequência/blocos

Antes de escolher uma estrutura, pergunte: **o que cada movimento muda na sequência?**
Exemplo ilustrativo: se o critério for “crescer de 1 em 1”, [1,2,7,8,9,3]
tem blocos [1,2] | [7,8,9] | [3]. Uma varredura detecta as quebras em O(N).
Se o enunciado usar outro critério, adapte a comparação. Não conclua uma resposta
de movimentos só pelo número de blocos: é necessário provar o efeito das operações.

### XOR Array — construção e propriedade

Primeiro escreva a condição que o array construído deve satisfazer.
Propriedades: `x ^ x = 0` e `x ^ 0 = x`; [5,5] tem XOR zero **se repetição for permitida**.
Isso pode guiar uma construção sem set/heap. Não é solução pronta:
confira tamanho, limites dos valores, unicidade e valide todas as condições.
N elementos impressos já exigem O(N) trabalho, mesmo que a ideia seja uma fórmula.

</details>

<details>
<summary>Entender melhor: raciocínios passo a passo e equivalentes Python</summary>

## Referências e equivalentes C++ / Python

Consultas novas: [vizinhos, lower_bound e upper_bound](c++/algorithms/bounds.cpp);
[atualizações de intervalos](c++/algorithms/difference-array.cpp);
[janela com até K distintos](c++/algorithms/sliding-window-distinct.cpp).

Novo assunto: [prefix sum × sliding window, com execução passo a passo](c++/algorithms/prefix-and-window.md).
Para melhor soma de exatamente K consecutivos, use janela fixa
([C++](c++/algorithms/sliding-window-fixed.cpp), [Python](python/algorithms/sliding_window_fixed.py)).
Para maior trecho com soma limitada e valores não negativos, use a variante
de janela variável ([C++](c++/algorithms/sliding-window-variable.cpp),
[Python](python/algorithms/sliding_window_variable.py)).

| O que você percebeu | Técnica candidata e condição | C++17 | Python |
|---|---|---|---|
| Quantas vezes cada valor aparece | Frequências; vetor se valores forem pequenos e limitados, mapa caso contrário | [Map](c++/basics/map.cpp) | [Counter](python/collections/frequency.py) |
| Quais valores existem ou quantos são diferentes | Set; duplicatas não precisam ser preservadas | [Set](c++/basics/set.cpp) | [Set](python/collections/sets.py) |
| Localizar um valor sem dados ordenados | Busca linear; para poucas consultas pode bastar | [Busca linear](c++/algorithms/linear-search.cpp) | [Busca](python/algorithms/searching.py) |
| Primeiro valor que atinge um limite | Busca binária; vetor ordenado ou predicado monotônico | [Busca binária](c++/algorithms/binary-search.cpp) | [Bisect](python/algorithms/searching.py) |
| Muitas somas de intervalos | Prefix sum; valores fixos entre consultas | [Prefix sum](c++/algorithms/prefix-sum.cpp) | [Prefix sum](python/algorithms/prefix_sum.py) |
| Dois valores cuja soma é um alvo | Dois ponteiros; exemplo exige sequência ordenada | [Dois ponteiros](c++/algorithms/two-pointers.cpp) | [Dois ponteiros](python/algorithms/two_pointers.py) |
| Primeiro que chega deve sair primeiro | Fila (FIFO) | [Queue](c++/data-structures/queue.cpp) | [Deque](python/collections/queue.py) |
| Último item pendente deve ser resolvido primeiro | Pilha (LIFO); fechamento de símbolos é um exemplo | [Stack](c++/data-structures/stack.cpp) | [Pilha](python/collections/balanced.py) |
| Inserir/remover nas duas extremidades | Deque; acesso ao meio tem custos diferentes nas linguagens | [Deque](c++/data-structures/deque.cpp) | [Operações](python/cheatsheets/python-collections.md#deque) |
| Retirar repetidamente o maior/menor disponível | Heap; útil com inserções entre retiradas | [Priority queue](c++/data-structures/priority-queue.cpp) | [Heap](python/collections/heap.py) |
| Agrupar iguais ou comparar vizinhos por valor | Ordenação; preserve índices originais se necessários | [Sort](c++/algorithms/sorting.cpp) | [Sort](python/algorithms/sorting.py) |
| Máximo número de intervalos sem conflito | Guloso pelo menor fim; intervalos sem pesos | [Guloso](c++/algorithms/greedy.cpp) | [Guloso](python/algorithms/greedy.py) |
| Divisibilidade, primos ou divisores | Teoria dos números; testar até a raiz só cabe para N moderado | [Matemática](c++/math/number-theory.cpp) | [Matemática](python/math/number_theory.py) |
| Potência enorme com resposta módulo M | Exponenciação modular; confira limites da multiplicação | [Potência modular](c++/math/modular-power.cpp) | [pow(a,b,mod)](python/math/README.md) |
| Transformar caracteres ou contar letras | Conversão + frequência; confirme alfabeto e maiúsculas | [Strings](c++/basics/strings.md) | [Strings](python/cheatsheets/python-strings.md) |

Busca binária em vetor exige ordem compatível. Na resposta, quem precisa ser
monotônico é o teste de viabilidade; não é obrigatório ordenar a entrada.
Nenhuma dessas associações substitui a leitura das restrições.

## Roteiro ao receber uma questão

1. **Reescreva o objetivo em uma frase.** Ex.: “Para cada intervalo, devolver a soma”.
   Separe o objetivo da história: clientes, monstros e tarefas podem usar a mesma estrutura.
2. **Identifique entrada e saída.** Quantos elementos, consultas e casos? Índices começam
   em zero ou um? É para devolver valor, posição, quantidade ou uma construção?
3. **Anote propriedades.** Há ordem? Duplicatas? Negativos? Os dados mudam? A resposta
   precisa respeitar a ordem original? É um trecho contíguo ou qualquer subconjunto?
4. **Pense na solução direta.** Mesmo lenta, ela ajuda a entender e testar o problema.
5. **Estime o custo e encontre a repetição.** Está recontando, ressomando ou buscando
   os mesmos dados? Essa repetição costuma apontar para a otimização.
6. **Escolha uma candidata no mapa e tente derrubá-la.** Use um caso pequeno que
   explore suas limitações antes de implementar.
7. **Abra o arquivo e adapte.** Confira pré-condições, tipos, leitura e saída.
   As mensagens demonstrativas dos exemplos não devem ir para o juiz sem adaptação.

### Preciso armazenar tudo?

Para somar, contar ou verificar se a sequência é estritamente crescente, geralmente
basta manter acumulador, frequências ou último valor. Para ordenar, revisitar ou
responder consultas por posição, armazenar costuma ser necessário.

Exemplo: em 2, 5, 5, 9, o segundo 5 viola crescimento estrito. Compare cada valor
com o anterior; depois de detectar falha, não redefina o resultado para verdadeiro.

## Exemplos de raciocínio

### 1. Vendas entre os dias L e R

**Pedido:** N vendas fixas e Q consultas de soma.

- Direto: percorrer cada trecho, até O(NQ).
- Trabalho repetido: somar as mesmas vendas em consultas sobrepostas.
- Aproveitamento: pré-calcular somas acumuladas, O(N + Q) no total.
- Para vendas [2, 3, 5, 1], prefixos [0, 2, 5, 10, 11].
  Soma dos índices 1 até 2: prefix[3] - prefix[1] = 10 - 2 = 8.
- **Procure prefix sum.** Se houver alterações nas vendas, essa versão fica
  desatualizada; não a use como se cada atualização também fosse O(1).

### 2. Atendimento de clientes

**Pedido A:** atender por ordem de chegada → fila.
**Pedido B:** atender a maior prioridade disponível, com novas chegadas → heap.

Chegam prioridades 2, 9, 4: FIFO atende 2 primeiro; heap máximo atende 9.
A palavra “cliente” não escolhe a estrutura; a regra de retirada escolhe.
Se todas as chegadas já ocorreram e você só precisa listar por prioridade,
uma ordenação pode ser suficiente.

### 3. Dois preços que somam um orçamento

**Pedido:** escolher dois itens distintos cuja soma seja 10.

- Direto: testar todos os pares, O(N²).
- Com preços ordenados [1, 3, 4, 7], pontas dão 1+7=8.
- A soma é pequena; mover a direita para valores menores não ajudaria.
  Avance a esquerda: 3+7=10.
- **Procure dois ponteiros.** Ordenar custa O(N log N), caso necessário.
  Para devolver índices originais, carregue pares (valor, índice).
- Esse exemplo encontra um par; contar todos os pares exige tratar duplicatas.
  A técnica de janela por soma é outra variante e pode falhar com negativos.

### 4. Quantos códigos diferentes foram enviados?

Entrada: [8, 2, 8, 3, 2].

- Apenas quantidade de diferentes: set → {2, 3, 8}, resposta 3.
- Quantas vezes cada um apareceu: frequência → 2:2, 3:1, 8:2.
- **Procure set ou map conforme a saída exigida.** Set sozinho não preserva
  quantidades nem a sequência original.

### 5. Primeiro produto com preço pelo menos X

Preços ordenados [4, 7, 7, 12], X=7: primeiro índice é 1.

- O teste “preço >= 7” gera falso, verdadeiro, verdadeiro, verdadeiro.
- Essa transição única permite descartar metade dos candidatos: busca binária.
- **Procure lower_bound/bisect_left.** Com X=20, retorna tamanho da sequência:
  isso é ausência, não um índice acessível.
- Perguntar se existe exatamente X exige também comparar o valor encontrado.
  Sem ordenação, o padrão de falsos/verdadeiros pode não existir.

### 6. Escolher o máximo de atividades

Atividades [0,2), [1,4), [2,3): escolher [0,2) e [2,3) permite duas.

- Ordenar pelo fim e aceitar a próxima compatível é a candidata gulosa.
- Justificativa: trocar a primeira atividade de uma solução ótima pela que termina
  antes não reduz o tempo disponível para as seguintes; repita o argumento.
- **Procure guloso de intervalos.** Se [1,4) pagar 100 e as outras pagarem 1,
  maximizar quantidade não maximiza pagamento. O exemplo não resolve pesos.

## Os limites ajudam a eliminar ideias

- N=100: comparar todos os pares faz cerca de 10 mil verificações.
- N=100.000: N² chega a 10 bilhões; procure uma forma de evitar esse trabalho.
- N=20: enumerar 2^N subconjuntos dá cerca de um milhão; pode ser uma candidata,
  dependendo do custo por subconjunto e do número de casos.
- Q também importa: uma busca O(N) repetida Q vezes custa O(NQ).
- Considere a soma dos tamanhos de todos os casos e a memória, além do maior N.

São estimativas, não garantias de tempo. Python e C++ têm constantes diferentes;
operações com strings, mapas e inteiros enormes não custam o mesmo que uma soma simples.
Veja [C++: tempo e memória](c++/basics/performance.md) e
[Python: performance](python/basics/performance.md).

## Armadilhas de reconhecimento

- “Menor” ou “maior” não implica guloso. A escolha local precisa de justificativa.
- “Intervalo” não implica prefix sum. Soma fixa é uma situação específica;
  mínimo de intervalo, atualizações e janelas pedem análises diferentes.
- “Ordenar” pode ser só uma etapa, não a solução completa.
- Não use busca binária apenas porque N é grande: demonstre a monotonicidade.
- Um problema pode combinar técnicas: ordenar + dois ponteiros; conversões +
  frequência; ordenar + guloso.
- Se envolver caminhos, conectividade, decisões com estados ou geometria, talvez
  a técnica necessária ainda não esteja nesta biblioteca. Não force um encaixe.

## Quando travar

Faça um exemplo pequeno à mão, descreva a solução direta e procure o trabalho
repetido. Tente entradas com um elemento, duplicatas, valor ausente e limites.
Para otimizações, compare a ideia com força bruta em casos pequenos.

Use este rascunho para organizar o raciocínio antes de procurar código:

    Objetivo em uma frase:
    Entrada, limites e número de consultas/casos:
    Saída esperada:
    Propriedades que posso aproveitar:
    Solução direta e custo:
    Trabalho repetido:
    Técnica candidata e por que funciona:
    Contraexemplo ou condição que pode invalidá-la:
    Arquivo que vou consultar:
    Adaptações e casos de teste:

Não é necessário conhecer o nome da técnica de imediato. Primeiro identifique
a operação e as propriedades; depois use o material para localizar uma implementação.

</details>
