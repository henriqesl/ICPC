# BACKTRACKING — escolher, explorar, desfazer

[Índice](README.md) · [Mapeamento](#mapeamento) · [Modelos](#modelos) · [Base](#base) · [Desfazer](#desfaz) · [Poda](#poda) · [Código](backtracking-templates.cpp)

**Use:** construir aos poucos, testar restrições e tentar alternativas. Geralmente N pequeno.

**Não confunda:** “existe/quantas/melhor” define o retorno; “pega/não pega/opções/usados” define os ramos.

<a id="mapeamento"></a>
## CONSULTA RÁPIDA — ESCOLHA A RECEITA

Abra [backtracking-templates.cpp](backtracking-templates.cpp) e use Ctrl+F em `TEMPLATE N`.
As funções são exemplos com regras específicas: adapte validade/base à sua questão.

| Pedido | Receita / função | Estado / ação |
|---|---|---|
| Existe solução? | 1: `decisions::exists(0)` | posição + prefixo; para no primeiro true |
| Quantas soluções? | 2: `decisions::count(0)` | mesmo estado; soma todos os filhos |
| Escolher subconjunto com soma alvo | 3: `subsets::count(0)` | idx + soma; pega / não pega |
| Uma coluna por linha sem conflitos | 4: `placements::count(0)` | linha + colunas/diagonais; for nas colunas |
| Todas as ordens | 5: `permutations::generate(0)` | posição + used + prefixo; marca/desmarca |
| Menor/maior custo de exatamente K itens | 6: `optimization::minimize(0,0)` / `maximize(0,0)` | idx + escolhidos + custo; atualiza melhor global |
| Caminho com restrições | 7: `paths::exists(r,c)` | posição + visited do caminho; tenta vizinhos |

**Antes de chamar:** inicialize os dados/flags como indicado no cabeçalho da receita.
1/2 impedem vizinhos iguais; 4 usa bloqueios e diagonais; 6 exige custos não negativos.
Não copie o arquivo inteiro como solução: não tem main. Copie uma receita e as declarações usadas.

<a id="modelos"></a>
## RETORNO + ESCOLHAS — COMBINE OS DOIS

| O problema pergunta | Na folha válida | Juntar os filhos |
|---|---|---|
| Existe? | true | basta um true; pode parar |
| Quantas? | 1 | soma todos |
| Melhor? | atualize melhor resposta | min/max, sem perder alternativas melhores |
| Listar? | imprima/salve a construção | explore todas as válidas |

Exemplos: N-Rainhas = **contar + opções por linha**; soma de subconjunto = **contar + pega/não pega**.

<a id="base"></a>
## CASO BASE — ACABOU, MAS É VÁLIDO?

| Construção | Terminou | Confira |
|---|---|---|
| Subconjunto | idx == N | soma == alvo / coverage == FULL |
| Permutação | pos == N | regras finais não garantidas antes |
| Uma peça por linha | row == N | conflitos já impedidos em cada escolha |
| Caminho | chegou ao destino | célula válida e demais exigências atendidas |

Folha inválida: 0 / false. Sem opções antes do fim também é falha, não solução.
Contagem distingue soluções por índice, valor ou ordem? Defina isso antes de codar.

<a id="desfaz"></a>
## FAZ → RECURSA → DESFAZ

| Faz | Depois da chamada, desfaz |
|---|---|
| `used[i] = 1` | `used[i] = 0` |
| `sum += a[idx]` | `sum -= a[idx]` |
| `current.push_back(x)` | `current.pop_back()` |
| marca board/coluna/diagonais | restaura todos |

Desfaça **inclusive antes de retornar true**. Melhor resposta/soluções salvas são resultados: não desfaça.
Passou estado por valor? A cópia já isola. OR não se desfaz com XOR: passe coverage por valor ou salve o valor antigo.
Reinicialize globais entre casos. Para mostrar uma solução, salve-a antes de desfazer.

<a id="poda"></a>
## PODA — SÓ DESCARTE COM JUSTIFICATIVA

| Pode parar quando... | Hipótese necessária |
|---|---|
| posição bloqueada / coluna ocupada / conflito | regra torna a escolha inválida |
| faltam mais itens que os disponíveis | impossível atingir quantidade exigida |
| soma passou do alvo | restantes não negativos; negativos podem corrigir |
| custo atual >= melhor mínimo | custos restantes não negativos |
| teto otimista <= melhor máximo | teto nunca subestima a continuação |

Minimizar usa piso seguro; maximizar usa teto seguro. Para contar soluções ótimas, não descarte empates sem adaptar.

## GRID / CAMINHO — QUAL visited?

- **Enumerar caminhos simples/regras dependentes do caminho:** marca ao entrar, desmarca ao sair.
- **Só alcance/componente:** [DFS](../grafos/dfs.cpp) com visited permanente; [BFS](../grafos/bfs.cpp) também dá menor distância sem peso, O(V+E). [Labirinto](../grafos/bfs_grid.cpp). Não enumere caminhos.

Não conte caminhos com visited permanente. Memorizar só a célula/posição pode ser insuficiente se o histórico muda o futuro.

## COMPLEXIDADE / ARMADILHAS

| Árvore, com trabalho O(1) por ramo salvo indicação | Pior caso / memória extra |
|---|---|
| Pega/não pega | O(2^N) / O(N) pilha |
| B opções em D etapas, B >= 2 | O(B^D) / O(D) pilha |
| Permutação ou colunas exclusivas, loop N por nó | O(N·N!) / O(N), além do board |
| Caminhos simples em V células | limite grosseiro O(4^V) / O(V) |

Poda **não garante** um algoritmo rápido. Conte validação/cópia/saída, overflow de contagem e profundidade da pilha.
Bitmask gera subconjuntos completos; next_permutation gera ordens completas; backtracking permite cortar prefixos inválidos.

<details>
<summary>Entender melhor: traduzir frases do enunciado</summary>

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

</details>

<details>
<summary>Entender melhor: N-Rainhas, coverage e combinações</summary>

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

</details>

Teste fora do contest: `python -B c++/test_backtracking.py`.
