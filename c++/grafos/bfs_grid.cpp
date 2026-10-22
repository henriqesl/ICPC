// Grid = grafo implícito; 4 direções; BFS -> menor distância.
// O(linhas * colunas) tempo/memória; '#' = parede, demais células livres.
// Entrada: n m; n linhas; sr sc tr tc (células válidas, 1-based).
// Saída: distância até destino; -1 se bloqueado/inalcançável.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto &row : grid) cin >> row;
    int sr, sc, tr, tc;
    cin >> sr >> sc >> tr >> tc;
    --sr;
    --sc;
    --tr;
    --tc;
    if (grid[sr][sc] == '#' || grid[tr][tc] == '#') {
        cout << -1 << '\n';
        return 0;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    cout << dist[tr][tc] << '\n';
}

/*
COMO LER ESTE CÓDIGO
1. Cada célula livre é um vértice; não é preciso montar adjacências.
   dist[r][c]=-1 indica célula ainda não alcançada; '#' não pode entrar.
2. dr/dc combinados dão cima, baixo, esquerda e direita.
3. A fila começa em {sr,sc}. auto [r,c] separa a célula retirada.
4. Para cada direção, calculamos nr/nc e descartamos fora do grid,
   paredes e células já visitadas. As demais recebem dist[r][c]+1.
Exemplo: grid livre 2x2, de (1,1) a (2,2), tem distância 2.
A resposta conta movimentos, não células. Cada movimento deve custar igual.
*/
