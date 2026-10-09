# Python 3 — consulta rápida

[Consulta geral](../README.md) · [Template](templates/template.py) · [C++ × Python](cheatsheets/cpp-python.md)

| Preciso... | Abra |
|---|---|
| Sintaxe e funções | [Quick Reference](cheatsheets/python.md) |
| Remover valor / encontrar índice | [Listas](cheatsheets/python-collections.md#listas), [exemplo](collections/lists.py) |
| Letras, dígitos, texto | [Strings](cheatsheets/python-strings.md), [exemplo](strings/conversions.py) |
| Distintos / frequências | [Sets](collections/sets.py), [Counter](collections/frequency.py) |
| Fila / pilha / prioridade | [Deque](collections/queue.py), [delimitadores](collections/balanced.py), [heap](collections/heap.py) |
| Leitura rápida | [I/O](basics/io.py) |
| Algoritmos e aplicações | [Índice](algorithms/README.md) |
| Somas em intervalos / melhor soma fixa / maior trecho limitado | [Prefix sum](algorithms/prefix_sum.py) · [janela fixa](algorithms/sliding_window_fixed.py) · [variável](algorithms/sliding_window_variable.py) (não negativos) |
| Primos, divisores, MDC | [Matemática](math/README.md) |
| Tempo e memória | [Performance](basics/performance.md) |
| Diagnosticar erro | [Debugging e erros comuns](debugging/README.md) |
| Começar uma solução | [Template](templates/template.py) |
| Equivalências C++ | [Comparação](cheatsheets/cpp-python.md) |

**Atenção:** set Python não mantém ordem; bisect exige lista ordenada.
Entrada com leitura completa só termina após EOF (ou entrada redirecionada).

<details>
<summary>Fora do contest: versões, execução, entrada e testes</summary>

C++17 continua principal. Referências e implementações usam apenas biblioteca
padrão. Exemplos funcionam em Python 3.8+; math.lcm exige 3.9, com alternativa
fornecida. Custos de algoritmos assumem inteiros de tamanho moderado.


As funções podem ser copiadas isoladamente. Os arquivos .py têm demonstração
protegida por `if __name__ == "__main__"`; podem ser importados sem ler entrada.
Cabeçalhos informam entrada, saída e limitações. lists.py, sets.py e conversions.py
rodam sem entrada; os demais exemplos leem o formato descrito no cabeçalho.
template.py é um esqueleto e termina sem saída.

Na raiz icpc:

```text
python python/collections/lists.py
python python/algorithms/searching.py
```

No segundo, digite `4 1 3 3 8 3` e sinalize EOF (Ctrl+Z e Enter no
Windows, Ctrl+D no Linux). Resultado: 1. Leitura completa espera EOF.
Também pode usar redirecionamento de arquivo no shell que o suporta ou
`Get-Content entrada.txt | python python/algorithms/searching.py` no PowerShell.

Testes: `python -B python/tests/test_library.py`.

</details>
