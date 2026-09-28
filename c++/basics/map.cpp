// MAP: cada chave está associada a um valor. Aqui: número -> frequência.
// Use para contar ocorrências e percorrer as chaves em ORDEM CRESCENTE.
// Entrada: N e N inteiros. 4 3 3 8 3 -> 3: 3 / 8: 1.
// Inserção/busca O(log(K+1)), memória O(K), K = chaves diferentes.
// Após as frequências: menor e maior chave, ou "vazio".
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> frequencia; // chave int, valor int

    for (int i = 0; i < n; i++) {
        int numero;
        cin >> numero;
        frequencia[numero]++; // chave nova começa em 0; depois soma 1
        // Ao ler 3,3,8,3: {3:1} -> {3:2} -> {3:2,8:1} -> {3:3,8:1}
    }

    for (const auto& item : frequencia) {
        // item é um pair. first = chave; second = valor associado.
        cout << item.first << ": " << item.second << '\n';
    }

    // Consultar SEM criar chave:
    // auto it = frequencia.find(7);
    // if (it != frequencia.end()) cout << it->second;
    // Se não encontrou, it == end(); não acesse it->second nesse caso.
    // frequencia[7] criaria a chave com zero mesmo numa simples consulta!
    // frequencia.erase(7); remove a chave se existir.
    // begin()->first = menor CHAVE; rbegin()->first = maior CHAVE.
    // begin()->second é o valor da menor chave, NÃO a menor frequência.
    // auto it = frequencia.lower_bound(5); // primeira chave >= 5
    // auto it = frequencia.upper_bound(5); // primeira chave > 5
    // if (it != frequencia.end()) cout << it->first << ": " << it->second;

    if (!frequencia.empty()) {
        cout << "menor_chave=" << frequencia.begin()->first;
        cout << " maior_chave=" << frequencia.rbegin()->first << '\n';
    } else cout << "vazio\n";

    // Remover frequências iguais a 1 durante um percurso:
    // for (auto it = frequencia.begin(); it != frequencia.end(); ) {
    //     if (it->second == 1) it = frequencia.erase(it); // próximo
    //     else ++it;
    // }
    // Não faça erase(it) e depois ++it: esse iterador já é inválido.
}
