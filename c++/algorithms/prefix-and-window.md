# Prefix sum ou sliding window?

[Mapa geral](../../MAPA-DE-RESOLUCAO.md) · [Prefix sum](#prefix-sum) · [Sliding window](#sliding-window)

Os recortes vão dentro de `main()`, com o [template](../template.cpp).

O nome é **sliding window** (janela deslizante). Slicing é extrair um trecho
da sequência; não é a mesma técnica. A janela evita recalcular o trecho inteiro.

| O problema pede | Use | Arquivo |
|---|---|---|
| Muitas consultas de soma [L,R] em dados fixos | Prefix sum | [prefix-sum.cpp](prefix-sum.cpp) |
| Melhor soma entre trechos de exatamente K consecutivos | Janela fixa | [sliding-window-fixed.cpp](sliding-window-fixed.cpp) |
| Maior trecho com soma <= limite, valores não negativos | Janela variável | [sliding-window-variable.cpp](sliding-window-variable.cpp) |
| Maior trecho com até K valores diferentes | Janela com frequências | [sliding-window-distinct.cpp](sliding-window-distinct.cpp) |
| Somar incrementos a intervalos e ver resultado só no final | Vetor de diferenças | [difference-array.cpp](difference-array.cpp) |

Trecho/subarray é **contíguo**: [2,1,5] é trecho de [2,1,5,1,3]; escolher
[2,5,3] pulando posições não é.

<a id="prefix-sum"></a>

## 1. Prefix sum: guarde o que já foi somado

### Quando pensar nisso?

- “O array não muda e tenho muitas consultas de soma [L,R].”
- “Preciso contar uma propriedade em vários intervalos fixos.”

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

### Operações que preciso lembrar

<!-- example: prefix-sum -->
```cpp
vector<int> v{2, 3, 5, 1}; vector<long long> p(v.size() + 1, 0);
for (int i = 0; i < int(v.size()); i++) p[i+1] = p[i] + v[i];
int l = 1, r = 2; // base zero, inclusivo
cout << p[r+1] - p[l]; // 8
```

**Por que R+1?** prefixo[3] contém as posições 0,1,2. Depois retiramos o que
vem antes de L. O zero inicial permite consultar L=0 sem tratamento especial.

### Complexidade

Construção O(N), cada consulta O(1), espaço O(N). Negativos funcionam.
Erros frequentes: esquecer posição extra, confundir índices base 0/1,
usar int para somas grandes e modificar os valores sem refazer prefixos.

Exercício: [4,-2,7,1], soma de [1,3]? **6**.

### Não confundir com

Sliding window reaproveita um trecho que se move. Prefixos consultam quaisquer
intervalos fixos. Não substitua soma por mínimo: subtrair não desfaz um mínimo.
Dados mudando + somas online → [Fenwick](../../QUAL-ESTRUTURA-USAR.md#op19).

<a id="sliding-window"></a>

## Sliding window: movimentação não é a estrutura

### Quando pensar nisso?

- “Considero todo trecho de K elementos consecutivos.”
- “O segmento cresce pela direita e encolhe pela esquerda.”

### Ideia simples

A janela diz quais posições estão dentro do trecho atual. A informação mantida
depende da pergunta: acumulador para soma, mapa para frequência, deque monotônica
para extremos, dois multisets para mediana.

### Exemplo de contest

[2,1,5,1], K=3: [2,1,5] soma 8 → sai 2, entra 1 → [1,5,1] soma 7.
Não some os três itens novamente. Para máximo, porém, remover o antigo máximo
pede saber quem ainda pode ser o próximo: só uma variável não basta.

### Operações que preciso lembrar

<!-- example: sliding-window -->
```cpp
vector<int> v{2, 1, 5, 1}; int k = 3; // 1 <= k <= size()
long long soma = accumulate(v.begin(), v.begin() + k, 0LL);
cout << soma << ' ';
for (int r = k; r < int(v.size()); r++) {
    soma -= v[r-k]; soma += v[r]; cout << soma << ' '; // 8 7
}
```

### Complexidade

Soma fixa: O(N) total, O(1) por avanço. Frequência com hash: O(N) médio,
O(N²) pior caso. Mediana com dois multisets: O(N log K).
Deque monotônica para extremos: O(N). Entrada guardada usa O(N) memória.

### Não confundir com

Janela não garante algoritmo linear. Pergunte **o que consultar dentro dela**:

| Consulta | Estado | Detalhes |
|---|---|---|
| Soma | acumulador | [janela fixa](sliding-window-fixed.cpp) |
| Frequência/distintos | mapa de contagens | [até K distintos](sliding-window-distinct.cpp) |
| Máximo/mínimo | deque monotônica de índices | [padrão](patterns.md#monotonic-deque) |
| Mediana | dois multisets + rebalanceamento | [padrão](../data-structures/README.md#median) |

Janela variável também usa two pointers, mas é preciso justificar o descarte.
Para soma limitada, a versão abaixo exige **não negativos**; já a janela fixa
de soma aceita negativos. Não ordene a entrada: perderia os trechos originais.

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

## 4. Outra condição de janela: até K distintos

Em [1,2,1,3], com K=2, o trecho [1,2,1] tem três posições mas só dois valores.
Use um mapa com as frequências dentro da janela. Ao entrar o 3, há três chaves:
avance a esquerda até restarem no máximo duas.
Quando uma frequência chegar a zero, apague a chave; caso contrário size()
continuará contando um valor que já saiu. Essa variante aceita negativos.

## 5. Prefixos para contar e diferenças para atualizar

Para contar pares em [L,R], transforme cada valor em 1 se for par e 0 caso
contrário, depois use os mesmos prefixos. Ex.: [2,3,6] vira [1,0,1].
Para média, divida a soma pelo tamanho convertendo antes para double.
Não funciona substituir soma por mínimo: não há uma subtração que remova o
mínimo de um prefixo e revele o mínimo de outro intervalo.

Se o pedido é adicionar 10 a [L,R] muitas vezes e só imprimir os valores finais,
marque +10 em L e -10 em R+1 num vetor extra de tamanho N+1. Um prefixo dessas
alterações reconstrói o incremento de cada posição. Veja difference-array.cpp.
