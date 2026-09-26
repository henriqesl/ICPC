// Soma durante a leitura: não precisa guardar os valores.
// Entrada: N e N inteiros; exemplo: 4 1 2 3 4 -> saída: 10.
// Tempo O(N), memória O(1). N >= 0; soma e valores devem caber em long long.
#include <iostream>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    if (!(std::cin >> n)) return 0;
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        long long x; std::cin >> x;
        total += x;
    }
    std::cout << total << '\n';
}
