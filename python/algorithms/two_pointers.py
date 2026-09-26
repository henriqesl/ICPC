"""Encontra dois índices distintos cuja soma é alvo, em lista ORDENADA.
Se soma é pequena, aumentar esquerda pode aumentá-la; se grande, reduzir direita.
Cada ponteiro anda no máximo N vezes: O(N) tempo, O(1) espaço auxiliar.
Também aceita negativos; não altera a lista. Ordenar antes mudaria os índices!
Entrada: N, valores ordenados e alvo. Ex.: 4 1 3 5 8 9. Saída: 0 3.
Saída -1 se não existir. Não resolve contagem de pares nem qualquer janela.
"""
import sys


def pair_sum(values, target):
    left, right = 0, len(values) - 1
    while left < right:
        total = values[left] + values[right]
        if total == target:
            return left, right
        if total < target:
            left += 1
        else:
            right -= 1
    return None


def main():
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(tokens)
    values = [next(tokens) for _ in range(n)]
    answer = pair_sum(values, next(tokens))
    print(*answer) if answer is not None else print(-1)


if __name__ == "__main__":
    main()
