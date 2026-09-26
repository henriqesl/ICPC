// Máximo número de intervalos sem sobreposição, TODOS de mesmo peso.
// Entrada: N e N pares início fim. Ex.: 3 0 2 1 4 2 3 -> 2.
// Exige início < fim; fim igual ao próximo início é permitido.
// Escolher menor fim deixa pelo menos tanto espaço quanto qualquer primeira escolha:
// substitua a primeira escolha de uma solução ótima e repita o argumento.
// Não resolve intervalos com pesos. O(N log N) tempo, O(N) espaço (cópia).
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int max_intervals(std::vector<std::pair<long long,long long>> intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const auto& a, const auto& b) { return a.second < b.second; });
    int count = 0;
    long long last_end = 0;
    for (auto [start,end] : intervals) {
        if (count == 0 || start >= last_end) { ++count; last_end = end; }
    }
    return count;
}
int main() {
    int n; std::cin >> n;
    std::vector<std::pair<long long,long long>> intervals(n);
    for (auto& [start,end] : intervals) std::cin >> start >> end;
    std::cout << max_intervals(intervals) << '\n';
}
