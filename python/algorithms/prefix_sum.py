"""Intervalos imutáveis: c++/algorithms/prefix-sum/prefix-sum-main.cpp (raiz icpc).
Construção O(N), consulta O(1), memória O(N), contando inteiros como custo fixo.
Entrada: N, valores, Q e Q pares l r inclusivos (base zero).
Ex.: 3 2 -1 4 2 0 2 1 1. Saída: 5 / -1.
"""
import sys


def build_prefix(values):
    prefix = [0]
    for value in values:
        prefix.append(prefix[-1] + value)
    return prefix


def range_sum(prefix, left, right):
    if not 0 <= left <= right < len(prefix) - 1:
        raise ValueError("intervalo inválido")
    return prefix[right + 1] - prefix[left]


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    prefix = build_prefix(next(tokens) for _ in range(n))
    for _ in range(next(tokens)):
        print(range_sum(prefix, next(tokens), next(tokens)))


if __name__ == "__main__":
    main()
