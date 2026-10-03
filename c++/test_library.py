"""Compila toda a trilha C++17 e executa exemplos e casos contra força bruta.
Na raiz icpc: python -B "c++/test_library.py". Requer g++ no PATH.
Executáveis/objetos ficam apenas em uma pasta temporária.
"""
from pathlib import Path
import itertools
import math
import random
import re
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parent


def main():
    compiler = shutil.which("g++")
    if compiler is None:
        raise SystemExit("g++ não encontrado no PATH")
    cases = [
        ("template.cpp", "", ""),
        ("basics/io.cpp", "4 1 2 3 4", "10"),
        ("basics/io.cpp", "0", "0"),
        ("basics/strings.cpp", "", "3 4 7 d abc 123"),
        ("data-structures/deque.cpp", "", "1 3 2"),
        ("data-structures/pair.cpp", "", "1:1 3:0 3:2"),
        ("data-structures/stack.cpp", "([{}])", "balanceado"),
        ("data-structures/stack.cpp", "([)]", "desbalanceado"),
        ("data-structures/stack.cpp", ")", "desbalanceado"),
        ("data-structures/queue.cpp", "2 Ana Bia", "Ana Bia"),
        ("basics/set.cpp", "4 3 1 3 8", "1 3 8 menor=1 maior=8"),
        ("basics/set.cpp", "0", "vazio"),
        ("basics/set.cpp", "3 -5 -5 -5", "-5 menor=-5 maior=-5"),
        ("basics/map.cpp", "4 3 3 8 3", "3: 3 8: 1 menor_chave=3 maior_chave=8"),
        ("basics/map.cpp", "0", "vazio"),
        ("data-structures/priority-queue.cpp", "4 -3 9 9 2", "9 9 2 -3 -3 2 9 9"),
        ("data-structures/priority-queue.cpp", "0", ""),
        ("basics/vector.cpp", "4 3 1 3 8 3",
         "indice=0 ocorrencias=2 1 3 3 8 primeiro=1 ultimo=8 sem_x: 1 8 distintos: 1 3 8"),
        ("basics/vector.cpp", "0 3", "indice=-1 ocorrencias=0 vazio sem_x: distintos:"),
        ("basics/vector.cpp", "3 -2 -2 -2 -2",
         "indice=0 ocorrencias=3 -2 -2 -2 primeiro=-2 ultimo=-2 sem_x: distintos: -2"),
        ("algorithms/linear-search.cpp", "3 8 1 8 8", "0"),
        ("algorithms/linear-search.cpp", "0 8", "-1"),
        ("algorithms/binary-search.cpp", "4 1 3 3 8 3", "1"),
        ("algorithms/binary-search.cpp", "0 8", "-1"),
        ("algorithms/prefix-sum.cpp", "3 2 -1 4 2 0 2 1 1", "5 -1"),
        ("algorithms/prefix-sum.cpp", "2 3000000000 3000000000 1 0 1", "6000000000"),
        ("algorithms/sorting.cpp", "3 2 1 3", "1 2 3 3 2 1"),
        ("algorithms/greedy.cpp", "0", "0"),
        ("math/number-theory.cpp", "12 18", "1 2 3 4 6 12 false 6 36"),
        ("math/number-theory.cpp", "1 1", "1 false 1 1"),
        ("basics/unordered-map.cpp", "4 3 3 8 3 3 3 8 7", "3 1 0"),
        ("basics/unordered-map.cpp", "0 2 7 7", "0 0"),
        ("basics/multiset.cpp", "5 3 1 3 8 3 3", "1 3 3 8 menor=1 maior=8 restantes=2"),
        ("basics/multiset.cpp", "2 1 1 9", "1 1 menor=1 maior=1 restantes=0"),
        ("basics/multiset.cpp", "1 3 3", "vazio restantes=0"),
        ("basics/multiset.cpp", "0 3", "vazio restantes=0"),
        ("data-structures/queue.cpp", "0", ""),
        ("algorithms/sliding-window-fixed.cpp", "3 2 -5 -2 -7", "-7"),
        ("algorithms/sliding-window-variable.cpp", "3 0 0 0 0", "3"),
        ("algorithms/bounds.cpp", "5 1 3 3 8 10 3 3 8",
         "lower=1 upper=3 iguais=2 intervalo=3 menor_que=1 menor_igual=3 maior_igual=3 maior_que=8"),
        ("algorithms/bounds.cpp", "0 0 -1 1",
         "lower=0 upper=0 iguais=0 intervalo=0 menor_que=nenhum menor_igual=nenhum maior_igual=nenhum maior_que=nenhum"),
        ("algorithms/difference-array.cpp", "4 2 1 2 3 4 0 2 10 1 3 -2", "11 10 11 2"),
        ("algorithms/difference-array.cpp", "0 0", ""),
        ("algorithms/sliding-window-distinct.cpp", "6 2 1 2 1 3 3 2", "3"),
        ("algorithms/sliding-window-distinct.cpp", "3 0 1 1 1", "0"),
        ("algorithms/monotonic-stack.cpp", "3 3 1 2", "-1 -1 1 1 -1 -1"),
        ("algorithms/monotonic-stack.cpp", "0", ""),
        ("algorithms/monotonic-stack.cpp", "4 2 2 2 2", "-1 -1 -1 -1 -1 -1 -1 -1"),
        ("algorithms/monotonic-deque.cpp", "5 3 2 1 5 1 3", "5 5 5"),
        ("algorithms/monotonic-deque.cpp", "5 3 -5 -2 -7 -1 -1", "-2 -1 -1"),
        ("algorithms/monotonic-deque.cpp", "3 1 4 -2 4", "4 -2 4"),
        ("algorithms/monotonic-deque.cpp", "3 3 4 -2 4", "4"),
    ]
    checks = 0
    with tempfile.TemporaryDirectory(prefix="icpc-cpp-") as temp:
        binaries = {}
        for i, source in enumerate(sorted(ROOT.rglob("*.cpp"))):
            relative = source.relative_to(ROOT).as_posix()
            executable = "int main(" in source.read_text(encoding="utf-8")
            output = Path(temp) / (str(i) + (".exe" if executable else ".o"))
            command = [compiler, "-std=c++17", "-Wall", "-Wextra", "-Wpedantic",
                       "-O0", "-D_GLIBCXX_DEBUG", str(source), "-o", str(output)]
            if not executable:
                command.insert(1, "-c")
            result = subprocess.run(command, capture_output=True, text=True, timeout=60)
            if result.returncode:
                raise AssertionError(relative + "\n" + result.stderr)
            if result.stderr:
                print(result.stderr)
            if executable:
                binaries[relative] = output
            print("Compilado:", relative, flush=True)

        # Recortes marcados nas referências: cada um compila em um escopo independente.
        expected_snippets = {
            "vector": "7 8", "array": "2 1", "pair": "3 1", "frequency": "2 1",
            "map": "21", "unordered-map": "0", "set": "1", "multiset": "1 3 5 8",
            "unordered-set": "1 1", "stack": "[ (", "queue": "Ana Bia", "deque": "1 3 2",
            "max-heap": "9 5", "min-heap": "2 5", "median": "3", "sort": "1 3 3 8",
            "comparator": "10:1 10:2 8:0", "lower-bound": "3 1", "pair-bound": "1",
            "upper-bound": "8 3", "binary-search": "1", "two-pointers": "1 3",
            "monotonic-stack": "-1 -1 1", "monotonic-deque": "5 5 5",
            "prefix-sum": "8", "sliding-window": "8 7", "fenwick": "7",
        }
        snippets = []
        docs = sorted([*ROOT.parent.glob("*.md"), *ROOT.rglob("*.md")])
        for doc in docs:
            snippets.extend(re.findall(r"<!-- example:\s*([\w-]+)\s*-->\s*```cpp\n(.*?)\n```",
                                       doc.read_text(encoding="utf-8"), re.S))
        names = [name for name, _ in snippets]
        assert len(names) == len(set(names)), "identificador de recorte repetido"
        assert set(names) == set(expected_snippets), (set(names) ^ set(expected_snippets))
        extra_checks = {
            "vector": "assert(v.size() == 3 && v.back() == 3);",
            "array": "assert(freq[0] == 0 && freq[1] == 0);",
            "frequency": "assert(freq.count(sai) == 0);",
            "map": 'assert(idade.count("Bia") == 0);',
            "unordered-map": "assert(freq.count(8) == 0);",
            "set": "assert(s.size() == 3 && s.count(9) == 0);",
            "unordered-set": "assert(vistos.count(8) == 0);",
            "stack": "assert(s.top() == '(');",
            "queue": 'assert(fila.front() == "Bia");',
            "deque": "assert(d.size() == 1 && d.front() == 2);",
            "median": "assert(baixo.size() == 3 && alto.size() == 2 && *baixo.rbegin() <= *alto.begin());",
            "monotonic-stack": "assert((anterior == vector<int>{-1, -1, 1}));",
        }
        source = "#include <bits/stdc++.h>\n#include <cassert>\nusing namespace std;\nint main() {\n"
        for name, snippet in snippets:
            source += "{\n" + snippet + "\n" + extra_checks.get(name, "") + '\ncout << char(31);\n}\n'
        source += "}\n"
        guide_binary = Path(temp) / "references.exe"
        result = subprocess.run([compiler, "-std=c++17", "-Wall", "-Wextra", "-Wpedantic",
                                 "-Werror", "-O0", "-D_GLIBCXX_DEBUG", "-x", "c++", "-",
                                 "-o", str(guide_binary)], input=source, text=True,
                                capture_output=True, timeout=60)
        assert result.returncode == 0, result.stderr
        result = subprocess.run([str(guide_binary)], capture_output=True, text=True, timeout=5)
        assert result.returncode == 0, result.stderr
        outputs = result.stdout.split(chr(31))
        assert len(outputs) == len(snippets) + 1 and outputs[-1] == ""
        for (name, _), actual in zip(snippets, outputs):
            expected = expected_snippets[name]
            assert actual.split() == expected.split(), (name, actual, expected)
        print(f"OK: {len(snippets)} recortes das referências compilados e verificados.", flush=True)

        def run(relative, data):
            nonlocal checks
            result = subprocess.run([str(binaries[relative])], input=data, text=True,
                                    capture_output=True, timeout=5)
            if result.returncode:
                raise AssertionError(relative + "\n" + result.stderr)
            checks += 1
            return result.stdout.split()

        for relative, data, expected in cases:
            assert run(relative, data) == expected.split(), (relative, data)
        rng = random.Random(42)
        for _ in range(40):
            v = sorted(rng.randrange(-8, 9) for _ in range(rng.randrange(10)))
            target = rng.randrange(-16, 17)
            data = " ".join(map(str, [len(v), *v, target]))
            answer = run("algorithms/two-pointers.cpp", data)
            exists = any(a+b == target for a,b in itertools.combinations(v, 2))
            assert (answer != ["-1"]) == exists
            if exists:
                i,j = map(int, answer)
                assert 0 <= i < j < len(v) and v[i]+v[j] == target
            index = next((i for i,x in enumerate(v) if x >= target), -1)
            assert run("algorithms/binary-search.cpp", data) == [str(index)]
        for _ in range(30):
            intervals = []
            for _ in range(rng.randrange(7)):
                start = rng.randrange(-5, 6)
                intervals.append((start, start+rng.randrange(1, 5)))
            best = 0
            for mask in range(1 << len(intervals)):
                subset = sorted(x for i,x in enumerate(intervals) if mask & (1 << i))
                if all(a[1] <= b[0] for a,b in zip(subset, subset[1:])):
                    best = max(best, len(subset))
            data = " ".join(map(str, [len(intervals), *itertools.chain.from_iterable(intervals)]))
            assert run("algorithms/greedy.cpp", data) == [str(best)]
        for n in range(1, 61):
            divisors = [d for d in range(1, n+1) if n%d == 0]
            expected = [*map(str, divisors), str(len(divisors)==2).lower(),
                        str(math.gcd(n,18)), str(math.lcm(n,18))]
            assert run("math/number-theory.cpp", f"{n} 18") == expected
        for a,b,m in [(2,10,1000), (0,0,1), (9,0,7), (10**18,99,10**9)]:
            assert run("math/modular-power.cpp", f"{a} {b} {m}") == [str(pow(a,b,m))]
        assert run("math/number-theory.cpp", "2 9223372036854775807")[-1] == "overflow"
        for _ in range(60):
            n = rng.randrange(1, 14)
            k = rng.randrange(1, n + 1)
            v = [rng.randrange(-12, 13) for _ in range(n)]
            expected = max(sum(v[i:i+k]) for i in range(n-k+1))
            data = " ".join(map(str, [n, k, *v]))
            assert run("algorithms/sliding-window-fixed.cpp", data) == [str(expected)]

            v = [rng.randrange(8) for _ in range(n)]
            limit = rng.randrange(20)
            expected = max([0] + [r-l for l in range(n) for r in range(l+1,n+1)
                                  if sum(v[l:r]) <= limit])
            data = " ".join(map(str, [n, limit, *v]))
            assert run("algorithms/sliding-window-variable.cpp", data) == [str(expected)]
        for _ in range(50):
            v = [rng.randrange(-6, 7) for _ in range(rng.randrange(12))]
            x = rng.randrange(-8, 9)
            l, r = sorted([rng.randrange(-8, 9), rng.randrange(-8, 9)])
            s = sorted(v)
            lower = sum(a < x for a in s)
            upper = sum(a <= x for a in s)
            def last_or_none(items):
                return str(items[-1]) if items else "nenhum"
            def first_or_none(items):
                return str(items[0]) if items else "nenhum"
            expected = [f"lower={lower}", f"upper={upper}",
                        f"iguais={v.count(x)}", f"intervalo={sum(l <= a <= r for a in v)}",
                        "menor_que=" + last_or_none([a for a in s if a < x]),
                        "menor_igual=" + last_or_none([a for a in s if a <= x]),
                        "maior_igual=" + first_or_none([a for a in s if a >= x]),
                        "maior_que=" + first_or_none([a for a in s if a > x])]
            data = " ".join(map(str, [len(v), *v, x, l, r]))
            assert run("algorithms/bounds.cpp", data) == expected

            k = rng.randrange(5)
            expected_length = max([0] + [j-i for i in range(len(v))
                                  for j in range(i+1, len(v)+1) if len(set(v[i:j])) <= k])
            data = " ".join(map(str, [len(v), k, *v]))
            assert run("algorithms/sliding-window-distinct.cpp", data) == [str(expected_length)]

            if v:
                updates = []
                final = v[:]
                for _ in range(rng.randrange(10)):
                    l, r = sorted([rng.randrange(len(v)), rng.randrange(len(v))])
                    delta = rng.randrange(-10, 11)
                    updates.extend([l, r, delta])
                    for i in range(l, r+1):
                        final[i] += delta
                data = " ".join(map(str, [len(v), len(updates)//3, *v, *updates]))
                assert run("algorithms/difference-array.cpp", data) == list(map(str, final))
        for _ in range(60):
            v = [rng.randrange(-5, 6) for _ in range(rng.randrange(15))]
            left = [next((j for j in range(i-1, -1, -1) if v[j] < v[i]), -1)
                    for i in range(len(v))]
            right = [next((j for j in range(i+1, len(v)) if v[j] < v[i]), -1)
                     for i in range(len(v))]
            data = " ".join(map(str, [len(v), *v]))
            assert run("algorithms/monotonic-stack.cpp", data) == list(map(str, left + right))

            values = v or [0]
            k = rng.randrange(1, len(values) + 1)
            expected = [max(values[i:i+k]) for i in range(len(values)-k+1)]
            data = " ".join(map(str, [len(values), k, *values]))
            assert run("algorithms/monotonic-deque.cpp", data) == list(map(str, expected))
        print(f"OK: {len(binaries)} executáveis; {checks} execuções verificadas.")


if __name__ == "__main__":
    main()
