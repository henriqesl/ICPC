"""Na raiz icpc: python -B c++/test_dp.py. C++17, exemplos e oráculos pequenos."""
from functools import lru_cache
import itertools
import math
from pathlib import Path
import random
import re
import shutil
import subprocess

from test_search import BuildDirectory, compile_source

ROOT = Path(__file__).resolve().parent / "dp"
MOD = 1000000007
NAMES = {
    "fibonacci_bruteforce", "fibonacci_memo", "fibonacci_iterative",
    "dice_combinations_bruteforce", "dice_combinations_memo", "dice_combinations_iterative",
    "subordinates", "expected_moves", "winning_states", "subset_sum",
    "frog_1", "frog_1_iterative", "grid_paths", "vacation", "vacation_iterative",
    "rectangle_cutting", "kadane", "knapsack_01", "lcs", "lcs_reconstruct", "lis",
}


def subsequence(small, large):
    it = iter(large)
    return all(any(c == x for c in it) for x in small)


def subsets(values):
    for mask in range(1 << len(values)):
        yield [x for i, x in enumerate(values) if mask & (1 << i)]


def lcs_oracle(a, b):
    if len(a) > len(b):
        a, b = b, a
    return max(len(s) for s in subsets(a) if subsequence(s, b))


def frog_oracle(heights):
    costs = []
    def visit(i, cost):
        if i == len(heights) - 1:
            costs.append(cost)
        for jump in (1, 2):
            if i + jump < len(heights):
                visit(i + jump, cost + abs(heights[i + jump] - heights[i]))
    visit(0, 0)
    return min(costs)


def grid_oracle(grid):
    n = len(grid)
    if grid[0][0] == "*":
        return 0
    answer = 0
    for down_steps in itertools.combinations(range(2 * n - 2), n - 1):
        down_steps = set(down_steps)
        r = c = 0
        valid = True
        for step in range(2 * n - 2):
            if step in down_steps:
                r += 1
            else:
                c += 1
            if grid[r][c] == "*":
                valid = False
                break
        answer += valid
    return answer % MOD


@lru_cache(None)
def game_oracle(n):
    return any(not game_oracle(n - take) for take in range(1, (n + 1) // 2 + 1))


def main():
    compiler = shutil.which("g++")
    assert compiler, "g++ precisa estar no PATH"
    assert {path.stem for path in ROOT.glob("*.cpp")} == NAMES
    rng = random.Random(20261030)
    checks = 0
    with BuildDirectory(prefix="icpc-dp-") as temp:
        directory = Path(temp)
        binaries = {}
        for name in sorted(NAMES):
            source = (ROOT / (name + ".cpp")).read_text(encoding="utf-8")
            assert "COMO LER ESTE CÓDIGO" in source
            binaries[name] = compile_source(compiler, directory, name, source)
            print("Compilou:", name, flush=True)

        def execute(name, data):
            nonlocal checks
            result = subprocess.run([str(binaries[name])], input=data, text=True,
                                    capture_output=True, timeout=25)
            assert result.returncode == 0, (name, data, result.stderr)
            checks += 1
            return result.stdout

        def expect(name, data, expected):
            actual = execute(name, data).split()
            assert actual == str(expected).split(), (name, data, actual, expected)

        fib = [0, 1]
        for _ in range(91):
            fib.append(fib[-1] + fib[-2])
        for n in list(range(16)) + [46, 92]:
            for name in ("fibonacci_memo", "fibonacci_iterative"):
                expect(name, f"{n}\n", fib[n])
            if n <= 10:
                expect("fibonacci_bruteforce", f"{n}\n", fib[n])

        dice = [1]
        for n in range(1, 100001):
            dice.append(sum(dice[max(0, n - 6):n]) % MOD)
        for n in list(range(10)) + [20, 50, 100, 1000]:
            for name in ("dice_combinations_memo", "dice_combinations_iterative"):
                expect(name, f"{n}\n", dice[n])
            if n < 10:
                expect("dice_combinations_bruteforce", f"{n}\n", dice[n])
        expect("dice_combinations_iterative", "100000\n", dice[100000])

        trees = [[], [1], [1, 1, 1], [1, 2, 3, 4]]
        for _ in range(18):
            trees.append([rng.randrange(1, u) for u in range(2, rng.randrange(2, 12))])
        for bosses in trees:
            n = len(bosses) + 1
            answer = [0] * (n + 1)
            parent = [0, 0] + bosses
            for u in range(2, n + 1):
                boss = parent[u]
                while boss:
                    answer[boss] += 1
                    boss = parent[boss]
            expect("subordinates", f"{n}\n" + " ".join(map(str, bosses)),
                   " ".join(map(str, answer[1:])))

        for n, k in [(0, 1), (0, 3), (1, 1), (3, 1), (1, 2), (3, 2), (5, 3), (10, 1000), (4, 2.5)]:
            text = execute("expected_moves", f"{n} {k}\n").strip()
            if n > 0 and k == 1:
                assert text == "INF"
            else:
                expected = 0 if n == 0 else n * k / (k - 1)
                assert math.isclose(float(text), expected, rel_tol=1e-9, abs_tol=1e-9)
        for n in list(range(22)) + [100]:
            expect("winning_states", f"{n}\n", "VENCEDOR" if game_oracle(n) else "PERDEDOR")

        subset_cases = [([], 0), ([], 3), ([0, 0], 0), ([2], 4),
                        ([3, 34, 4, 12, 5, 2], 9), ([2, 2], 4)]
        subset_cases += [([rng.randrange(12) for _ in range(rng.randrange(9))], rng.randrange(25))
                         for _ in range(25)]
        for values, target in subset_cases:
            expected = any(sum(s) == target for s in subsets(values))
            data = f"{len(values)} {target}\n" + " ".join(map(str, values))
            expect("subset_sum", data, "SIM" if expected else "NAO")

        frogs = [[10], [10, 30, 40, 20], [0, 5000000000], [5, 5, 5]]
        frogs += [[rng.randrange(50) for _ in range(rng.randrange(1, 10))] for _ in range(22)]
        for heights in frogs:
            data = f"{len(heights)}\n" + " ".join(map(str, heights))
            for name in ("frog_1", "frog_1_iterative"):
                expect(name, data, frog_oracle(heights))

        grids = [["."], ["*"], ["..", ".."], ["*.", ".."], ["..", ".*"]]
        for _ in range(25):
            n = rng.randrange(1, 6)
            grids.append(["".join("*" if rng.random() < 0.3 else "." for _ in range(n)) for _ in range(n)])
        for grid in grids:
            expect("grid_paths", f"{len(grid)}\n" + "\n".join(grid), grid_oracle(grid))
        expect("grid_paths", "20\n" + ("." * 20 + "\n") * 20, math.comb(38, 19) % MOD)

        vacations = [[], [[0, 0, 0]], [[10, 40, 70], [20, 50, 80], [30, 60, 90]],
                     [[3000000000] * 3, [3000000000] * 3]]
        vacations += [[[rng.randrange(20) for _ in range(3)] for _ in range(rng.randrange(7))]
                      for _ in range(20)]
        for points in vacations:
            n = len(points)
            expected = max(sum(points[d][a] for d, a in enumerate(choices))
                           for choices in itertools.product(range(3), repeat=n)
                           if all(choices[i] != choices[i-1] for i in range(1, n)))
            data = f"{n}\n" + "\n".join(" ".join(map(str, day)) for day in points)
            for name in ("vacation", "vacation_iterative"):
                expect(name, data, expected)

        cuts = [[0] * 7 for _ in range(7)]
        for a in range(1, 7):
            for b in range(1, 7):
                if a != b:
                    options = [1 + cuts[i][b] + cuts[a-i][b] for i in range(1, a)]
                    options += [1 + cuts[a][j] + cuts[a][b-j] for j in range(1, b)]
                    cuts[a][b] = min(options)
                expect("rectangle_cutting", f"{a} {b}\n", cuts[a][b])

        arrays = [[-5, -2, -8], [0], [-2, 1, -3, 4, -1, 2, 1, -5, 4], [4000000000, 4000000000, -1]]
        arrays += [[rng.randrange(-15, 16) for _ in range(rng.randrange(1, 10))] for _ in range(25)]
        for values in arrays:
            expected = max(sum(values[l:r]) for l in range(len(values)) for r in range(l+1, len(values)+1))
            expect("kadane", f"{len(values)}\n" + " ".join(map(str, values)), expected)

        bags = [([], 0), ([], 5), ([(0, 7), (0, 3), (1, 9)], 0),
                ([(3, 4), (4, 5), (2, 3), (6, 7)], 7), ([(1, 5000000000)], 1)]
        bags += [([(rng.randrange(9), rng.randrange(20)) for _ in range(rng.randrange(9))], rng.randrange(15))
                 for _ in range(24)]
        for items, capacity in bags:
            expected = max(sum(v for w, v in s) for s in subsets(items) if sum(w for w, v in s) <= capacity)
            data = f"{len(items)} {capacity}\n" + "\n".join(f"{w} {v}" for w, v in items)
            expect("knapsack_01", data, expected)

        pairs = [("", ""), ("", "abc"), ("abc", ""), ("ABCDGH", "AEDFHR"),
                 ("abc", "def"), ("aaaa", "aa"), (" a ", " a ")]
        pairs += [("".join(rng.choices("abc", k=rng.randrange(7))),
                   "".join(rng.choices("abc", k=rng.randrange(7)))) for _ in range(24)]
        for a, b in pairs:
            data = a + "\n" + b + "\n"
            expected = lcs_oracle(a, b)
            expect("lcs", data, expected)
            lines = execute("lcs_reconstruct", data).splitlines()
            assert len(lines) == 2, (a, b, lines)
            length, recovered = int(lines[0]), lines[1]
            assert length == len(recovered) == expected, (a, b, lines, expected)
            assert subsequence(recovered, a) and subsequence(recovered, b)
        for s in ["", "bbbab", "character", "abcd", "aaaa"]:
            expected = max(len(part) for part in subsets(s) if part == part[::-1])
            expect("lcs", s + "\n" + s[::-1] + "\n", expected)

        sequences = [[], [2, 2, 2], [10, 2, 5, 3, 7, 18], [-3, -2, -1]]
        sequences += [[rng.randrange(-10, 11) for _ in range(rng.randrange(10))] for _ in range(24)]
        for values in sequences:
            expected = max(len(s) for s in subsets(values) if all(x < y for x, y in zip(s, s[1:])))
            expect("lis", f"{len(values)}\n" + " ".join(map(str, values)), expected)

        guide = (ROOT / "dp-1.md").read_text(encoding="utf-8")
        snippets = re.findall(r"<!-- dp-example: ([\w-]+) -->\s*```cpp\n(.*?)\n```", guide, re.S)
        assert len(snippets) == len(re.findall(r"^```cpp\s*$", guide, re.M)) == 6
        for name, snippet in snippets:
            prefix = "#include <bits/stdc++.h>\nusing namespace std;\n"
            if name.endswith("iterative"):
                program = prefix + "int main() { int n = 8;\n" + snippet + "\n}\n"
            else:
                setup = "memo.assign(9, -1);" if name.endswith("memo") else ""
                program = prefix + snippet + '\nint main() { ' + setup + " cout << solve(8); }\n"
            binary = compile_source(compiler, directory, "guide-" + name, program)
            expected = "21" if name.startswith("fib") else "125"
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=20)
            assert result.returncode == 0 and result.stdout.strip() == expected, (name, result.stderr)
            checks += 1

    print(f"OK: 21 programas, 6 trechos do guia, {checks} execucoes; oraculos e casos-limite.", flush=True)


if __name__ == "__main__":
    main()
