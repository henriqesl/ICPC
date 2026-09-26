"""Divisores/primalidade para N moderado: testar até isqrt(N).
Tempo O(sqrt(N)); divisors usa O(D) memória, is_prime O(1) auxiliar.
MDC/MMC seguem Euclides; inteiros grandes têm custos maiores por operação.
Entrada: dois inteiros positivos a b.
Ex.: 12 18. Saída: 1 2 3 4 6 12 / False / 6 36.
"""
from math import gcd, isqrt
import sys


def divisors(n):
    if n < 1:
        raise ValueError("n deve ser positivo")
    small, large = [], []
    for d in range(1, isqrt(n) + 1):
        if n % d == 0:
            small.append(d)
            if d * d != n:  # raiz não aparece duas vezes
                large.append(n // d)
    return small + large[::-1]


def is_prime(n):
    if n < 2:
        return False
    if n % 2 == 0:
        return n == 2
    return all(n % d for d in range(3, isqrt(n) + 1, 2))


def lcm(a, b):
    # Alternativa a math.lcm, disponível desde Python 3.9.
    return abs(a // gcd(a, b) * b) if a and b else 0


def main():
    a, b = map(int, sys.stdin.read().split())
    print(*divisors(a))
    print(is_prime(a))
    print(gcd(a, b), lcm(a, b))


if __name__ == "__main__":
    main()
