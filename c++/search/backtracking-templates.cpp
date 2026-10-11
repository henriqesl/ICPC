#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// RETORNO + ESCOLHAS: combine; procure TEMPLATE N.
// 1 existe; 2 conta; 3 pega/não pega; 4 opções; 5 usados; 6 melhor; 7 grid.
// Sem main: copie uma receita + includes/ll; inicialize conforme seu cabeçalho.
// FAZ -> RECURSA -> DESFAZ, inclusive no sucesso. Resultados não se desfazem.
// Somas/contagens em ll; recursão precisa caber na pilha. Poda mantém pior caso.
// Custo: subsets O(2^N), B opções/D etapas O(B^D) (B>=2), permutação O(N*N!).
// Memória extra O(profundidade), além do estado. Guia: backtracking.md.

namespace decisions {
// Opções por posição (distintas); vizinhos diferentes. Inicialize options/current.clear().
vector<vector<int>> options;
vector<int> current;

// TEMPLATE 1 — EXISTE? bool; uma opção por posição.
bool exists(int pos) {
    if (pos == static_cast<int>(options.size())) return true;

    for (int choice : options[pos]) {
        if (!current.empty() && current.back() == choice) continue;

        current.push_back(choice);                // FAZ
        bool found = exists(pos + 1);             // RECURSA
        current.pop_back();                       // DESFAZ, mesmo no sucesso
        if (found) return true;
    }
    return false;
}

// TEMPLATE 2 — QUANTAS? Soma filhos; options/current acima.
ll count(int pos) {
    if (pos == static_cast<int>(options.size())) return 1;

    ll ways = 0;
    for (int choice : options[pos]) {
        if (!current.empty() && current.back() == choice) continue;

        current.push_back(choice);
        ways += count(pos + 1);                    // soma, não para no sucesso
        current.pop_back();
    }
    return ways;
}
} // namespace decisions

namespace subsets {
// TEMPLATE 3 — PEGA / NÃO PEGA: soma alvo; conta subconjuntos de índices.
// Inicialize a/target, sum=0; count(0). Absolutos/contagem cabem em ll.
// Aceita negativos: não pode podar sum > target.
vector<ll> a;
ll target, sum = 0;

ll count(int idx) {
    if (idx == static_cast<int>(a.size())) return sum == target ? 1 : 0;

    sum += a[idx];                                // FAZ: pega
    ll ways = count(idx + 1);                      // RECURSA
    sum -= a[idx];                                // DESFAZ
    ways += count(idx + 1);                        // não pega
    return ways;
}
// Coverage por valor: coverage | mask[idx]; folha coverage==FULL. OR não desfaz com XOR.
} // namespace subsets

namespace placements {
// TEMPLATE 4 — OPÇÕES: uma coluna por linha, sem coluna/diagonal compartilhada.
// board: '.' livre, '#' bloqueada; n=board.size(); col.assign(n,0).
// diag1.assign(max(0,2*n-1),0); diag2.assign(max(0,2*n-1),0); count(0).
int n;
vector<string> board;
vector<int> col, diag1, diag2;

ll count(int row) {
    if (row == n) return 1;

    ll ways = 0;
    for (int c = 0; c < n; c++) {
        int d1 = row + c, d2 = row - c + n - 1;
        if (board[row][c] != '.' || col[c] || diag1[d1] || diag2[d2]) continue;

        board[row][c] = 'Q';
        col[c] = diag1[d1] = diag2[d2] = 1;
        ways += count(row + 1);
        col[c] = diag1[d1] = diag2[d2] = 0;
        board[row][c] = '.';
    }
    return ways;
}
} // namespace placements

namespace permutations {
// TEMPLATE 5 — PERMUTAÇÃO: cada índice uma vez; repetidos podem duplicar saídas.
// Inicialize a; current.resize(a.size()); used.assign(a.size(),0); generate(0).
vector<ll> a, current;
vector<int> used;

void generate(int pos) {
    int n = static_cast<int>(a.size());
    if (pos == n) {
        for (ll x : current) cout << x << ' ';
        cout << '\n';                             // ou avalie a solução aqui
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        // Sem duplicatas: sort(a) antes + ative abaixo.
        // if (i > 0 && a[i] == a[i-1] && !used[i-1]) continue;

        ll previous = current[pos];
        used[i] = 1;
        current[pos] = a[i];
        generate(pos + 1);
        current[pos] = previous;                   // restaura também o buffer
        used[i] = 0;
    }
}
} // namespace permutations

namespace optimization {
// TEMPLATE 6 — MELHOR: exatamente k índices, custos NÃO NEGATIVOS; soma cabe em ll.
// Inicialize cost/k, current=0, found_min=found_max=false; best_min=LLONG_MAX, best_max=LLONG_MIN.
// Max: suffix[n]=0; suffix[i]=suffix[i+1]+cost[i]. Flags distinguem ausência.
vector<ll> cost, suffix;
int k;
ll current = 0, best_min = LLONG_MAX, best_max = LLONG_MIN;
bool found_min = false, found_max = false;

void minimize(int idx, int chosen) {
    if (chosen == k) {
        best_min = min(best_min, current);
        found_min = true;
        return;
    }
    int n = static_cast<int>(cost.size());
    if (idx == n || n - idx < k - chosen) return; // faltam itens suficientes
    if (found_min && current >= best_min) return; // não negativos: custo só aumenta

    current += cost[idx];
    minimize(idx + 1, chosen + 1);
    current -= cost[idx];
    minimize(idx + 1, chosen);
}

void maximize(int idx, int chosen) {
    if (chosen == k) {
        best_max = max(best_max, current);
        found_max = true;
        return;
    }
    int n = static_cast<int>(cost.size());
    if (idx == n || n - idx < k - chosen) return;
    // Teto otimista: nem pegando todos os restantes melhora.
    if (found_max && current + suffix[idx] <= best_max) return;

    current += cost[idx];
    maximize(idx + 1, chosen + 1);
    current -= cost[idx];
    maximize(idx + 1, chosen);
}
} // namespace optimization

namespace paths {
// TEMPLATE 7 — CAMINHO: visited local ao caminho; desfaz inclusive no sucesso.
// Inicialize rows/cols/board/target_r/c; visited.assign(rows,vector<int>(cols,0)).
// '#' bloqueada; exists(start_r,start_c). Pior O(4^V), memória O(V).
// Só alcance/menor distância: ../grafos/dfs.cpp ou bfs.cpp; não enumere caminhos.
int rows, cols, target_r, target_c;
vector<string> board;
vector<vector<int>> visited;
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

bool exists(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
    if (board[r][c] == '#' || visited[r][c]) return false;
    if (r == target_r && c == target_c) return true;

    visited[r][c] = 1;
    for (int d = 0; d < 4; d++) {
        if (exists(r + dr[d], c + dc[d])) {
            visited[r][c] = 0;                     // DESFAZ antes do retorno antecipado
            return true;
        }
    }
    visited[r][c] = 0;
    return false;
}
} // namespace paths
