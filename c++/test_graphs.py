"""Na raiz icpc/: python -B c++/test_graphs.py. Compila/testa os nove .cpp reais."""
from pathlib import Path
import random
import shutil

from test_search import BuildDirectory, compile_source, run

ROOT = Path(__file__).resolve().parent / "grafos"
INF = 10**9


def graph_input(n, edges):
    return f"{n} {len(edges)}\n" + "".join(f"{u+1} {v+1}\n" for u, v in edges)


def distances(n, edges):
    # Floyd-Warshall: oráculo independente das BFS/DFS dos templates.
    dist = [[INF] * n for _ in range(n)]
    for u in range(n):
        dist[u][u] = 0
    for u, v in edges:
        dist[u][v] = min(dist[u][v], 1)
        dist[v][u] = min(dist[v][u], 1)
    for k in range(n):
        for u in range(n):
            for v in range(n):
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v])
    return dist


def components_and_cycle(n, edges):
    # DSU: uma aresta dentro do mesmo conjunto fecha ciclo, inclusive paralela/loop.
    parent = list(range(n))

    def find(u):
        while parent[u] != u:
            u = parent[u]
        return u

    cycle = False
    for u, v in edges:
        u, v = find(u), find(v)
        if u == v:
            cycle = True
        else:
            parent[u] = v
    return len({find(u) for u in range(n)}), cycle


def directed_cycle(n, edges):
    reach = [[False] * n for _ in range(n)]
    for u, v in edges:
        reach[u][v] = True
    for k in range(n):
        for u in range(n):
            for v in range(n):
                reach[u][v] |= reach[u][k] and reach[k][v]
    return any(reach[u][u] for u in range(n))


def grid_distance(grid, start, target):
    n, m = len(grid), len(grid[0])
    if grid[start[0]][start[1]] == "#" or grid[target[0]][target[1]] == "#":
        return -1
    edges = []
    for r in range(n):
        for c in range(m):
            if grid[r][c] == "#":
                continue
            for nr, nc in ((r + 1, c), (r, c + 1)):
                if nr < n and nc < m and grid[nr][nc] != "#":
                    edges.append((r*m+c, nr*m+nc))
    result = distances(n*m, edges)[start[0]*m+start[1]][target[0]*m+target[1]]
    return -1 if result == INF else result


def main():
    compiler = shutil.which("g++")
    assert compiler, "g++ precisa estar no PATH"
    names = (
        "graph_representation", "dfs", "bfs", "bfs_grid", "bipartite",
        "topological_sort", "bfs_multisource", "cycle_undirected", "tree_diameter",
    )
    rng = random.Random(20261011)
    checks = 0
    with BuildDirectory(prefix="icpc-graphs-") as temporary:
        binaries = {}
        for name in names:
            source = (ROOT / f"{name}.cpp").read_text(encoding="utf-8")
            if name == "graph_representation":
                # Inspeciona as variáveis reais; a demo original não imprime.
                probe = r'''
    cout << "U";
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) cout << ' ' << u << ' ' << v;
    cout << "\nD";
    for (int u = 0; u < n; u++)
        for (int v : directed[u]) cout << ' ' << u << ' ' << v;
    cout << "\nW";
    for (int u = 0; u < n; u++)
        for (auto [v, w] : weighted[u]) cout << ' ' << u << ' ' << v << ' ' << w;
    cout << '\n';
'''
                head, tail = source.rsplit("}", 1)
                source = head + probe + "}" + tail
            binaries[name] = compile_source(compiler, Path(temporary), name, source)
            print("Compilou:", name, flush=True)

        def execute(name, data):
            nonlocal checks
            checks += 1
            return " ".join(run(binaries[name], data)).split()

        def expect(name, data, expected):
            actual = execute(name, data)
            assert actual == list(map(str, expected)), (name, data, actual, expected)

        undirected = [
            (0, []), (1, []), (1, [(0, 0)]), (2, [(0, 1)]),
            (2, [(0, 1), (0, 1)]), (4, [(0, 1), (1, 2), (2, 3)]),
            (4, [(0, 1), (2, 3)]), (5, [(2, 3), (3, 4), (4, 2)]),
            (4, [(0, 1), (1, 2), (2, 3), (3, 0)]),
        ]
        for _ in range(50):
            n = rng.randrange(1, 9)
            edges = [(rng.randrange(n), rng.randrange(n)) for _ in range(rng.randrange(20))]
            undirected.append((n, edges))
        for n, edges in undirected:
            data = graph_input(n, edges)
            dist = distances(n, edges)
            components, cycle = components_and_cycle(n, edges)
            expect("dfs", data, [components])
            expect("cycle_undirected", data, ["SIM" if cycle else "NAO"])
            bipartite = any(
                all(((mask >> u) & 1) != ((mask >> v) & 1) for u, v in edges)
                for mask in range(1 << n)
            )
            expect("bipartite", data, ["SIM" if bipartite else "NAO"])
            if n:
                start = rng.randrange(n)
                expect("bfs", data + f"{start+1}\n", [-1 if d == INF else d for d in dist[start]])
            sources = [rng.randrange(n) for _ in range(rng.randrange(n + 3))] if n else []
            if sources:
                sources.append(sources[0])
            expected = [min((dist[s][v] for s in sources), default=INF) for v in range(n)]
            expect("bfs_multisource", data + f"{len(sources)}\n" +
                   " ".join(str(s+1) for s in sources), [-1 if d == INF else d for d in expected])
            weights = [rng.randint(-10**9, 10**9) for _ in edges]
            weighted_input = f"{n} {len(edges)}\n" + "".join(
                f"{u+1} {v+1} {w}\n" for (u, v), w in zip(edges, weights)
            )
            a, d, w = [[] for _ in range(n)], [[] for _ in range(n)], [[] for _ in range(n)]
            for (u, v), weight in zip(edges, weights):
                a[u].append(v)
                a[v].append(u)
                d[u].append(v)
                w[u].append((v, weight))
            expected = ["U"] + [x for u in range(n) for v in a[u] for x in (u, v)]
            expected += ["D"] + [x for u in range(n) for v in d[u] for x in (u, v)]
            expected += ["W"] + [x for u in range(n) for v, weight in w[u] for x in (u, v, weight)]
            expect("graph_representation", weighted_input, expected)

        directed = [(0, []), (1, []), (1, [(0, 0)]), (3, [(0, 1), (1, 2), (2, 0)]),
                    (5, [(0, 1), (0, 1), (2, 3)]), (5, [(3, 4), (4, 3)])]
        for _ in range(60):
            n = rng.randrange(1, 9)
            directed.append((n, [(rng.randrange(n), rng.randrange(n))
                                 for _ in range(rng.randrange(20))]))
        for n, edges in directed:
            order = execute("topological_sort", graph_input(n, edges))
            if directed_cycle(n, edges):
                assert order == ["IMPOSSIVEL"], (n, edges, order)
            else:
                order = list(map(int, order))
                assert sorted(order) == list(range(1, n+1)), (n, edges, order)
                position = {u-1: i for i, u in enumerate(order)}
                assert all(position[u] < position[v] for u, v in edges), (edges, order)

        grids = [(["."], (0, 0), (0, 0)), (["#"], (0, 0), (0, 0)),
                 ([".#."], (0, 0), (0, 2)), (["..", ".."], (0, 0), (1, 1)),
                 (["..#"], (0, 0), (0, 2)), (["#.."], (0, 0), (0, 2))]
        for _ in range(50):
            n, m = rng.randrange(1, 5), rng.randrange(1, 5)
            grid = ["".join("#" if rng.random() < 0.3 else "." for _ in range(m)) for _ in range(n)]
            grids.append((grid, (rng.randrange(n), rng.randrange(m)),
                          (rng.randrange(n), rng.randrange(m))))
        for grid, start, target in grids:
            data = f"{len(grid)} {len(grid[0])}\n" + "\n".join(grid) + "\n"
            data += " ".join(str(x+1) for x in (*start, *target))
            expect("bfs_grid", data, [grid_distance(grid, start, target)])

        trees = [(1, []), (6, [(0, i) for i in range(1, 6)]),
                 (6, [(i-1, i) for i in range(1, 6)])]
        for _ in range(50):
            n = rng.randrange(1, 16)
            edges = [(u, rng.randrange(u)) for u in range(1, n)]
            rng.shuffle(edges)
            trees.append((n, edges))
        for n, edges in trees:
            diameter = max(map(max, distances(n, edges)))
            data = f"{n}\n" + "".join(f"{u+1} {v+1}\n" for u, v in edges)
            expect("tree_diameter", data, [diameter])

        # Iterativos devem funcionar numa cadeia longa sem depender da pilha recursiva.
        n = 20000
        edges = [(u-1, u) for u in range(1, n)]
        data = graph_input(n, edges)
        expect("bfs", data + "1\n", range(n))
        expect("bfs_multisource", data + f"2\n1 {n}\n", [min(u, n-1-u) for u in range(n)])
        expect("topological_sort", data, range(1, n+1))
        expect("tree_diameter", f"{n}\n" + data.split("\n", 1)[1], [n-1])

    print(f"OK: {len(names)} templates, {checks} execuções contra oráculos + cadeias de 20000 nós.")


if __name__ == "__main__":
    main()
