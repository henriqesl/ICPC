# Matemática Python

As propriedades continuam em [math-reference.cpp](../../c++/math/math-reference.cpp);
aqui estão APIs e [implementações executáveis](number_theory.py).

```python
import math
math.gcd(12, 18)     # 6
math.lcm(12, 18)     # 36; Python >= 3.9
math.sqrt(10)        # aproximação float
math.isqrt(10)       # 3, raiz inteira exata para n >= 0
math.ceil(2.3)       # 3
math.floor(-2.3)     # -3
math.factorial(5)    # 120; exige inteiro >= 0
pow(2, 10, 1000)    # 24; exponenciação modular sem construir 2**10 primeiro
n = 49
perfect_square = n >= 0 and math.isqrt(n) ** 2 == n
```

Use isqrt para limites inteiros; sqrt pode arredondar números grandes.
Para a,b inteiros positivos, divisão com teto: (a+b-1)//b evita float.
pow(a,b,mod), com b >= 0 e mod > 0, faz O(log b) multiplicações modulares;
o custo de cada uma depende do tamanho dos números.
MDC via Euclides tem O(log min(|a|,|b|)) passos para entradas não nulas;
factorial e suas saídas crescem rapidamente. Não trate todas as funções math como O(1).
A versão local de lcm trata zero e sinais e atende Python anterior ao 3.9.
[Referência oficial](https://docs.python.org/3/library/math.html).
