// Aplicação: primeiro índice exato em vetor sem ordenação.
// Entrada: N, N inteiros e alvo. Ex.: 3 8 1 8 8 -> 0; ausente -> -1.
// Busca O(N), O(1) auxiliar; vetor usa O(N).
#include <iostream>
#include <vector>
int linear_search(const std::vector<int>& v, int target) {
    for (int i = 0; i < int(v.size()); ++i) if (v[i] == target) return i;
    return -1;
}
int main() {
    int n, target; std::cin >> n;
    std::vector<int> v(n);
    for (int& x : v) std::cin >> x;
    std::cin >> target;
    std::cout << linear_search(v, target) << '\n';
}
