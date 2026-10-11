// GULOSO: máxima quantidade de atividades compatíveis, sem pesos.
// Entrada: n; n pares início fim (início < fim). Saída: quantidade.
// O(N log N) tempo, O(N) memória; fim == próximo início é permitido.
// Menor fim deixa mais espaço; não maximiza pagamento com pesos.
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
        atividades.push_back({fim, inicio}); // {fim,início}
    }
    sort(atividades.begin(), atividades.end()); // menor fim primeiro

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
}
