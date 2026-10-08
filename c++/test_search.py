"""Na raiz icpc/: python -B c++/test_search.py. Compila os blocos reais de search/."""

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
DOCS = ROOT / "search"
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
    assert set(result) == {"linear", "binary", "bounds", "first-true", "last-true", "ceiling"}
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
            executables[name] = compile_source(compiler, directory, name, source)
            print(f"Compilou: {name}", flush=True)

        assert run(executables["bounds"]) == ["1", "1", "4", "3", "2", "5", "1"]
        assert run(executables["ceiling"]) == []
        cases += 2

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
    print(f"OK: 6 blocos C++, {cases} execuções e 2912 combinações de limites/monotonicidade.")


if __name__ == "__main__":
    main()
