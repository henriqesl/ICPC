// ITERADORES: cursor, valor, índice e limites. Demonstração sem entrada.
// Dentro de main, cada bloco é independente. Leia iterators.md para os detalhes.
// Find em vector O(N); bounds em set O(log N); sort O(N log N).
#include <bits/stdc++.h>
using namespace std;

int main() {
    { // O cursor muda com ++; *it lê/altera o valor daquela posição.
        vector<int> v{10, 20, 30};
        auto it = v.begin();
        cout << "cursor: " << *it << ' ';
        ++it;
        cout << *it << ' ';
        *it = 7;
        cout << v[1] << '\n'; // 10 20 7
    }
    { // Find retorna end se ausente. Valor e índice são coisas diferentes.
        vector<int> v{8, 3, 5};
        auto it = find(v.begin(), v.end(), 3);
        cout << "busca: ";
        if (it != v.end()) cout << *it << ' ' << (it - v.begin());
        it = find(v.begin(), v.end(), 99);
        if (it == v.end()) cout << " ausente";
        cout << '\n';
    }
    { // Set tem cursor, mas não índice nem it+K. Distance percorre os passos.
        set<int> s{1, 4, 5, 9};
        auto it = s.lower_bound(3);
        cout << "set: ";
        if (it != s.end()) cout << *it;
        if (!s.empty()) cout << ' ' << *s.rbegin();
        cout << ' ' << distance(s.begin(), it) << '\n'; // 4 9 1
    }
    { // Map: it->first é chave, it->second é informação; *it é o pair inteiro.
        map<string, int> idade{{"Ana", 20}, {"Bia", 21}};
        auto it = idade.find("Ana");
        cout << "map: ";
        if (it != idade.end()) {
            it->second++;
            cout << it->first << ':' << it->second;
        }
        cout << '\n';
    }
    { // Erase devolve o próximo, pois o cursor apagado não pode mais ser usado.
        set<int> s{1, 2, 3, 4};
        for (auto it = s.begin(); it != s.end(); ) {
            if (*it % 2 == 0) it = s.erase(it);
            else ++it;
        }
        cout << "erase: ";
        for (int x : s) cout << x << ' ';
        cout << '\n';
    }
    { // Sort não realoca o vector: o cursor mantém a posição, não a identidade.
        vector<int> v{30, 10, 20};
        auto it = v.begin(); // inicialmente aponta para 30
        sort(v.begin(), v.end());
        cout << "apos_sort: " << *it << '\n'; // 10
    }
    // Vazio: begin() == end(); não há *begin() válido para ler.
    // *end(), ++end(), --begin() e prev(begin()) são operações inválidas.
    // Após crescer/apagar/rehash, confira validade antes de reutilizar cursores.
}
