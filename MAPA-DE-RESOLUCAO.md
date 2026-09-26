# Do enunciado à técnica

[Voltar ao índice](README.md)

**O que preciso descobrir → quais propriedades posso aproveitar → qual custo cabe nos limites.**
Use o mapa para levantar hipóteses. Antes de copiar um exemplo, confirme suas pré-condições.

## Mapa rápido

| O que você percebeu | Técnica candidata e condição | C++17 | Python |
|---|---|---|---|
| Quantas vezes cada valor aparece | Frequências; vetor se valores forem pequenos e limitados, mapa caso contrário | [Map](c++/data-structures/map/frequency-map.cpp) | [Counter](python/collections/frequency.py) |
| Quais valores existem ou quantos são diferentes | Set; duplicatas não precisam ser preservadas | [Set](c++/data-structures/set/set-example.cpp) | [Set](python/collections/sets.py) |
| Localizar um valor sem dados ordenados | Busca linear; para poucas consultas pode bastar | [Busca linear](c++/algorithms/searching/linear-search.cpp) | [Busca](python/algorithms/searching.py) |
| Primeiro valor que atinge um limite | Busca binária; vetor ordenado ou predicado monotônico | [Busca binária](c++/algorithms/searching/binary-search-main.cpp) | [Bisect](python/algorithms/searching.py) |
| Muitas somas de intervalos | Prefix sum; valores fixos entre consultas | [Prefix sum](c++/algorithms/prefix-sum/prefix-sum-main.cpp) | [Prefix sum](python/algorithms/prefix_sum.py) |
| Dois valores cuja soma é um alvo | Dois ponteiros; exemplo exige sequência ordenada | [Dois ponteiros](c++/algorithms/two-pointers/two-pointers.cpp) | [Dois ponteiros](python/algorithms/two_pointers.py) |
| Primeiro que chega deve sair primeiro | Fila (FIFO) | [Queue](c++/data-structures/queue/queue-example.cpp) | [Deque](python/collections/queue.py) |
| Último item pendente deve ser resolvido primeiro | Pilha (LIFO); fechamento de símbolos é um exemplo | [Stack](c++/data-structures/stack/balanced-parentheses-main.cpp) | [Pilha](python/collections/balanced.py) |
| Inserir/remover nas duas extremidades | Deque; acesso ao meio tem custos diferentes nas linguagens | [Deque](c++/data-structures/deque/deque-example.cpp) | [Operações](python/cheatsheets/python-collections.md#deque) |
| Retirar repetidamente o maior/menor disponível | Heap; útil com inserções entre retiradas | [Priority queue](c++/data-structures/priority-queue/priority-queue-example.cpp) | [Heap](python/collections/heap.py) |
| Agrupar iguais ou comparar vizinhos por valor | Ordenação; preserve índices originais se necessários | [Sort](c++/algorithms/sorting/sorting-example.cpp) | [Sort](python/algorithms/sorting.py) |
| Máximo número de intervalos sem conflito | Guloso pelo menor fim; intervalos sem pesos | [Guloso](c++/algorithms/greedy/intervals.cpp) | [Guloso](python/algorithms/greedy.py) |
| Divisibilidade, primos ou divisores | Teoria dos números; testar até a raiz só cabe para N moderado | [Matemática](c++/math/number-theory.cpp) | [Matemática](python/math/number_theory.py) |
| Potência enorme com resposta módulo M | Exponenciação modular; confira limites da multiplicação | [Potência modular](c++/math/modular-power.cpp) | [pow(a,b,mod)](python/math/README.md) |
| Transformar caracteres ou contar letras | Conversão + frequência; confirme alfabeto e maiúsculas | [Strings](c++/cheatsheets/strings.md) | [Strings](python/cheatsheets/python-strings.md) |

Os exemplos de busca binária do repositório trabalham com vetores ordenados.
Busca binária sobre uma resposta exige escrever e justificar outro predicado.
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
