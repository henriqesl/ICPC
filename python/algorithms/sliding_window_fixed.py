"""Maior soma de K consecutivos: janela fixa, aceita negativos.
Entrada: N K e N valores; 5 3 2 1 5 1 3 -> 9.
Exige 1 <= K <= N. Tempo O(N), memória O(N) da entrada.
Ideia: soma inicial; a cada avanço, remove o que sai e soma o que entra.
"""
import sys


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(tokens), next(tokens)
    values = [next(tokens) for _ in range(n)]
    total = sum(values[:k])
    best = total  # zero daria resposta errada quando todas as somas são negativas
    for right in range(k, n):
        total -= values[right - k]
        total += values[right]
        best = max(best, total)
    print(best)


if __name__ == "__main__":
    main()
