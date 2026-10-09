"""Na raiz icpc/: python -B c++/test_search.py. Compila os blocos de c++/search/."""

from bisect import bisect_left, bisect_right
import itertools
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile
import time

ROOT = Path(__file__).resolve().parents[1]
DOCS = ROOT / "c++" / "search"
LL_MAX = 2**63 - 1


class BuildDirectory(tempfile.TemporaryDirectory):
    def cleanup(self):
        # No Windows, o antivírus pode manter o .exe bloqueado após o processo sair.
        for attempt in range(30):
            try:
                super().cleanup()
                return
            except PermissionError:
                if attempt == 29:
                    raise
                time.sleep(0.2)


def examples():
    result = {}
    assert {path.name for path in DOCS.glob("*.md")} == {
        "README.md", "binary-search.md", "two-pointers.md", "sweep-line.md",
        "exhaustive-search.md", "patterns.md",
        "backtracking.md",
    }
    for path in DOCS.glob("*.md"):
        document = path.read_text(encoding="utf-8")
        blocks = re.findall(
            r"<!-- search-example: ([\w-]+) -->\s*```cpp\n(.*?)\n```",
            document, re.S,
        )
        assert len(blocks) == len(re.findall(r"^```cpp\s*$", document, re.M)), path
        for name, source in blocks:
            assert name not in result, name
            result[name] = source
    assert set(result) == {
        "linear", "binary", "bounds", "first-true", "last-true", "ceiling",
        "two-pointers-pair", "two-pointers-window", "sweep-line",
        "coordinate-compression", "exhaustive-pairs", "exhaustive-subsets",
        "exhaustive-permutations",
        "two-pointers-difference", "two-pointers-merge", "exhaustive-triples",
        "sweep-base", "prefix-events", "sweep-query", "active-structures",
    }
    return result


def compile_source(compiler, directory, name, source):
    executable = directory / (name + ".exe")
    process = subprocess.run(
        [compiler, "-x", "c++", "-", "-std=c++17", "-Wall", "-Wextra",
         "-Wpedantic", "-Werror", "-O0", "-D_GLIBCXX_DEBUG", "-o", str(executable)],
        input=source, text=True, capture_output=True, timeout=120,
    )
    assert process.returncode == 0, f"{name}: {process.stderr}"
    return executable


def run(executable, data=""):
    process = subprocess.run(
        [str(executable)], input=data, text=True, capture_output=True, timeout=20,
    )
    assert process.returncode == 0, f"{executable.name}: {process.stderr}"
    return process.stdout.strip().splitlines()


def input_case(values, parameter):
    return f"{len(values)} {parameter}\n" + " ".join(map(str, values)) + "\n"


def first_true_oracle(values, k):
    # Enumera cortes: independente do greedy usado no verify C++.
    best = sum(values)
    for mask in range(1 << (len(values) - 1)):
        if mask.bit_count() + 1 > k:
            continue
        groups = [0]
        for i, value in enumerate(values):
            groups[-1] += value
            if i < len(values) - 1 and mask & (1 << i):
                groups.append(0)
        best = min(best, max(groups))
    return best


def loop_harness(sources):
    pieces = ["#include <bits/stdc++.h>\n#include <cassert>\nusing namespace std;\nusing ll = long long;\n"]
    for namespace, name, operator in (
        ("First", "first-true", ">="), ("Last", "last-true", "<="),
    ):
        loop = re.search(r"    while \(l <= r\) \{.*?\n    \}", sources[name], re.S)
        assert loop, name
        pieces.append(
            f"namespace {namespace} {{\nll threshold;\n"
            f"bool verify(ll mid) {{ return mid {operator} threshold; }}\n"
            "ll search(ll l, ll r) { ll ans = -1;\n" + loop[0] +
            "\nreturn ans;\n}\n}\n"
        )
    pieces.append(r"""
int main() {
    for (ll l = 0; l <= 12; l++) {
        for (ll r = -1; r <= 12; r++) {
            for (ll threshold = -1; threshold <= 14; threshold++) {
                First::threshold = Last::threshold = threshold;
                ll first = -1, last = -1;
                for (ll x = l; x <= r; x++) {
                    if (x >= threshold && first == -1) first = x;
                    if (x <= threshold) last = x;
                }
                assert(First::search(l, r) == first);
                assert(Last::search(l, r) == last);
            }
        }
    }
    ll high = LLONG_MAX - 1;
    First::threshold = 0;
    assert(First::search(0, high) == 0); // todos verdadeiros
    First::threshold = high;
    assert(First::search(0, high) == high);
    First::threshold = LLONG_MAX;
    assert(First::search(0, high) == -1); // todos falsos
    Last::threshold = high;
    assert(Last::search(0, high) == high);
    Last::threshold = 0;
    assert(Last::search(0, high) == 0);
    Last::threshold = -1;
    assert(Last::search(0, high) == -1);
    cout << "loops ok\n";
}
""")
    return "".join(pieces)


def main():
    compiler = shutil.which("g++")
    assert compiler, "g++ precisa estar no PATH"
    sources = examples()
    rng = random.Random(107)
    cases = 0
    with BuildDirectory(prefix="icpc-search-") as folder:
        directory = Path(folder)
        executables = {}
        for name, source in sources.items():
            if name == "ceiling":
                # Fragmento: confere o teto pequeno e perto do máximo de long long.
                source = (
                    "#include <bits/stdc++.h>\n#include <cassert>\nusing namespace std;\nint main() {\n" +
                    source + "\nassert(ceiling == 4);\n" +
                    "a = LLONG_MAX; b = 2;\n"
                    "assert(a / b + (a % b != 0) == LLONG_MAX / 2 + 1);\n}\n"
                )
            elif "int main(" not in source:
                before, after = "", ""
                if name == "prefix-events":
                    # O trecho documentado depende de events já ordenado.
                    before = "vector<pair<long long, int>> events = {{1,1},{3,1},{4,-1},{6,-1}};\n"
                    after = "\nassert((accumulated == vector<long long>{1,2,1,0}));\n"
                source = (
                    "#include <bits/stdc++.h>\n#include <cassert>\nusing namespace std;\nint main() {\n" +
                    before + source + after + "\n}\n"
                )
            executables[name] = compile_source(compiler, directory, name, source)
            print(f"Compilou: {name}", flush=True)

        assert run(executables["bounds"]) == ["1", "1", "4", "3", "2", "5", "1"]
        assert run(executables["ceiling"]) == []
        assert run(executables["sweep-base"]) == ["1", "2", "1", "0"]
        assert run(executables["prefix-events"]) == []
        assert run(executables["active-structures"]) == ["2", "7 7", "2 2 7", "9", "2"]
        assert run(executables["exhaustive-triples"]) == ["4"]
        cases += 6

        for values in [[], [2], [1, 2, 2, 2, 5, 8], [-5, -2, 0]] + [
            [rng.randrange(-5, 6) for _ in range(rng.randrange(9))] for _ in range(16)
        ]:
            for target in [-8, 2, 10]:
                expected = values.index(target) if target in values else -1
                assert run(executables["linear"], input_case(values, target)) == [str(expected)]
                ordered = sorted(values)
                result = int(run(executables["binary"], input_case(ordered, target))[0])
                if target in ordered:
                    assert 0 <= result < len(ordered) and ordered[result] == target
                else:
                    assert result == -1
                cases += 2
        print("Busca linear e tradicional: ausência, vazios e repetidos OK", flush=True)

        # Só troca a entrada fixa do exemplo; testa as mesmas chamadas e guardas.
        bounds_source = sources["bounds"].replace(
            "vector<long long> v = {1, 2, 2, 2, 5, 8};\n    long long x = 2;",
            "int n; long long x; cin >> n >> x;\n"
            "    vector<long long> v(n); for (auto &value : v) cin >> value;",
        )
        assert bounds_source != sources["bounds"]
        bounds = compile_source(compiler, directory, "bounds-input", bounds_source)
        for values, target in itertools.product(
            [[], [2], [1, 2, 2, 2, 5, 8], [-5, -5, -1, 0]], [-8, -5, 0, 2, 3, 8, 9]
        ):
            lower, upper = bisect_left(values, target), bisect_right(values, target)
            expected = [int(target in values), lower, upper, upper - lower]
            if lower < len(values):
                expected.append(values[lower])
            if upper < len(values):
                expected.append(values[upper])
            expected.append(int(target in values))
            assert run(bounds, input_case(values, target)) == list(map(str, expected))
            cases += 1

        workloads = [([0], 1), ([0, 0, 0], 2), ([2, 3, 5], 2), ([9], 7)]
        workloads += [([rng.randrange(10) for _ in range(rng.randrange(1, 8))], rng.randrange(1, 9))
                      for _ in range(30)]
        for values, k in workloads:
            expected = first_true_oracle(values, k)
            assert run(executables["first-true"], input_case(values, k)) == [str(expected)]
            cases += 1
        for values, k, expected in [
            ([LL_MAX - 1], 1, LL_MAX - 1),
            ([LL_MAX - 2, 1], 2, LL_MAX - 2),
        ]:
            assert run(executables["first-true"], input_case(values, k)) == [str(expected)]
            cases += 1
        print("FIRST TRUE: comparação com todos os cortes e limites grandes OK", flush=True)

        lengths_cases = [([0], 1), ([1], 2), ([5, 8], 3), ([3, 3], 1)]
        lengths_cases += [([rng.randrange(15) for _ in range(rng.randrange(1, 8))], rng.randrange(1, 25))
                          for _ in range(30)]
        for values, k in lengths_cases:
            expected = max([size for size in range(1, max(values) + 1)
                            if sum(x // size for x in values) >= k], default=-1)
            assert run(executables["last-true"], input_case(values, k)) == [str(expected)]
            cases += 1
        for values, k, expected in [
            ([LL_MAX - 1], 1, LL_MAX - 1),
            ([LL_MAX - 1, LL_MAX - 1], LL_MAX, 1),
        ]:
            assert run(executables["last-true"], input_case(values, k)) == [str(expected)]
            cases += 1

        harness = compile_source(compiler, directory, "loop-boundaries", loop_harness(sources))
        assert run(harness) == ["loops ok"]

        pairs_cases = [([], 0), ([2], 4), ([2, 2, 2], 4), ([-5, -1, 0, 4], -1)]
        pairs_cases += [([rng.randrange(-8, 9) for _ in range(rng.randrange(9))], rng.randrange(-12, 13))
                        for _ in range(16)]
        for values, target in pairs_cases:
            expected = sum(a + b == target for a, b in itertools.combinations(values, 2))
            assert run(executables["exhaustive-pairs"], input_case(values, target)) == [str(expected)]
            ordered = sorted(values)
            result = run(executables["two-pointers-pair"], input_case(ordered, target))[0]
            if expected == 0:
                assert result == "-1"
            else:
                left, right = map(int, result.split())
                assert 0 <= left < right < len(ordered)
                assert ordered[left] + ordered[right] == target
            cases += 2

        windows = [([], 0), ([0, 0, 0], 0), ([9, 9], 1), ([2, 1, 3, 1, 1], 5)]
        windows += [([rng.randrange(10) for _ in range(rng.randrange(9))], rng.randrange(20))
                    for _ in range(12)]
        for values, limit in windows:
            expected = max([0] + [r - l for l in range(len(values))
                                  for r in range(l + 1, len(values) + 1)
                                  if sum(values[l:r]) <= limit])
            assert run(executables["two-pointers-window"], input_case(values, limit)) == [str(expected)]
            cases += 1
        print("Two pointers: pares e janelas comparados com força bruta OK", flush=True)

        differences = [([], 0), ([2], 0), ([2, 2], 0), ([-5, -1, 0, 4], 4),
                       ([1, 4, 9], 2), ([-10**18, 10**18], 2 * 10**18)]
        differences += [(sorted(rng.randrange(-9, 10) for _ in range(rng.randrange(9))), rng.randrange(12))
                        for _ in range(12)]
        for values, target in differences:
            expected = any(abs(a - b) == target for a, b in itertools.combinations(values, 2))
            result = run(executables["two-pointers-difference"], input_case(values, target))[0]
            if expected:
                l, r = map(int, result.split())
                assert 0 <= l < r < len(values) and values[r] - values[l] == target
            else:
                assert result == "-1"
            cases += 1

        merges = [([], []), ([], [1, 1]), ([1, 2], []), ([-LL_MAX - 1], [LL_MAX])]
        merges += [(sorted(rng.randrange(-9, 10) for _ in range(rng.randrange(9))),
                    sorted(rng.randrange(-9, 10) for _ in range(rng.randrange(9)))) for _ in range(12)]
        for a, b in merges:
            data = f"{len(a)} {len(b)}\n" + " ".join(map(str, a)) + "\n" + " ".join(map(str, b)) + "\n"
            expected = [" ".join(map(str, sorted(a + b)))] if a or b else []
            assert run(executables["two-pointers-merge"], data) == expected
            cases += 1
        print("Two difference e merge: diferença zero, negativos, vazios e extremos OK", flush=True)

        coordinate_cases = [[], [0], [100, 5, 100, 10**9], [-5, -5, -1, 0], [-LL_MAX - 1, LL_MAX]]
        coordinate_cases += [[rng.randrange(-9, 10) for _ in range(rng.randrange(9))] for _ in range(12)]
        for values in coordinate_cases:
            ids = {x: i for i, x in enumerate(sorted(set(values)))}
            expected = [f"{x} -> {ids[x]}" for x in values]
            data = f"{len(values)}\n" + " ".join(map(str, values)) + "\n"
            assert run(executables["coordinate-compression"], data) == expected
            cases += 1

        subsets = [([], 0), ([], 3), ([0, 0, 0], 0), ([1, 2, 3], 3), ([-5, 2, 3], 0)]
        subsets += [([rng.randrange(-5, 6) for _ in range(rng.randrange(9))], rng.randrange(-7, 8))
                    for _ in range(12)]
        for values, target in subsets:
            expected = sum(sum(choice) == target for size in range(len(values) + 1)
                           for choice in itertools.combinations(values, size))
            assert run(executables["exhaustive-subsets"], input_case(values, target)) == [str(expected)]
            cases += 1
        for text in ["a", "aba", "cba", "aaaa", "abca"]:
            expected = sorted({"".join(choice) for choice in itertools.permutations(text)})
            assert run(executables["exhaustive-permutations"], text + "\n") == expected
            cases += 1

        interval_cases = [[], [(1, 3), (3, 5)], [(1, 3), (1, 3)],
                          [(-5, 3), (-1, 0), (2, 2)], [(-LL_MAX - 1, LL_MAX)]]
        interval_cases += [[tuple(sorted((rng.randrange(-9, 10), rng.randrange(-9, 10))))
                            for _ in range(rng.randrange(9))] for _ in range(12)]
        # Compila exatamente as duas adaptações de empate explicadas para [L,R].
        closed_source = sources["sweep-query"].replace(
            "enum { END = 0, START = 1, QUERY = 2 };",
            "enum { START = 0, QUERY = 1, END = 2 };",
        ).replace("if (l == r) continue; // [l,l) é vazio", "")
        assert closed_source != sources["sweep-query"]
        closed_query = compile_source(compiler, directory, "sweep-query-closed", closed_source)
        for intervals in interval_cases:
            positions = sorted({x for pair in intervals for x in pair})
            queries = sorted(set([-LL_MAX - 1, LL_MAX, -10, -1, 0, 1, 3, 5, 10, *positions]))
            queries += [0, 3] # repetidas e fora de ordem: resposta deve preservar ids
            rng.shuffle(queries)
            active = lambda x: sum(l <= x < r for l, r in intervals)
            maximum = max(map(active, positions), default=0)
            data = f"{len(intervals)}\n" + "".join(f"{l} {r}\n" for l, r in intervals)
            data += f"{len(queries)}\n" + " ".join(map(str, queries)) + "\n"
            expected = [str(maximum), *[str(active(x)) for x in queries]]
            assert run(executables["sweep-line"], data) == expected
            assert run(executables["sweep-query"], data) == expected[1:]
            closed_expected = [str(sum(l <= x <= r for l, r in intervals)) for x in queries]
            assert run(closed_query, data) == closed_expected
            cases += 3
        print("Compressão, exaustiva e sweep line: duplicados, empates e extremos OK", flush=True)
    print(f"OK: {len(sources)} blocos C++, {cases} execuções e 2912 combinações de limites/monotonicidade.")


if __name__ == "__main__":
    main()
