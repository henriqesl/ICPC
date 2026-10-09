# BACKTRACKING — do enunciado ao estado

[Índice](README.md) · [Mapeamento](#mapeamento) · [Combinar modelos](#modelos) ·
[Caso base](#base) · [Faz/recursa/desfaz](#desfaz) · [Poda](#poda) · [Receitas C++](backtracking-templates.cpp)

**O centro é: TIPO DE RETORNO + TIPO DE ESCOLHA.**
“Quantas?” decide como juntar respostas; “pega/não pega” decide como abrir os ramos.
São decisões diferentes. Não escolha um template só pelo tema da questão.

```text
ENUNCIADO → ESTADO → ESCOLHAS → VALIDADE / PODA → CASO BASE → O QUE RETORNAR
```

## CONSULTA RÁPIDA — QUAL PARTE DO CÓDIGO PRECISO?

Abra [backtracking-templates.cpp](backtracking-templates.cpp) e procure `TEMPLATE N`:

| Pedido | Receita |
|---|---|
| A) Existe alguma solução? | 1: bool, para no primeiro sucesso |
| B) Quantas soluções? | 2: long long, soma os filhos |
| C) Pega / não pega | 3: duas chamadas por índice |
| D) Uma opção entre várias | 4: for nas opções da etapa |
| E) Permutação / usados | 5: used[], marca e desmarca |
| F) Melhor solução | 6: min/max e branch and bound |
| G) Grid / caminho | 7: vizinhos e visited do caminho |

<a id="mapeamento"></a>
## COMO MAPEAR O ENUNCIADO PARA O BACKTRACKING

### ENUNCIADO DIZ: “QUANTAS MANEIRAS / CONFIGURAÇÕES VÁLIDAS?”

- **Retorno:** quantidade (`long long` se couber; módulo se o enunciado pedir).
- **Estado/escolhas:** ainda precisam vir das decisões descritas no problema.
- **Caso base válido:** retorna 1; inválido retorna 0.
- **Junção:** some todas as chamadas; não pare no primeiro sucesso.

Se uma etapa tem filhos com 2, 0 e 3 soluções, ela retorna 5, não “true”.
Antes de contar, defina se soluções diferem por índice, por valor ou por ordem.

### ENUNCIADO DIZ: “EXISTE ALGUMA FORMA / É POSSÍVEL COMPLETAR?”

- **Retorno:** bool. Folha válida retorna true; sem opção viável retorna false.
- **Junção:** basta um filho verdadeiro; pode parar no primeiro sucesso.
- **Estado:** o que já foi decidido e o que falta completar.
- **Restauração:** desfaça antes de retornar true. Se precisar mostrar a solução,
  salve uma cópia na folha válida antes de desfazer.

O pedido é existência, não “quantas”: não precisa percorrer o restante da árvore após achar uma.

### ENUNCIADO DIZ: “PARA CADA ELEMENTO POSSO ESCOLHER OU NÃO”

- **Estado:** idx + o efeito das escolhas anteriores (soma, cobertura, capacidade…).
- **Escolhas:** pega idx / não pega idx; ambas seguem para idx + 1.
- **Validade/poda:** depende do efeito acumulado, não apenas do índice.
- **Caso base:** idx == N; agora confira a condição final.
- **Retorno:** bool, quantidade, min ou max, conforme o pedido.
- **Árvore:** binária, O(2^N) nós se cada atualização/teste custar O(1).

Exemplo neutro: “quantos subconjuntos têm soma T?” → estado (idx,sum), duas escolhas,
folha retorna `sum == T ? 1 : 0`, filhos somam. Valores negativos impedem a poda automática sum > T.

### ENUNCIADO DIZ: “EM CADA ETAPA ESCOLHO UMA OPÇÃO ENTRE VÁRIAS”

- **Estado:** posição, linha ou etapa atual + restrições já ocupadas.
- **Escolhas:** for nas opções daquela etapa, pulando as inválidas.
- **Transição:** aplica, recursa para próxima etapa, desfaz.
- **Caso base:** passou da última etapa; conta 1 ou retorna true se tudo estiver válido.

“Uma opção” é **uma por etapa**, não uma única escolha no problema inteiro.
No exemplo dos templates 1/2, cada posição tem seus valores permitidos e vizinhos não podem repetir:
estado = pos + prefixo atual; escolha = valor; validade = diferente do anterior.
Com opções {1,2} em duas posições, existem duas sequências válidas: [1,2] e [2,1].

### ENUNCIADO DIZ: “USAR CADA ELEMENTO UMA VEZ / TODAS AS ORDENS”

- **Estado:** pos + used[] + prefixo da permutação.
- **Escolhas:** cada índice ainda não usado.
- **Transição:** marca used[i], coloca a[i], recursa, desmarca.
- **Caso base:** pos == N; processe a solução.
- **Retorno:** void para listar/avaliar, bool para existência ou count para contar.

Só pos não descreve quais itens sobraram. Valores iguais em índices distintos podem gerar
sequências repetidas; o template explica como ordenar e pular duplicatas se o pedido distinguir só valores.

### ENUNCIADO DIZ: “PREENCHER TABULEIRO / UMA ESCOLHA POR LINHA”

- **Estado:** célula/linha atual + tabuleiro parcial + ocupações.
- **Escolhas:** valores ou colunas possíveis na posição atual.
- **Validade:** bloqueios, coluna usada, diagonais ou outras regras do enunciado.
- **Caso base:** passou da última posição relevante.
- **Retorno:** conte todas as configurações ou pare na primeira, conforme a pergunta.

Exemplo: uma peça por linha sem compartilhar coluna/diagonal → estado row,
escolha col, conflitos em `row + col` e `row - col + N - 1`.
O template 4 conta; as ocupações guardam o histórico que não aparece no parâmetro row.

<a id="modelos"></a>
## MAPEAMENTO POR PADRÃO — OS MODELOS SE COMBINAM

| Frase / estrutura | Estado provável | Escolhas prováveis | Retorno |
|---|---|---|---|
| Quantas configurações válidas? | etapa + restrições acumuladas | explorar todas as válidas | long long |
| É possível completar? | posição + situação parcial | opções válidas | bool |
| Escolher subconjunto | idx + soma/cobertura | pega / não pega | bool/count/min/max |
| Uma escolha por linha | row + colunas/diagonais ocupadas | colunas | count/bool |
| Gerar permutação | pos + used[] + prefixo | índices não usados | processar solução |
| Achar melhor solução | etapa + custo + restrições | todas que ainda podem melhorar | min/max |
| Caminho simples com restrições | posição + visitados do caminho + estado extra | vizinhos válidos | bool/count/min/max |

**Não são categorias mutuamente exclusivas:**

- **N-Rainhas:** B (quantas?) + D (uma coluna por linha). Base row == N; cada configuração soma 1.
- **Coverage:** B (quantas?) + C (pega/não pega). Estado (idx,coverage);
  pegar faz `coverage | mask[idx]`; na folha, `coverage == FULL` vale 1, senão 0.
  Explorar até idx == N evita esquecer escolhas opcionais posteriores, mesmo se a cobertura já estiver completa.
- **Completar uma sequência:** A (existe?) + D (uma opção por posição). Base pos == N;
  retorna true no primeiro preenchimento válido.
- **Menor custo de exatamente K escolhas:** F (melhor) + C (pega/não pega);
  estado (idx,chosen,current_cost), folha quando chosen == K.

Em coverage, passe a máscara por valor ou salve a antiga para restaurar.
OR **não** se desfaz com XOR: duas escolhas podem cobrir o mesmo bit.

<a id="base"></a>
## CASO BASE — QUANDO NÃO EXISTE MAIS DECISÃO A TOMAR?

O índice só diz que a construção terminou; a condição final diz se ela serve.

| Construção mapeada | Acabou quando… | Ainda precisa conferir? |
|---|---|---|
| Subsets | idx == N | soma == alvo, coverage == FULL… |
| Permutação | pos == N | restrições finais, se não foram garantidas durante a construção |
| N-Rainhas / uma peça por linha | row == N | não, se conflitos foram impedidos em cada escolha |
| Sudoku por célula | pos == 81 ou row == 9 | só com tabuleiro inicial válido e preenchimentos válidos; ignore células fixas |
| Lista de células vazias | idx == vazias.size() | terminou a última decisão relevante |
| Caminho | u == destino | entrada é válida? comprimento/cobertura exigidos foram atendidos? |

Para contar, folha **válida** retorna 1. Para existência, retorna true.
Com condição final, retorne `condicao_final ? 1 : 0` ou `condicao_final`.
Coverage: `if (idx == N) return coverage == FULL;` (bool ou 0/1 convertido para count).
Para minimizar, atualize a melhor resposta; para listar, processe a construção completa.
Sem opções válidas antes do fim: 0 maneiras / false. Não transforme esse beco sem saída em solução.

<a id="desfaz"></a>
## FAZ → RECURSA → DESFAZ

| Faz | Recursa | Desfaz |
|---|---|---|
| board[row][col] = 'Q' | ways += solve(row + 1) | board[row][col] = '.' |
| used[i] = true | solve(pos + 1) | used[i] = false |
| sum += a[idx] | solve(idx + 1) | sum -= a[idx] |

Desfaça **tudo que modificou na construção parcial**: tabuleiro, coluna, diagonais, frequência, custo etc.
A melhor resposta global e as soluções salvas são resultados: não devem ser desfeitas.
Dados passados por valor já são isolados; shared/global/referência precisa de restauração.
Nos templates, `exists` restaura antes de retornar true; o buffer da permutação também é restaurado.
Se quiser manter um testemunho, copie a solução à parte em vez de deixar flags sujas.
Antes de outro caso de teste, reinicialize vetores, flags, current e melhor resposta.

<a id="poda"></a>
## VALIDADE / PODA — QUAL RAMO O TEXTO PROÍBE OU TORNA INÚTIL?

| Enunciado / regra | Tradução no código | Por que pode descartar? |
|---|---|---|
| Posição bloqueada | continue / return false | nunca pode fazer parte da solução |
| Coluna já usada | continue | violaria exclusividade |
| Diagonal atacada | continue | violaria conflito geométrico |
| Soma passou do alvo | return 0/false **se restantes não negativos** | não existe como reduzir; negativos podem corrigir |
| Custo atual já >= melhor mínimo | return **se custos restantes não negativos** | completar não pode melhorar |
| Teto otimista <= melhor máximo | return | nem a melhor continuação imaginável supera o atual |
| Faltam mais itens que os disponíveis | return | impossível completar a quantidade exigida |
| Estado repetido | talvez memo / visited | só se o estado guardar tudo que influencia o futuro |

No template 6, os custos são não negativos: min poda pelo custo atual;
max usa `current + suffix[idx]` como teto, somando todos os custos restantes.
Esse teto pode ignorar o limite K, mas não pode subestimar uma continuação válida.
Para podar mínimo por um limite, ele deve ser um **piso** seguro; máximo exige **teto** seguro.
Se precisar contar soluções ótimas, podar empates pode apagar respostas: adapte a regra.

Memo não é um simples “já visitei”: para contar, reutilize o **número de continuações**;
para otimizar, reutilize a melhor continuação se o estado for suficiente.
Em permutação, só pos é insuficiente; em caminho com restrições, só a célula pode ser insuficiente.

## GRID / CAMINHO — QUANDO DESFAZER visited?

- **Todos os caminhos simples / restrição dependente do caminho:** visited significa
  “está neste caminho”. Marque ao entrar e desmarque ao sair; outro ramo pode usar a célula.
- **Apenas existe caminho, sem outra restrição:** DFS/BFS com visited permanente basta,
  em O(V+E). Encontrar algum caminho simples não exige enumerar todos: ciclos podem ser evitados.
- **Explorar componente inteira:** visited significa “já processado”; não desmarque,
  não pare no primeiro destino e processe todos os vizinhos alcançáveis.

O template 7 mostra a versão que restaura o caminho, inclusive no sucesso.
Antes do caso base, verifica limites, bloqueio e visited: destino bloqueado não é sucesso.
Para só alcance, retire os dois desfazeres; para contar caminhos simples, troque bool por contagem
e explore todas as alternativas. Não conte caminhos com visited permanente.

## COMPLEXIDADE — RETORNO NÃO DETERMINA O TAMANHO DA ÁRVORE

| Escolhas | Pior caso / memória extra |
|---|---|
| Pega/não pega, atualização O(1) | O(2^N) tempo; O(N) pilha |
| Até B opções em D etapas | O(B^D), para B >= 2 e trabalho O(1) por ramo; O(D) pilha |
| Peças por linha com coluna exclusiva | até O(N · N!) com loop de N colunas por nó; O(N) flags/pilha, além do board |
| Permutação com loop de N índices por nó | O(N · N!) incluindo avaliação/saída O(N); O(N) pilha/used/current |
| Melhor subconjunto por branch and bound | O(2^N) no pior caso; O(N) pilha/suffix |
| Caminhos simples no grid de V células | limite grosseiro O(4^V); O(V) visited/pilha |
| Alcance/componente com visited permanente | O(V+E), O(V) memória |

Poda melhora muitos casos, **não garante** que deixa de ser exponencial/fatorial.
Conte o custo real de validar/copiar/avaliar. Long long pode estourar ao contar; use o módulo pedido
ou outro tipo adequado. Recursão profunda pode estourar a pilha mesmo quando há poucos ramos.

## NÃO CONFUNDIR / ARMADILHAS

| Comparação | Diferença prática |
|---|---|
| Backtracking × bitmask | ambos geram subsets; bitmask é iterativo, backtracking permite poda parcial natural |
| Backtracking × next_permutation | este gera ordens completas; backtracking pode impedir um prefixo inválido |
| Backtracking × greedy | greedy normalmente não desfaz para explorar alternativas; backtracking explora |
| Contar × existir | soma todos os filhos × para no primeiro true |
| Estado × parâmetro | parte pode estar em globals/used/board; precisa estar coerente e ser restaurada |

Não use return 1 só porque chegou ao fim se a condição final não foi atendida.
Não conte a mesma configuração por caminhos diferentes sem definir a identidade da solução.
Não use poda de soma/custo com negativos sem prova. Não mantenha marcações permanentes
entre ramos ao enumerar caminhos simples. Não deixe `used[]` marcado após um retorno antecipado.

Os templates completos ficam **apenas** no [.cpp](backtracking-templates.cpp), sem cópia neste guia.
Teste na raiz icpc/: `python -B c++/test_backtracking.py`.
