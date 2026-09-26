"""Busca linear/binária: c++/algorithms/searching/binary-search-main.cpp (raiz icpc).
first_at_least exige ordem crescente (não estrita), retorna len(values) se ausente.
Busca binária O(log N)/O(1); linear O(N)/O(1). Leitura usa O(N).
Entrada: N, N valores ORDENADOS e alvo. Ex.: 4 1 3 3 8 3. Saída: 1.
"""
from bisect import bisect_left
import sys


def linear_search(values, target):
    for i, value in enumerate(values):
        if value == target:
            return i
    return -1


def first_at_least(values, target):
    return bisect_left(values, target)


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    values = [next(tokens) for _ in range(n)]
    index = first_at_least(values, next(tokens))
    print(index if index < n else -1)


if __name__ == "__main__":
    main()
