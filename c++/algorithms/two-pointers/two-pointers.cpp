// Dois índices distintos com soma alvo, vetor crescente.
// Entrada: N, N valores e alvo. Ex.: 4 1 3 5 8 9 -> 0 3; ausente -> -1.
// Se a soma é pequena, avance esquerda; se grande, recue direita.
// Cada ponta anda no máximo N vezes: O(N), espaço auxiliar O(1).
// Negativos são permitidos. Não ordene se precisa preservar índices originais.
// Valores e soma devem caber em long long. Não conta todos os pares.
#include <iostream>
#include <utility>
#include <vector>
std::pair<int,int> pair_sum(const std::vector<long long>& v, long long target) {
    int left = 0, right = int(v.size()) - 1;
    while (left < right) {
        long long total = v[left] + v[right];
        if (total == target) return {left, right};
        if (total < target) ++left;
        else --right;
    }
    return {-1, -1};
}
int main() {
    int n; std::cin >> n;
    std::vector<long long> v(n);
    for (auto& x : v) std::cin >> x;
    long long target; std::cin >> target;
    auto [i,j] = pair_sum(v, target);
    if (i == -1) std::cout << -1 << '\n';
    else std::cout << i << ' ' << j << '\n';
}
