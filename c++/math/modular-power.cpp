// POTÊNCIA MODULAR: a elevado a b, com resto mod, sem construir a potência.
// Entrada: a b mod. Ex.: 2 10 1000 -> 24.
// Exige a,b >= 0 e 1 <= mod <= 10^9; produtos cabem em long long.
// Tempo O(log b), memória O(1).
#include <iostream>
using namespace std;

int main() {
    long long base, expoente, modulo;
    cin >> base >> expoente >> modulo;
    if (base < 0 || expoente < 0 || modulo < 1 || modulo > 1000000000LL) return 1;

    long long resposta = 1 % modulo;
    base %= modulo;
    while (expoente > 0) {
        if (expoente % 2 == 1) { // expoente ímpar: usa uma cópia da base
            resposta = resposta * base % modulo;
        }
        base = base * base % modulo; // quadrado da base
        expoente /= 2;
    }
    cout << resposta << '\n';
}
