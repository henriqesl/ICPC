"""Aplicação: presença, distintos e elementos comuns.
Operações individuais O(1) médio; conjuntos completos usam O(N+M) memória.
Demonstração sem entrada: [2] / [1, 2, 3] / [1].
"""


def main():
    a, b = {1, 2, 2}, {2, 3}
    a.add(4)
    a.remove(4)  # exige presença
    a.discard(99)  # ausente é permitido
    print(sorted(a & b))
    print(sorted(a | b))
    print(sorted(a - b))


if __name__ == "__main__":
    main()
