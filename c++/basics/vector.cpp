// Aplicação: buscar, contar, ordenar ou obter o índice de um valor.
// Entrada: n, os n valores e um valor x.
// Complexidade: find/count O(N); sort O(N log N).
// Ex.: 4 3 1 3 8 3 -> indice=0 / ocorrencias=2 / 1 3 3 8.
// Índice ORIGINAL antes do sort; -1 se ausente. Memória O(N).
// Depois: extremos ordenados, cópia sem X e cópia sem repetidos.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cin >> x;

    // find retorna um iterador; a distância até begin() é o índice.
    auto it = find(v.begin(), v.end(), x);
    // end() significa que não encontrou. Não podemos ler *end().
    int index = -1;
    if (it != v.end()) index = int(it - v.begin());

    cout << "indice=" << index << '\n';
    cout << "ocorrencias=" << count(v.begin(), v.end(), x) << '\n';

    sort(v.begin(), v.end()); // ordena o próprio vector
    for (int value : v) cout << value << ' ';
    cout << '\n';

    if (!v.empty()) {
        // front/back são primeiro/último. Só são min/max porque ordenamos!
        cout << "primeiro=" << v.front() << " ultimo=" << v.back() << '\n';
    } else cout << "vazio\n";

    vector<int> semX = v; // cópia O(N); v não muda
    semX.erase(remove(semX.begin(), semX.end(), x), semX.end());
    cout << "sem_x:";
    for (int valor : semX) cout << ' ' << valor;
    cout << '\n';

    vector<int> distintos = v; // iguais estão juntos porque v está ordenado
    distintos.erase(unique(distintos.begin(), distintos.end()), distintos.end());
    cout << "distintos:";
    for (int valor : distintos) cout << ' ' << valor;
    cout << '\n';

    // remove/unique reorganizam; erase realmente encolhe o vetor. Ambos O(N).
    // Sem ordenar, unique elimina apenas repetições CONSECUTIVAS.
    // Inserir em i (0 <= i <= size): v.insert(v.begin()+i, valor); O(N).
    // Remover em i (0 <= i < size): v.erase(v.begin()+i); O(N).
    // Remover último: if (!v.empty()) v.pop_back(); O(1).
    // reserve(n) reserva capacidade, NÃO cria elementos; resize(n) muda size.
    // push_back pode realocar e invalidar iteradores/referências.
}
