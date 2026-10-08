# RECONHECIMENTO — do enunciado ao padrão

[Índice](README.md) · [FIRST TRUE](binary-search-on-answer.md#first-true) ·
[LAST TRUE](binary-search-on-answer.md#last-true)

## NECESSIDADE → TÉCNICA PROVÁVEL

| Frase / necessidade | Padrão provável | Pergunta que confirma |
|---|---|---|
| Existe x, sem ordem útil? | [Linear](linear-search.md) | Posso percorrer uma vez? Muitas consultas mudam a escolha? |
| Existe x em array ordenado? | [Binary search](binary-search.md) | A comparação permite descartar metade? |
| Primeiro >= x / primeiro > x | [lower / upper bound](bounds.md) | Quero posição-limite, não necessariamente igualdade? |
| Quantas vezes x aparece? | [upper − lower](bounds.md#contar) | Os iguais estão consecutivos em um vector ordenado? |
| “menor valor que permite…” | FIRST TRUE | Se x permite, qualquer maior também permite? |
| “menor tempo necessário…” | FIRST TRUE | Esperar mais nunca prejudica? |
| “menor capacidade suficiente…” | FIRST TRUE | Capacidade extra nunca impede a solução? |
| “minimize a maior…” | FIRST TRUE | Com limite máximo x, consigo uma solução? Aumentar relaxa o limite? |
| “maior valor possível…” | Normalmente LAST TRUE | Se x é possível, qualquer menor também é? |
| “maior distância mínima…” | LAST TRUE | Diminuir a distância exigida mantém a viabilidade? |
| “maior tamanho que ainda permite…” | LAST TRUE | Tamanhos menores continuam atendendo a necessidade? |
| “maximize o mínimo…” | LAST TRUE | Com mínimo exigido x, consigo uma solução? Diminuir relaxa a exigência? |

## NÃO DECORE APENAS AS FRASES

**Sempre pergunte: “Se x funciona, o que acontece com x+1? E com x-1?”**
Além desses vizinhos, justifique que a propriedade vale para todos os candidatos maiores/menores.
O padrão depende da pergunta feita por verify, não só da palavra “mínimo” ou “máximo”.

```text
F F F T T T → primeiro true → funciona? salve e tente MENOR
T T T F F F → último true   → funciona? salve e tente MAIOR
F T F T F T → não monotônico → estes templates NÃO servem
```

## IDEIA / EXEMPLOS NEUTROS

- **Minimizar o máximo:** “consigo manter a soma de cada grupo <= mid?”
  Aumentar mid relaxa a restrição → first true (para grupos do exemplo com não negativos).
- **Maximizar o mínimo:** “consigo manter cada distância entre escolhidos >= mid?”
  Diminuir mid relaxa a restrição → last true (se não houver regras adicionais que a quebrem).
- “Consigo produzir **exatamente** mid unidades?” pode alternar entre possível/impossível.
  Não assuma que é igual a “produzir **pelo menos** mid unidades”.

## TEMPLATE C++ / COMPLEXIDADE / ARMADILHAS

Use [FIRST TRUE](binary-search-on-answer.md#first-true) ou
[LAST TRUE](binary-search-on-answer.md#last-true) depois de definir verify e limites.
O custo é **O(custo de verify · log R)**; se verify = O(N), O(N log R).
Não precisa copiar os templates aqui: um link leva diretamente ao programa correspondente.

Antes de codar: consigo provar a monotonicidade? Meu teste é viável no tempo limite?
Os limites contêm a resposta? Há um caso “nenhum candidato funciona”?
