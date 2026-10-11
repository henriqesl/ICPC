// ITERADORES: posição / valor / índice. Demo sem entrada.
// Find em vector O(N); bounds em set O(log N); sort O(N log N).
// *it: valor; it-begin(): índice no vector. Nunca leia *end().
#include <bits/stdc++.h>
using namespace std;

int main() {
    { // ++it: avança; *it: lê/altera valor
        vector<int> v{10, 20, 30};
        auto it = v.begin();
        cout << "cursor: " << *it << ' ';
        ++it;
        cout << *it << ' ';
        *it = 7;
        cout << v[1] << '\n'; // 10 20 7
    }
    { // find: end se ausente
        vector<int> v{8, 3, 5};
        auto it = find(v.begin(), v.end(), 3);
        cout << "busca: ";
        if (it != v.end()) cout << *it << ' ' << (it - v.begin());
        it = find(v.begin(), v.end(), 99);
        if (it == v.end()) cout << " ausente";
        cout << '\n';
    }
    { // set: sem it+K/it-begin; distance O(K)
        set<int> s{1, 4, 5, 9};
        auto it = s.lower_bound(3);
        cout << "set: ";
        if (it != s.end()) cout << *it;
        if (!s.empty()) cout << ' ' << *s.rbegin();
        cout << ' ' << distance(s.begin(), it) << '\n'; // 4 9 1
    }
    { // map: first=chave; second=valor
        map<string, int> idade{{"Ana", 20}, {"Bia", 21}};
        auto it = idade.find("Ana");
        cout << "map: ";
        if (it != idade.end()) {
            it->second++;
            cout << it->first << ':' << it->second;
        }
        cout << '\n';
    }
    { // erase retorna próximo
        set<int> s{1, 2, 3, 4};
        for (auto it = s.begin(); it != s.end(); ) {
            if (*it % 2 == 0) it = s.erase(it);
            else ++it;
        }
        cout << "erase: ";
        for (int x : s) cout << x << ' ';
        cout << '\n';
    }
    { // sort: mesma posição, outro valor
        vector<int> v{30, 10, 20};
        auto it = v.begin(); // lê 30
        sort(v.begin(), v.end());
        cout << "apos_sort: " << *it << '\n'; // 10
    }
    // Vazio: begin == end.
    // *end(), ++end(), --begin() e prev(begin()) são operações inválidas.
    // Crescer/erase/rehash pode invalidar cursores.
}
