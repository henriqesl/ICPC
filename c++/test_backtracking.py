"""Na raiz icpc/: python -B c++/test_backtracking.py. Testa as sete receitas reais."""

from collections import Counter, deque
import itertools
from pathlib import Path
import random

from test_search import BuildDirectory, compile_source, run

ROOT = Path(__file__).resolve().parent
SOURCE = ROOT / "search" / "backtracking-templates.cpp"

# Acrescenta uma entrada de teste ao arquivo sem main; não copia as recursões.
RUNNER = r"""
#include <cassert>
int main() {
    int mode;
    cin >> mode;
    if (mode == 1) {
        int n; cin >> n;
        decisions::options.resize(n);
        for (auto &options : decisions::options) {
            int size; cin >> size;
            options.resize(size);
            for (int &x : options) cin >> x;
        }
        bool exists = decisions::exists(0);
        assert(decisions::current.empty());
        ll count = decisions::count(0);
        assert(decisions::current.empty());
        assert(decisions::exists(0) == exists); // sucesso também restaura
        assert(decisions::count(0) == count);
        cout << exists << ' ' << count << '\n';
    } else if (mode == 2) {
        int n; cin >> n >> subsets::target;
        subsets::a.resize(n);
        for (ll &x : subsets::a) cin >> x;
        ll answer = subsets::count(0);
        assert(subsets::sum == 0);
        assert(subsets::count(0) == answer);
        cout << answer << '\n';
    } else if (mode == 3) {
        cin >> placements::n;
        int n = placements::n;
        placements::board.resize(n);
        for (auto &row : placements::board) cin >> row;
        auto original = placements::board;
        placements::col.assign(n, 0);
        placements::diag1.assign(max(0, 2*n-1), 0);
        placements::diag2.assign(max(0, 2*n-1), 0);
        ll answer = placements::count(0);
        assert(placements::board == original);
        assert(all_of(placements::col.begin(), placements::col.end(), [](int x) { return x == 0; }));
        assert(all_of(placements::diag1.begin(), placements::diag1.end(), [](int x) { return x == 0; }));
        assert(all_of(placements::diag2.begin(), placements::diag2.end(), [](int x) { return x == 0; }));
        assert(placements::count(0) == answer);
        cout << answer << '\n';
    } else if (mode == 4) {
        int n; cin >> n;
        permutations::a.resize(n);
        for (ll &x : permutations::a) cin >> x;
        permutations::used.assign(n, 0);
        permutations::current.assign(n, -777);
        permutations::generate(0);
        assert(permutations::current == vector<ll>(n, -777));
        assert(permutations::used == vector<int>(n, 0));
    } else if (mode == 5) {
        int n; cin >> n >> optimization::k;
        optimization::cost.resize(n);
        for (ll &x : optimization::cost) cin >> x;
        optimization::suffix.assign(n+1, 0);
        for (int i = n-1; i >= 0; i--)
            optimization::suffix[i] = optimization::suffix[i+1] + optimization::cost[i];
        optimization::minimize(0, 0);
        assert(optimization::current == 0);
        optimization::maximize(0, 0);
        assert(optimization::current == 0);
        if (!optimization::found_min) {
            assert(!optimization::found_max);
            cout << "none\n";
        } else {
            assert(optimization::found_max);
            cout << optimization::best_min << ' ' << optimization::best_max << '\n';
        }
    } else if (mode == 6) {
        int start_r, start_c;
        cin >> paths::rows >> paths::cols >> start_r >> start_c >> paths::target_r >> paths::target_c;
        paths::board.resize(paths::rows);
        for (auto &row : paths::board) cin >> row;
        auto original = paths::board;
        paths::visited.assign(paths::rows, vector<int>(paths::cols, 0));
        bool answer = paths::exists(start_r, start_c);
        assert(paths::board == original);
        assert(paths::visited == vector<vector<int>>(paths::rows, vector<int>(paths::cols, 0)));
        assert(paths::exists(start_r, start_c) == answer);
        cout << answer << '\n';
    }
}
"""


def grid_oracle(board, start, target):
    rows = len(board)
    cols = len(board[0]) if rows else 0
    def valid(cell):
        r, c = cell
        return 0 <= r < rows and 0 <= c < cols and board[r][c] != "#"
    if not valid(start) or not valid(target):
        return False
    queue, visited = deque([start]), {start}
    while queue:
        cell = queue.popleft()
        if cell == target:
            return True
        r, c = cell
        for neighbor in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
            if valid(neighbor) and neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return False


def main():
    import shutil
    compiler = shutil.which("g++")
    assert compiler, "g++ precisa estar no PATH"
    source = SOURCE.read_text(encoding="utf-8")
    rng = random.Random(109)
    checks = 0
    with BuildDirectory(prefix="icpc-backtracking-") as folder:
        folder = Path(folder)
        executable = compile_source(compiler, folder, "backtracking", source + RUNNER)
        print("Compilou: sete receitas + verificação de restauração de estado", flush=True)

        options_cases = [[], [[]], [[1], [1]], [[1, 2], [1, 2]], [[1], [2], []]]
        options_cases += [[rng.sample(range(4), rng.randrange(5)) for _ in range(rng.randrange(6))]
                         for _ in range(20)]
        for options in options_cases:
            ways = sum(all(a != b for a, b in zip(choice, choice[1:]))
                       for choice in itertools.product(*options))
            data = f"1 {len(options)}\n" + "".join(
                str(len(row)) + " " + " ".join(map(str, row)) + "\n" for row in options)
            assert run(executable, data) == [f"{int(ways > 0)} {ways}"]
            checks += 1

        subsets = [([], 0), ([], 1), ([0, 0, 0], 0), ([5, -4], 1), ([-2, 1, 1], 0)]
        subsets += [([rng.randrange(-5, 6) for _ in range(rng.randrange(9))], rng.randrange(-9, 10))
                    for _ in range(20)]
        for values, target in subsets:
            ways = sum(sum(choice) == target for size in range(len(values) + 1)
                       for choice in itertools.combinations(values, size))
            data = f"2 {len(values)} {target}\n" + " ".join(map(str, values)) + "\n"
            assert run(executable, data) == [str(ways)]
            checks += 1

        boards = [["." * n for _ in range(n)] for n in range(7)]
        boards += [["#"], [".#..", "....", "....", "...."]]
        boards += [["".join("#" if rng.randrange(4) == 0 else "." for _ in range(4)) for _ in range(4)]
                   for _ in range(8)]
        for board in boards:
            n = len(board)
            ways = 0
            for columns in itertools.permutations(range(n)):
                if any(board[r][c] == "#" for r, c in enumerate(columns)):
                    continue
                if len({r+c for r, c in enumerate(columns)}) == n and len({r-c for r, c in enumerate(columns)}) == n:
                    ways += 1
            assert run(executable, f"3 {n}\n" + "\n".join(board) + "\n") == [str(ways)]
            checks += 1

        for values in [[1], [1, 2, 3], [2, 1, 2], [-1, 0, 1, 2]]:
            expected = Counter(itertools.permutations(values))
            data = f"4 {len(values)}\n" + " ".join(map(str, values)) + "\n"
            actual = Counter(tuple(map(int, line.split())) for line in run(executable, data))
            assert actual == expected
            checks += 1
        assert run(executable, "4 0\n") == [] # uma folha vazia, impressa como linha vazia
        checks += 1

        costs = [([], 0), ([], 1), ([0, 0, 0], 2), ([5, 1, 3], 2), ([2], 3), ([2**63-1], 1)]
        costs += [([rng.randrange(10) for _ in range(rng.randrange(9))], rng.randrange(10)) for _ in range(20)]
        for values, k in costs:
            sums = [sum(choice) for choice in itertools.combinations(values, k)]
            expected = f"{min(sums)} {max(sums)}" if sums else "none"
            data = f"5 {len(values)} {k}\n" + " ".join(map(str, values)) + "\n"
            assert run(executable, data) == [expected]
            checks += 1

        grids = [([], (0, 0), (0, 0)), (["."], (0, 0), (0, 0)), (["#"], (0, 0), (0, 0)),
                 (["..", "##"], (0, 0), (1, 1)), (["..", ".."], (-1, 0), (1, 1)),
                 (["...", ".#.", "..."], (0, 0), (2, 2))]
        grids += [(["".join("#" if rng.randrange(3) == 0 else "." for _ in range(3)) for _ in range(3)],
                   (0, 0), (2, 2)) for _ in range(20)]
        for board, start, target in grids:
            rows, cols = len(board), len(board[0]) if board else 0
            data = f"6 {rows} {cols} {start[0]} {start[1]} {target[0]} {target[1]}\n" + "\n".join(board) + "\n"
            assert run(executable, data) == [str(int(grid_oracle(board, start, target)))]
            checks += 1
        print(f"OK: sete receitas, {checks} casos contra força bruta/BFS e restauração após sucesso/falha.")


if __name__ == "__main__":
    main()
