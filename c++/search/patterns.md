# PADRÕES — reconhecer, comparar e estimar

[Índice](README.md) · [Não confundir](#nao-confundir) · [Complexidades](#complexidades) · [Armadilhas](#armadilhas)

## ENUNCIADO / NECESSIDADE → TÉCNICA PROVÁVEL

| Enunciado / necessidade | Técnica provável e confirmação |
|---|---|
| Procurar x sem ordem útil | [Linear](binary-search.md#linear); muitas consultas podem pedir outra estrutura |
| Valor exato em array ordenado | [Binary search tradicional](binary-search.md#tradicional) |
| Primeiro >= x / primeiro > x / contar iguais | [Bounds](binary-search.md#bounds); limite não garante igualdade |
| “menor X que funciona”, menor tempo/capacidade/velocidade | [FIRST TRUE](binary-search.md#first-true): maiores também viáveis? |
| “maior X que ainda funciona” | [LAST TRUE](binary-search.md#last-true): menores também viáveis? |
| “maximize o mínimo” | LAST TRUE, se diminuir a exigência mantiver viabilidade |
| “minimize o máximo” | FIRST TRUE, se aumentar o limite mantiver viabilidade |
| “subarray contínuo”, janela válida ou frequência limitada | [Sliding window](two-pointers.md#janela), se expandir/contrair ajustar a condição monotonicamente |
| Par com soma alvo + ordenado | [Two sum](two-pointers.md#par): pontas opostas |
| Par com diferença alvo + ordenado | [Two difference](two-pointers.md#diferenca): ambos para a direita |
| Merge de arrays ordenados | [Dois índices, um por array](two-pointers.md#merge) |
| Muitos intervalos em tempo/coordenada | [Sweep line](sweep-line.md#receita) |
| “quando algo começa/termina” | Eventos START/END; defina extremos e empates |
| Consultar estado em um ponto | [QUERY como evento](sweep-line.md#query-events) ou histórico + bounds |
| Coordenadas 1e9, mas só 2e5 usadas | [Compression](sweep-line.md#compression) **se precisar de índices**; varredura direta pode dispensar |
| “quantos estão ativos” | [Contador](sweep-line.md#estado), não set por hábito |
| “quais estão ativos” | Set de ids únicos; valores repetidos pedem outra representação |
| Ativos com valores repetidos | Multiset; saída de um remove por iterator |
| Menor/maior ativo | begin()/rbegin(), após conferir que não está vazio |
| Soma/frequência dos ativos | Soma corrente / map, unordered_map ou vetor |
| Todas as escolhas, pego ou não pego | [Subsets / bitmask](exhaustive-search.md#subconjuntos) |
| Todas as ordens | [Permutations](exhaustive-search.md#permutacoes) |
| N <= aproximadamente 20 | Considere 2^N, mas estime o custo por estado |
| N pequeno, K fixo / todos os pares ou trios | [Nested loops / complete search](exhaustive-search.md#pares) |

## NÃO DECORE APENAS AS FRASES

**Se x funciona, o que acontece com x+1? E x-1?**
Justifique a propriedade para todos os maiores/menores, não só para dois exemplos.
O padrão depende da pergunta de verify, não só da palavra “mínimo” ou “máximo”.

```text
F F F T T T → first true → funciona? salve e tente MENOR
T T T F F F → last true  → funciona? salve e tente MAIOR
F T F T F T → não monotônico → esses templates NÃO servem
```

“Produzir exatamente mid” pode alternar entre possível/impossível;
não assuma que é igual a “produzir pelo menos mid”.

<a id="nao-confundir"></a>
## NÃO CONFUNDIR — O QUE CADA TÉCNICA FAZ?

| Comparação | Diferença essencial |
|---|---|
| Two pointers × Binary search | Avançar índices controladamente × descartar metade do espaço de candidatos |
| Sliding window × Two sum | Trecho consecutivo, preserva ordem × dois elementos quaisquer em vetor ordenado |
| Sweep line × Prefix sum | Ordenar e processar eventos × acumular mudanças; podem ser usados juntos |
| Sweep line × Compression | Processar mudanças × transformar coordenadas em índices; compressão é auxiliar/opcional |
| Set × Multiset | Únicos × duplicatas; multiset.erase(valor) remove todas as ocorrências |
| Busca tradicional × Busca na resposta | “X está aqui?” × “se a resposta fosse X, funcionaria?” |
| Subsets × Permutations | Quem participa × em qual ordem participa; são espaços de escolhas diferentes |
| Nested loops × Subsets | Quantidade fixa de posições × cada elemento escolhido ou não |
| Greedy × Backtracking | Faz escolha e normalmente não explora alternativas × escolhe, explora, desfaz e tenta outra |

Greedy precisa de justificativa; backtracking só pode podar quando a alternativa descartada
não puder melhorar/completar a solução. Aqui é uma nota de reconhecimento, não um template profundo.

<a id="complexidades"></a>
## COMPLEXIDADES — CONSULTA RÁPIDA

N = elementos; R = quantidade de respostas inteiras candidatas; E = eventos;
A = ativos; P = permutações distintas; K = constante.

| Técnica / operação | Custo |
|---|---|
| Linear search | O(N) por busca; Q buscas = O(QN) |
| Binary search / bounds em vector | O(log N); sort prévio O(N log N) uma vez |
| Na resposta | O(custo de verify · log R); verify O(N) → O(N log R) |
| Two pointers / sliding window | Normalmente O(N), quando cada ponteiro se move O(N) vezes |
| Merge | O(N+M) |
| Sweep line com estado escalar / árvore balanceada | Normalmente O(E log E) + atualizações; estado que percorre todos os ativos pode custar mais |
| Coordinate compression | O(N log N) para preparar e mapear todos |
| Set / multiset: insert, find, remoção por chave única | O(log A); multiset.erase(valor) = O(log A + removidos) |
| Menor / maior em set ou multiset | O(1) via begin/rbegin; exige não vazio |
| Subsets | 2^N estados; O(N · 2^N) se percorrer N bits por estado |
| Permutations | P <= N! estados; O(N · P) para gerar/avaliar/imprimir cada ordem completa |
| Pares / trios | O(N²) / O(N³) |
| K loops aninhados | O(N^K), para K fixo |

O(N!) conta ordens, não ignora o custo de construir/avaliar cada uma.
Para N/R/E pequenos, interprete o log como log(tamanho+1); inclua memória e saída na estimativa.

<a id="armadilhas"></a>
## ARMADILHAS — ÚLTIMA CONFERÊNCIA

| Tema | Confira |
|---|---|
| Binary search | first/last, lado de true, ans salvo, mid ± 1, overflow e limites com a resposta |
| Two pointers | ponteiro correto; sort no par, nunca na janela original; condição monotônica |
| Sweep line | sort, regra de empate, evento de saída, R ou R+1; não alocar por coordenada gigante |
| Estado ativo | contador para quantos; duplicatas não cabem em set de valores; erase(iterator) para uma |
| Compression | sort + unique + erase; converter por lower_bound; índices preservam ordem, não distância |
| Bitmask | mask != bit; tipo do shift; shift fora do tipo é inválido; 2^N cresce explosivamente |
| Permutations | começar ordenado, usar do/while, estimar N! e o volume da saída |

Os [templates de busca](binary-search.md) e de [varredura](sweep-line.md) ficam apenas nos guias;
esta tabela não cria uma segunda implementação para desatualizar.
