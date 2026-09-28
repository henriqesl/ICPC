"""Maior trecho com soma <= limite, somente valores NÃO NEGATIVOS e limite >= 0.
Entrada: N limite e N valores; 5 7 2 1 5 1 3 -> 3.
Tempo O(N), memória O(N); cada elemento entra e sai no máximo uma vez.
Com negativos esta estratégia falha: [5,-4] com limite 1 é um contraexemplo.
"""
import sys


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n, limit = next(tokens), next(tokens)
    values = [next(tokens) for _ in range(n)]
    left = total = best = 0
    for right in range(n):
        total += values[right]
        while total > limit and left <= right:
            total -= values[left]
            left += 1
        best = max(best, right - left + 1)
    print(best)


if __name__ == "__main__":
    main()
