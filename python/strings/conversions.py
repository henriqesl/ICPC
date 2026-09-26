"""Aplicação: frequência por letra/dígito e transformação de texto.
Demonstração sem entrada; saída: 3 4 7 d / abc / 123.
Conversões de um caractere O(1); ordenação do texto O(N log N).
"""


def letter_position(c):
    if len(c) != 1 or not 'a' <= c <= 'z':
        raise ValueError("esperada uma letra de a a z")
    return ord(c) - ord('a')


def main():
    print(letter_position('d'), letter_position('d') + 1, int('7'), chr(100))
    print("".join(sorted("Cab".lower())))
    print(str(int("00123")))


if __name__ == "__main__":
    main()
