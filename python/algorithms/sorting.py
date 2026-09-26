"""Ordenação: mesma aplicação de c++/algorithms/sorting/sorting-example.cpp (raiz icpc).
sorted cria lista, list.sort altera no lugar e retorna None.
Ambas estáveis: empates preservam ordem anterior; key escolhe critério.
Tempo O(N log N), memória auxiliar até O(N).
Entrada: N e N valores. Ex.: 3 2 1 3. Saída: 1 2 3 / 3 2 1.
"""
import sys


def by_second(pairs):
    return sorted(pairs, key=lambda pair: pair[1])


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    values = [next(tokens) for _ in range(n)]
    print(*sorted(values))
    values.sort(reverse=True)
    print(*values)


if __name__ == "__main__":
    main()
