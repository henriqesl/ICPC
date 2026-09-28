# Prefix sum ou sliding window?

O nome é **sliding window** (janela deslizante). Slicing é extrair um trecho
da sequência; não é a mesma técnica. A janela evita recalcular o trecho inteiro.

| O problema pede | Use | Arquivo |
|---|---|---|
| Muitas consultas de soma [L,R] em dados fixos | Prefix sum | [prefix-sum.cpp](prefix-sum.cpp) |
| Melhor soma entre trechos de exatamente K consecutivos | Janela fixa | [sliding-window-fixed.cpp](sliding-window-fixed.cpp) |
| Maior trecho com soma <= limite, valores não negativos | Janela variável | [sliding-window-variable.cpp](sliding-window-variable.cpp) |

Trecho/subarray é **contíguo**: [2,1,5] é trecho de [2,1,5,1,3]; escolher
[2,5,3] pulando posições não é.

## 1. Prefix sum: guarde o que já foi somado

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

**Por que R+1?** prefixo[3] contém as posições 0,1,2. Depois retiramos o que
vem antes de L. O zero inicial permite consultar L=0 sem tratamento especial.

Construção O(N), cada consulta O(1), espaço O(N). Negativos funcionam.
Erros frequentes: esquecer posição extra, confundir índices base 0/1,
usar int para somas grandes e modificar os valores sem refazer prefixos.

Exercício: [4,-2,7,1], soma de [1,3]? **6**.

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
