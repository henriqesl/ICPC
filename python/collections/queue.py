"""FIFO: mesma aplicação de c++/data-structures/queue/queue-example.cpp (raiz icpc).
Entrada: N e N nomes sem espaços. Ex.: 2 Ana Bia. Saída: Ana / Bia.
Tempo O(N), memória O(N); popleft evita deslocar a fila inteira.
"""
from collections import deque
import sys


def main():
    tokens = iter(sys.stdin.read().split())
    n = int(next(tokens))
    queue = deque(next(tokens) for _ in range(n))
    while queue:
        print(queue.popleft())


if __name__ == "__main__":
    main()
