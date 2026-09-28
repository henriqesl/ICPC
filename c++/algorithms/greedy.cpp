// GULOSO: maior QUANTIDADE de intervalos compatíveis, sem pesos.
// Entrada: N e N pares início fim. Ex.: 3 0 2 1 4 2 3 -> 2.
// Início < fim; terminar quando outro começa é permitido.
// O(N log N) tempo, O(N) memória.
// Ideia: terminar antes deixa mais espaço. Trocar a primeira atividade de
// uma solução ótima pela de menor fim não impede as próximas escolhas.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> atividades;

    for (int i = 0; i < n; i++) {
        long long inicio, fim;
        cin >> inicio >> fim;
        atividades.push_back({fim, inicio}); // fim PRIMEIRO para ordenar sem função
    }
    sort(atividades.begin(), atividades.end()); // ordena pelo primeiro campo (fim)

    int quantidade = 0;
    long long ultimoFim = 0;
    for (const auto& atividade : atividades) {
        long long fim = atividade.first;
        long long inicio = atividade.second;
        if (quantidade == 0 || inicio >= ultimoFim) {
            quantidade++;
            ultimoFim = fim;
        }
    }
    cout << quantidade << '\n';
    // Se cada atividade paga um valor diferente, esta estratégia não maximiza pagamento.
}
