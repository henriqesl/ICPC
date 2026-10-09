#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
    CONSULTA RÁPIDA — RETORNO + ESCOLHAS (combine os dois!)

    EXISTE?             -> TEMPLATE 1: bool, para no primeiro sucesso.
    QUANTAS?            -> TEMPLATE 2: ll, soma chamadas; folha válida vale 1.
    PEGA / NÃO PEGA?    -> TEMPLATE 3: duas chamadas por idx.
    UMA ENTRE VÁRIAS?   -> TEMPLATE 4: for nas opções de cada etapa.
    CADA ITEM UMA VEZ?  -> TEMPLATE 5: used[], marca / recursa / desmarca.
    MELHOR?             -> TEMPLATE 6: min/max + limite seguro para poda.
    GRID / CAMINHO?     -> TEMPLATE 7: vizinhos + visited do caminho atual.

    FAZ -> RECURSA -> DESFAZ. Inclui retornos antecipados!
    O estado PARCIAL compartilhado sai igual ao que entrou na chamada.
    Melhor resposta/soluções salvas são resultados: não se desfazem.

    Sem main: copie a receita, inicialize os dados e chame pelo seu main.
    Namespaces apenas separam nomes para este arquivo compilar com -c.
    Pode copiar só o interior do namespace, com includes/ll acima.
    Contagens, somas e limites precisam caber em ll; profundidade cabe na pilha.
    Guia: backtracking.md. Teste: python -B c++/test_backtracking.py
*/

namespace decisions {
// Dado neutro: opções por posição; vizinhos não podem ter valores iguais.
// Inicialize options e current.clear(); opções de cada posição são distintas.
vector<vector<int>> options;
vector<int> current;

// TEMPLATE 1 — EXISTE ALGUMA SOLUÇÃO? bool + uma opção por posição.
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

// TEMPLATE 2 — QUANTAS SOLUÇÕES? Usa options/current acima, outro retorno.
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
// TEMPLATE 3 — PEGA / NÃO PEGA: contar subconjuntos de índices com soma alvo.
// Inicialize a, target e sum = 0; inicie em count(0).
// Aceita negativos. Não pode podar sum > target sem outras hipóteses!
// Soma dos valores absolutos e quantidade de soluções precisam caber em ll.
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
// Para coverage: estado (idx, coverage), pega com coverage | mask[idx].
// Passe coverage POR VALOR; folha válida: coverage == FULL. OR não se desfaz com XOR!
} // namespace subsets

namespace placements {
// TEMPLATE 4 — UMA OPÇÃO ENTRE VÁRIAS: uma coluna por linha.
// board: '.' livre, '#' bloqueada; proíbe coluna e diagonais compartilhadas.
// Inicialize n = board.size(); col.assign(n,0);
// diag1.assign(max(0,2*n-1),0); diag2.assign(max(0,2*n-1),0); chame count(0).
// Para outras regras, troque a validade; o for e faz/recursa/desfaz continuam.
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
// TEMPLATE 5 — PERMUTAÇÃO / USED[]: ordem importa, cada índice usado uma vez.
// Inicialize a; current.resize(a.size()); used.assign(a.size(),0); chame generate(0).
// Valores repetidos em índices distintos geram sequências repetidas por padrão.
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
        // Para só sequências distintas: ordene a antes e ative a linha abaixo.
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
// TEMPLATE 6 — MELHOR SOLUÇÃO: escolher exatamente k índices com custo NÃO NEGATIVO.
// Inicialize cost, k, current=0, found_min=found_max=false.
// best_min=LLONG_MAX; best_max=LLONG_MIN.
// Para maximize, prepare suffix[n]=0; suffix[i]=suffix[i+1]+cost[i].
// A soma total cabe em ll. Flags distinguem ausência de um valor-limite válido.
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
    // Mesmo pegando TODOS os restantes, não supera a melhor resposta.
    // É um teto otimista (pode nem respeitar k), nunca subestima o melhor possível.
    if (found_max && current + suffix[idx] <= best_max) return;

    current += cost[idx];
    maximize(idx + 1, chosen + 1);
    current -= cost[idx];
    maximize(idx + 1, chosen);
}
} // namespace optimization

namespace paths {
// TEMPLATE 7 — GRID / CAMINHO: bool + escolha de vizinho não bloqueado/visitado.
// Inicialize rows, cols, board, target_r/c; visited.assign(rows, vector<int>(cols,0)).
// '#' bloqueia, '.' permite; chame exists(start_r,start_c).
// visited aqui pertence AO CAMINHO, e é restaurado inclusive no sucesso.
// Para APENAS alcance/componente, use visited global e NÃO desmarque: O(V+E).
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
