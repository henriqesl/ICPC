"""Prioridade máxima: equivalente a priority-queue-example.cpp.
Entrada: N e N inteiros. Ex.: 3 2 9 4. Saída: 9 4 2.
Construção O(N), remoções O(N log N), memória O(N).
Se todos os dados já existem e só quer ordenar, sorted é mais simples.
"""
import heapq
import sys


def descending(values):
    heap = [-x for x in values]
    heapq.heapify(heap)
    while heap:
        yield -heapq.heappop(heap)


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    print(*descending(next(tokens) for _ in range(n)))


if __name__ == "__main__":
    main()
