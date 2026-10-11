// MAP: chave -> frequência; chaves em ordem.
// Entrada: n; n valores. Saída: chave: frequência; extremos ou "vazio".
// O(log D) por chave, O(D) memória; D distintos. m[x] cria ausente.
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> frequencia;

    for (int i = 0; i < n; i++) {
        int numero;
        cin >> numero;
        frequencia[numero]++; // ausente começa em 0
    }

    for (const auto& item : frequencia) {
        // first = chave; second = frequência.
        cout << item.first << ": " << item.second << '\n';
    }

    // Consulta sem inserir:
    // auto it = frequencia.find(7);
    // if (it != frequencia.end()) cout << it->second;
    // frequencia.erase(7); // remove chave
    // auto it = frequencia.lower_bound(5); // chave >= 5
    // Para chave > 5: frequencia.upper_bound(5); valide it != end().
    // begin()->second NÃO é a menor frequência.

    if (!frequencia.empty()) {
        cout << "menor_chave=" << frequencia.begin()->first;
        cout << " maior_chave=" << frequencia.rbegin()->first << '\n';
    } else cout << "vazio\n";

    // Remover durante percurso:
    // for (auto it = frequencia.begin(); it != frequencia.end(); ) {
    //     if (it->second == 1) it = frequencia.erase(it); // próximo
    //     else ++it;
    // }
    // Após erase, use o retorno; it antigo é inválido.
}
