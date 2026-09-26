// Aplicação: ordenar valores mantendo os índices originais.
// Sem entrada; saída: 1:1 / 3:0 / 3:2.
// Pair compara first e, em empate, second; tempo O(N log N), memória O(N).
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int main() {
    std::vector<int> values{3, 1, 3};
    std::vector<std::pair<int,int>> indexed;
    for (int i = 0; i < int(values.size()); ++i) indexed.emplace_back(values[i], i);
    std::sort(indexed.begin(), indexed.end());
    for (auto [value, index] : indexed) std::cout << value << ':' << index << '\n';
}
