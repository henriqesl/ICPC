"""Entrada por tokens quando as quebras de linha não importam.
Use para somar N valores, mesmo distribuídos em várias linhas.
Entrada: 4\n1 2\n3 4\n. Saída: 10.
Tempo O(N), memória O(N) para a leitura completa; não usar em interativos.
Para economizar memória, processe linhas com sys.stdin.readline.
"""
import sys


def main():
    tokens = iter(sys.stdin.buffer.read().split())
    first = next(tokens, None)
    if first is None:
        return
    n = int(first)
    total = sum(int(next(tokens)) for _ in range(n))
    print(total)


if __name__ == "__main__":
    main()
