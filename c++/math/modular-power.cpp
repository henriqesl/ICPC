// Potência modular a^b % mod. Entrada: a b mod. Ex.: 2 10 1000 -> 24.
// Exige a >= 0, b >= 0 e 1 <= mod <= 10^9.
// O(log b) tempo, O(1) memória; produto < 10^18 cabe em long long.
// Para módulos maiores, esta multiplicação precisa de outra implementação.
#include <iostream>
long long mod_pow(long long a, long long b, long long mod) {
    long long result = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) result = result*a % mod;
        a = a*a % mod;
        b /= 2;
    }
    return result;
}
int main() {
    long long a,b,mod; std::cin >> a >> b >> mod;
    if (a < 0 || b < 0 || mod < 1 || mod > 1000000000LL) return 1;
    std::cout << mod_pow(a,b,mod) << '\n';
}
