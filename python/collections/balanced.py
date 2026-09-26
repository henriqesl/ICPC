"""LIFO: equivalente a c++/data-structures/stack/balanced-parentheses.cpp (raiz icpc).
Entrada: uma linha; saída: balanceado ou desbalanceado.
Ex.: ([{}]) -> balanceado; ([)] -> desbalanceado.
Tempo O(N), espaço O(N). Ignora caracteres que não são delimitadores.
"""
import sys


def balanced(text):
    stack = []
    pairs = {')': '(', ']': '[', '}': '{'}
    for char in text:
        if char in '([{':
            stack.append(char)
        elif char in pairs:
            if not stack or stack.pop() != pairs[char]:
                return False
    return not stack


def main():
    print("balanceado" if balanced(sys.stdin.readline()) else "desbalanceado")


if __name__ == "__main__":
    main()
