// Divisores, primalidade, MDC/MMC de inteiros positivos moderados.
// Entrada: a b positivos. Ex.: 12 18 -> 1 2 3 4 6 12 / false / 6 36.
// Divisores/primo O(sqrt(a)); memória O(D) divisores e O(1) primo.
// MMC sinaliza overflow em vez de multiplicar fora do limite.
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
std::vector<long long> divisors(long long n) {
    std::vector<long long> small, large;
    for (long long d = 1; d <= n/d; ++d) if (n%d == 0) {
        small.push_back(d);
        if (d != n/d) large.push_back(n/d);
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n%2 == 0) return n == 2;
    for (long long d = 3; d <= n/d; d += 2) if (n%d == 0) return false;
    return true;
}
int main() {
    long long a,b; std::cin >> a >> b;
    if (a <= 0 || b <= 0) return 1;
    for (auto d : divisors(a)) std::cout << d << ' ';
    std::cout << '\n' << std::boolalpha << is_prime(a) << '\n';
    long long g = std::gcd(a,b), reduced = a/g;
    std::cout << g << ' ';
    if (reduced > std::numeric_limits<long long>::max()/b) std::cout << "overflow";
    else std::cout << reduced*b;
    std::cout << '\n';
}
