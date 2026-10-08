# SWEEP LINE — intervalos viram eventos

[Índice](README.md) · [Compressão](coordinate-compression.md) · [Bounds](bounds.md)

## NECESSIDADE / RECONHECIMENTO

“Quantos intervalos se sobrepõem?”, “qual o máximo simultâneo?”, “quantos contêm x?”.
Em vez de visitar cada posição, processe somente onde algo muda: início e fim.
O exemplo é de intervalos 1D; sweep line em geometria pode exigir outras estruturas.

## IDEIA

Para intervalos **[l, r)**: +1 em l, -1 em r. Ordene os eventos por coordenada
e acumule os deltas (prefix sum). Após processar todos os eventos em x,
active é a quantidade válida em x e até antes da próxima coordenada.

```text
[1,4) e [3,6)
posição:  1   3   4   6
delta:   +1  +1  -1  -1
ativos:   1   2   1   0
máximo: 2; no ponto 4, apenas o segundo intervalo está ativo.
```

## TEMPLATE C++

Entrada: N intervalos l r (l <= r), depois Q e Q pontos de consulta.
Saída: máximo simultâneo, depois a quantidade ativa em cada ponto.
Coordenadas negativas/grandes funcionam: não existe um vetor até MAX_COORD.

<!-- search-example: sweep-line -->
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<long long, int>> events;
    for (int i = 0; i < n; i++) {
        long long l, r;
        cin >> l >> r;
        if (l == r) continue; // [l,l) é vazio
        events.push_back({l, +1});
        events.push_back({r, -1});
    }
    sort(events.begin(), events.end());

    vector<long long> positions, counts;
    long long active = 0, maximum = 0;
    size_t i = 0;
    while (i < events.size()) {
        long long x = events[i].first;
        // Agrupa empates: não registra estados intermediários em x.
        while (i < events.size() && events[i].first == x) {
            active += events[i].second;
            i++;
        }
        positions.push_back(x);
        counts.push_back(active);
        maximum = max(maximum, active);
    }
    cout << maximum << '\n';

    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;
        auto it = upper_bound(positions.begin(), positions.end(), x);
        if (it == positions.begin()) cout << 0 << '\n';
        else {
            auto index = (it - positions.begin()) - 1; // último evento <= x
            cout << counts[index] << '\n';
        }
    }
}
```

```text
Entrada: 2
         1 4
         3 6
         3
         0 3 4
Saída:   2
         0
         2
         1
```

## COMPLEXIDADE

O(N log N) para ordenar + O(N) para acumular; O(log N) por consulta,
total O(N log N + Q log N). Memória O(N). Para zero/um elemento, leia log como log(N+1).
Só precisa do máximo? Remova consultas e os vetores positions/counts.
Coordenadas inteiras pequenas em [0,U]? Um vetor de diferenças permite O(U+N+Q),
como na referência de study/, mas usa O(U) de memória.

## ARMADILHAS

- **[l,r) não inclui r.** [1,3) e [3,5) não se sobrepõem; empates precisam dessa convenção.
- Para intervalos fechados [l,r], l = r não é vazio: não copie este código sem adaptar.
  Em pontos inteiros, evento -1 em r+1 é uma opção **somente se r+1 couber no tipo**.
- Ordenar coordenadas não basta: mantenha o delta associado ao evento.
- Para comprimento da união, use distâncias **originais** entre eventos quando active > 0;
  a quantidade de índices comprimidos não mede comprimento.
- Eventos são a ideia; prefix sum é a acumulação. Não confunda com testar todo par O(N²).
