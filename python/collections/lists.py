"""Aplicação: localizar/remover valores e ordenar uma sequência.
find/index e remove O(N), append O(1) amortizado; sort O(N log N).
Demonstração sem entrada; saída: 0, [1, 3], [1, 3, 8] em três linhas.
"""


def first_index(values, target):
    # Evita fazer duas buscas (in seguido de index).
    for i, value in enumerate(values):
        if value == target:
            return i
    return -1


def main():
    values = [3, 1, 3]
    print(first_index(values, 3))
    values.remove(3)  # primeira ocorrência; exige presença
    print(values)
    values.append(8)
    values.sort()
    print(values)


if __name__ == "__main__":
    main()
