# Matemática C++17

[Implementação](number-theory.cpp): divisores ordenados, primalidade e MDC/MMC.
Use tentativa de divisores para N moderado; O(sqrt(N)) pode ser inviável para
inteiros próximos do limite de 64 bits.

[Potência modular](modular-power.cpp): O(log expoente), sem construir a potência
inteira. A implementação limita módulo a 10^9 para o produto caber em long long.

std::gcd e std::lcm vêm de <numeric>. lcm só pode ser usado quando o resultado
cabe no tipo; a implementação verifica o produto. abs(LLONG_MIN) não cabe.
Use d <= n/d para testar até a raiz sem overflow de d*d.
sqrt usa ponto flutuante; não confie somente em sqrt(n)==int(sqrt(n)) para
quadrados perfeitos enormes.

Paridade: soma igual dá par, diferente dá ímpar; produto só é ímpar se ambos forem.
Divisores vêm em pares d e n/d; quadrado perfeito tem um divisor desemparelhado.
Probabilidade equiprovável = favoráveis / possíveis, convertendo para double.
Esperança é linear: dois dados justos têm E = 3.5+3.5 = 7.
Permutações de N distintos: N!; combinações: N!/(K!(N-K)!).
Fatoriais estouram rápido: 20! cabe em long long de 64 bits, 21! não.
Essas fórmulas não são automaticamente implementações numericamente seguras.
