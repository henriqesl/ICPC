// DEQUE: inserir/remover nas duas pontas. Demo sem entrada: 1 3 / 2.
// Pontas/índice O(1), memória O(N). Confira empty antes de front/back/pop.
#include <deque>
#include <iostream>
int main() {
    std::deque<int> q{2};
    q.push_front(1);
    q.push_back(3);
    std::cout << q.front() << ' ' << q.back() << '\n';
    q.pop_front();
    q.pop_back();
    std::cout << q.front() << '\n';
    // q[i]/q.at(i): índice; at verifica limite. size/empty/clear disponíveis.
    // Mutações podem invalidar iteradores; memória não é contígua.
}
