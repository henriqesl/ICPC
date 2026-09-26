"""Contagem: equivalente a c++/data-structures/map/frequency-map.cpp (raiz icpc).
Entrada: N e N inteiros. Ex.: 4 3 3 8 3. Saída: 3: 3 / 8: 1.
Contagem O(N) média; saída ordenada O(K log K); memória O(N+K) com leitura total.
"""
from collections import Counter
import sys


def frequencies(values):
    return Counter(values)


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    freq = frequencies(next(tokens) for _ in range(n))
    for value in sorted(freq):
        print(f"{value}: {freq[value]}")


if __name__ == "__main__":
    main()
