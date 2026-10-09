# Prefix sum ou sliding window?

[Consulta geral](../../README.md) · [Prefix sum](#prefix-sum) · [Janela](#sliding-window)

| Pedido | Use / código | Condição |
|---|---|---|
| Muitas somas [L,R] | [Prefix sum](prefix-sum.cpp) | dados fixos; negativos permitidos |
| Melhor soma de K consecutivos | [Janela fixa](sliding-window-fixed.cpp) | 1 <= K <= N; negativos permitidos |
| Maior trecho com soma <= S | [Janela variável](../search/two-pointers.md#janela) | não negativos; S >= 0 |
| Maior trecho com até K distintos | [Janela + frequências](sliding-window-distinct.cpp) | K >= 0; negativos permitidos |
| Somar em intervalos, só ver o final | [Diferenças](difference-array.cpp) | não há consultas intercaladas |

Trecho é **consecutivo**, não pode pular posições. Recortes dentro de main com o [template](../template.cpp).

<a id="prefix-sum"></a>
## 1. Prefix sum: guarde o que já foi somado

**Use:** array não muda e preciso de várias somas/contagens em intervalos.

**Fórmula:** p[i+1] = p[i] + v[i]; soma inclusiva base 0 de [L,R] = **p[R+1] - p[L]**.

<!-- example: prefix-sum -->
```cpp
vector<int> v{2, 3, 5, 1}; vector<long long> p(v.size() + 1, 0);
for (int i = 0; i < int(v.size()); i++) p[i+1] = p[i] + v[i];
int l = 1, r = 2; // base zero, inclusivo
cout << p[r+1] - p[l]; // 8
```

**Custo:** O(N) construção, O(1) consulta, O(N) memória.

**Cuidado:** posição extra e zero inicial; somas em long long. Aceita negativos.
Se atualizar o array, o prefixo fica desatualizado. Mínimo não funciona por subtração.
Atualização pontual + somas online → [Fenwick](../../QUAL-ESTRUTURA-USAR.md#op19).

<details>
<summary>Entender melhor: construção e por que R+1</summary>

### Ideia simples

Guarde quanto foi somado antes de cada posição. A soma de um intervalo é
o acumulado até o fim menos o acumulado antes do começo, sem varrer o trecho.

### Exemplo de contest

Valores: [2, 3, 5, 1].

| i | prefixo[i] | Significado |
|---|---:|---|
| 0 | 0 | nenhum elemento |
| 1 | 2 | primeiro elemento |
| 2 | 5 | primeiros dois |
| 3 | 10 | primeiros três |
| 4 | 11 | todos |

Construção: `prefixo[i+1] = prefixo[i] + valores[i]`.
Para somar índices [1,2], queremos 3+5:
`prefixo[3] - prefixo[1] = 10 - 2 = 8`.

Fórmula para índices base zero inclusivos:
`soma(L,R) = prefixo[R+1] - prefixo[L]`.


O prefixo p[R+1] inclui até R. Retiramos p[L], que contém tudo antes de L.

</details>

<a id="sliding-window"></a>
## Sliding window: movimentação não é a estrutura

**Use:** o trecho se move e consigo atualizar o que entra/sai sem recalcular tudo.

**Janela fixa:** tamanho K. Soma nova = soma antiga - saiu + entrou.

<!-- example: sliding-window -->
```cpp
vector<int> v{2, 1, 5, 1}; int k = 3; // 1 <= k <= size()
long long soma = accumulate(v.begin(), v.begin() + k, 0LL);
cout << soma << ' ';
for (int r = k; r < int(v.size()); r++) {
    soma -= v[r-k]; soma += v[r]; cout << soma << ' '; // 8 7
}
```

**Custo:** soma fixa O(N), O(1) estado extra; entrada guardada O(N).

**Cuidado:** 1 <= K <= N; aceita negativos. Para maior soma, inicialize o melhor com a primeira janela, não com zero.
Não ordene: perderia os trechos originais.

| Quero dentro da janela | Estado | Template |
|---|---|---|
| Soma | acumulador | [maior soma fixa](sliding-window-fixed.cpp) |
| Distintos/frequências | mapa de contagens | [até K distintos](sliding-window-distinct.cpp) |
| Mínimo/máximo | deque monotônica de índices | [recorte](patterns.md#monotonic-deque) |
| Mediana | dois multisets + rebalanceamento | [recorte de inserção](../data-structures/README.md#median) |

<details>
<summary>Entender melhor: o que muda a cada avanço</summary>

### Ideia simples

A janela diz quais posições estão dentro do trecho atual. A informação mantida
depende da pergunta: acumulador para soma, mapa para frequência, deque monotônica
para extremos, dois multisets para mediana.

### Exemplo de contest

[2,1,5,1], K=3: [2,1,5] soma 8 → sai 2, entra 1 → [1,5,1] soma 7.
Não some os três itens novamente. Para máximo, porém, remover o antigo máximo
pede saber quem ainda pode ser o próximo: só uma variável não basta.

</details>

## Janela variável — expande, depois corrige

[Template completo](../search/two-pointers.md#janela): entra pela direita; enquanto inválida,
sai pela esquerda; com janela válida, registra o tamanho.

**Soma <= S:** exige não negativos e S >= 0. [5,-4], S=1 mostra por que negativos quebram o descarte.

**Até K distintos:** mantenha frequências; apague a chave quando virar zero. Essa condição aceita negativos.
Custo: soma O(N); frequências com hash O(N) médio, O(N²) pior caso.

<details>
<summary>Entender melhor: execução das janelas fixa e variável</summary>

## 2. Janela fixa: sai um, entra outro

Valores [2,1,5,1,3], K=3:

| Janela | Atualização | Soma |
|---|---|---:|
| [2,1,5] | soma inicial | 8 |
| [1,5,1] | 8 - 2 + 1 | 7 |
| [5,1,3] | 7 - 1 + 3 | 9 |

O resultado máximo é 9. Não somamos os K elementos novamente:
`soma -= valores[direita-K]; soma += valores[direita];`.

Comparar todas as janelas recalculando seria O(NK); reaproveitar a soma dá O(N).
O estado da janela é O(1), mas o exemplo guarda o vetor O(N).
Negativos são permitidos. Inicialize o máximo com a primeira soma, não zero.
Exige 1 <= K <= N.

Prefix sum também resolveria: soma de cada janela em O(1).
Janela fixa evita precisar do vetor adicional de prefixos.

Exercício: [-5,-2,-7], K=2. Maior soma? **-7**, não zero.

## 3. Janela variável: amplia e encolhe

Queremos o maior trecho com soma <= 7 em [2,1,5,1,3].

| Passo | Janela após ajustar | Soma | Tamanho |
|---|---|---:|---:|
| entra 2 | [2] | 2 | 1 |
| entra 1 | [2,1] | 3 | 2 |
| entra 5; soma 8, sai 2 | [1,5] | 6 | 2 |
| entra 1 | [1,5,1] | 7 | 3 |
| entra 3; soma 10, saem 1 e 5 | [1,3] | 4 | 2 |

Resposta: 3. A direita avança; enquanto a soma passa do limite, a esquerda avança.
Cada valor entra e sai no máximo uma vez: O(N), mesmo com while dentro do for.

**Pré-condição deste exemplo: valores não negativos e limite >= 0.**
Com negativos, remover da esquerda pode aumentar a soma e um prefixo inválido
pode se tornar válido depois. Ex.: [5,-4], limite 1: o trecho inteiro é válido,
mas a estratégia descartaria o 5 cedo demais.

Se nenhum elemento couber, resposta 0. Zeros funcionam. Outros problemas
podem exigir janela com frequências ou outra condição; não copie este critério
de soma para qualquer problema com a palavra “janela”.

Exercício: [1,2,1,1], limite 3. Maior tamanho? **2**.

</details>

## Prefixos para contar / diferenças para atualizar

**Contar pares em [L,R]:** transforme cada valor em 1 se par, 0 senão; consulte prefixos.
**Média:** soma / tamanho, convertendo para double antes de dividir.
**Adicionar X a [L,R] e ver só o final:** diferença[L] += X; diferença[R+1] -= X;
um prefixo reconstrói os incrementos. Reserve N+1 posições. [Código](difference-array.cpp).

Janela fixa também pode usar prefixos; acumulador evita o vetor extra.
“Sliding window” é janela deslizante; slicing é extrair um trecho, outra coisa.
