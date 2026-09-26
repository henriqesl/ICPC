# Strings Python

Strings são imutáveis; operações produzem resultados novos. [Exemplo executável](../strings/conversions.py).

| Operação | Exemplo |
|---|---|
| Índice / slice | `"abc"[0] == "a"`; `"abcd"[1:3] == "bc"`; `"abc"[::-1] == "cba"` |
| lower / upper | `"Ab".lower() == "ab"`; `"Ab".upper() == "AB"` |
| strip | `"  oi\n".strip() == "oi"`; remove espaços também |
| split | `"a  b".split() == ["a", "b"]` |
| join | `"-".join(["a", "b"]) == "a-b"` |
| replace | `"banana".replace("a", "o") == "bonono"` |
| find | `"banana".find("na") == 2`; ausente retorna -1 |
| count | `"aaaa".count("aa") == 2`; não conta sobreposições |
| startswith / endswith | `"abc".startswith("ab")`; `"abc".endswith("bc")` |
| Comparação | `"ab" < "ac"` lexicográfica; diferencia maiúsculas |
| Ordenar caracteres | `"".join(sorted("cab")) == "abc"` |

Índice é O(1); slice copia O(K); transformações percorrem o texto.
Join custa o total de caracteres produzidos; ordenar custa O(N log N).
Buscas dependem do tamanho do texto e padrão, não são O(1).

## Conversões

```python
ord('a')            # 97
chr(97)             # 'a'
c = 'd'
ord(c) - ord('a')   # 3, base zero
ord(c) - ord('a') + 1 # 4, base um
chr(ord('a') + 3)   # 'd'
int('7')           # 7
ord('7') - ord('0') # 7, somente dígitos ASCII
int("123")         # 123; texto inválido gera ValueError
str(123)           # "123"
```

ord exige um único caractere. Posição no alfabeto pressupõe 'a'..'z';
não aplique a acentos ou alfabetos diferentes.
