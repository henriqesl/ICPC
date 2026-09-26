"""Seleciona quantidade máxima de intervalos sem sobreposição.
Pré-condições: início < fim, mesmo peso; fim == próximo início é permitido.
Ordene pelo fim: trocar a primeira escolha pela que termina antes nunca
reduz o espaço disponível para as seguintes. Repita esse argumento.
Não serve para maximizar pesos; isso exige outra estratégia.
Tempo O(N log N), memória O(N).
Entrada: N e N pares início fim. Ex.: 3 0 2 1 4 2 3. Saída: 2.
"""
import sys


def select_intervals(intervals):
    chosen = []
    last_end = None
    for start, end in sorted(intervals, key=lambda interval: interval[1]):
        if last_end is None or start >= last_end:
            chosen.append((start, end))
            last_end = end
    return chosen


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    intervals = [(next(tokens), next(tokens)) for _ in range(n)]
    print(len(select_intervals(intervals)))


if __name__ == "__main__":
    main()
