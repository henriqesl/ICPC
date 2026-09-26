# Debugging e erros comuns

```python
import sys
values = [2, 4]
print(repr(values), file=sys.stderr)  # repr evidencia espaços e escapes em strings
assert len(values) == 2              # hipótese durante o treino
breakpoint()                        # pausa ANTES de continuar
total = sum(values)
```

No pdb: `p values` inspeciona; `n` avança; `s` entra na função;
`c` continua; `q` sai. breakpoint não deve ficar na submissão.
assert pode ser desativado com python -O; não o use como validação indispensável.

No VS Code, instale as extensões Python/Python Debugger da Microsoft,
selecione o interpretador, marque um breakpoint e execute “Python Debugger:
Debug Python File” pela paleta. Inspecione Variables/Watch ou passe o mouse na
variável; F10 avança, F5 continua na sessão. A entrada vai ao terminal.

| Erro | Incorreto | Correção |
|---|---|---|
| Fim exclusivo | `range(n+1)` para acessar lista de tamanho n | `range(n)` |
| Remover enquanto itera | `for x in v: v.remove(x)` | `v = [x for x in v if x != alvo]` |
| Retorno do sort | `v = v.sort()` | `v.sort()` ou `v = sorted(v)` |
| KeyError | `freq[x] += 1` sem chave | `freq[x] = freq.get(x, 0) + 1` |
| IndexError | `v[len(v)]` | `v[-1]` se v não vazio |
| Pilha vazia | `stack[-1]` sem verificar | `if stack: top = stack[-1]` |
| Fila lenta | `v.pop(0)` repetido | `deque.popleft()` |
| Aliasing | `b = a; b.append(1)` altera a | `b = a.copy()`, cópia rasa |
| Matriz compartilhada | `[[0]*m]*n` | `[[0]*m for _ in range(n)]` |

Na matriz errada, todas as linhas apontam para a mesma lista: alterar [0][0]
altera todas as linhas. A compreensão cria uma lista nova por linha.
A cópia rasa ainda compartilha objetos internos; para matriz de inteiros,
`[row[:] for row in matrix]` copia também cada linha.

Teste vazio quando permitido, um elemento, duplicatas, negativos, limites e
valor ausente. Antes de enviar, remova prints de diagnóstico e breakpoints.
