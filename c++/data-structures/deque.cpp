// Aplicação: inserir/remover nas duas pontas. Sem entrada; saída: 1 3 / 2.
// Operações nas pontas e acesso indexado O(1); memória O(N).
// Confira empty() antes de front/back/pop; não use iteradores antigos após mutações.
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
}
