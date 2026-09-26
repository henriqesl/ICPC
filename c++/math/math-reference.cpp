/*
    REFERÊNCIA RÁPIDA DE MATEMÁTICA

    Aplicações executáveis: number-theory.cpp e modular-power.cpp.
    Índice e limitações: README.md.

    PARIDADE
        par + par = par
        ímpar + ímpar = par
        par + ímpar = ímpar

    TEORIA DOS NÚMEROS
        gcd(a, b) calcula o MDC.
        lcm(a, b) = a / gcd(a, b) * b.
        A fórmula acima exige gcd != 0 e resultado representável.
        Se algum argumento é zero, o MMC é zero; não divida 0 por 0.
        Para testar se x é primo, teste divisores até sqrt(x).
        Um quadrado perfeito possui quantidade ímpar de divisores.

    TIPOS
        Use long long quando somas ou produtos puderem passar de 2 * 10^9.
        Cuidado com overflow antes de aplicar módulo ou imprimir o resultado.

    PROBABILIDADE
        Em casos equiprováveis:
        probabilidade = casos favoráveis / casos possíveis.
*/
