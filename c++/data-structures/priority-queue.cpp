// Aplicação: sempre processar primeiro o maior valor disponível.
// Use em prioridades, maiores pontuações, tarefas urgentes ou top K.
// Para obter o menor no topo: priority_queue<int, vector<int>, greater<int>>.
// Complexidade: push/pop O(log N), top O(1).
// Entrada: N e N inteiros. Ex.: 3 2 9 4 -> 9 4 2.
// Total O(N log N), memória O(N); extrações consomem a estrutura.
// Use para chegadas/remoções intercaladas; só ordenar é mais simples com sort.
// Agora a segunda linha mostra a mesma entrada em ordem crescente (min-heap).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int> pq; // fila por VALOR: o maior sai primeiro, não quem chegou antes
    priority_queue<int, vector<int>, greater<int>> minimo;
    // greater<int> inverte a prioridade: o MENOR fica no topo.

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.push(x); // o maior valor fica acessível por pq.top()
        minimo.push(x);
    }

    while (!pq.empty()) {
        int maior = pq.top(); // consulta sem remover
        cout << maior << ' ';
        pq.pop(); // remove esse maior; o próximo maior assume o topo
    }
    cout << '\n';

    while (!minimo.empty()) {
        cout << minimo.top() << ' ';
        minimo.pop();
    }
    cout << '\n';
    // Não há índice, begin(), erase(valor) nem lower_bound no heap.
    // Só top() é garantido extremo; os demais elementos não ficam em ordem.
    // Para os K maiores sem guardar tudo: use min-heap de tamanho até K.
    // A cada entrada, push(x); se size() > K, pop() elimina o menor candidato.
    // Para consultar sem consumir, copie o heap (O(N)) e retire da cópia.
}
