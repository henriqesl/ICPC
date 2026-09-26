"""Compila toda a trilha C++17 e executa exemplos e casos contra força bruta.
Na raiz icpc: python -B "c++/tests/test_library.py". Requer g++ no PATH.
Executáveis/objetos ficam apenas em uma pasta temporária.
"""
from pathlib import Path
import itertools
import math
import random
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    compiler = shutil.which("g++")
    if compiler is None:
        raise SystemExit("g++ não encontrado no PATH")
    cases = [
        ("template.cpp", "", ""),
        ("basics/io.cpp", "4 1 2 3 4", "10"),
        ("basics/io.cpp", "0", "0"),
        ("strings/conversions.cpp", "", "3 4 7 d abc 123"),
        ("data-structures/deque/deque-example.cpp", "", "1 3 2"),
        ("data-structures/pair/pair-example.cpp", "", "1:1 3:0 3:2"),
        ("data-structures/stack/balanced-parentheses-main.cpp", "([{}])", "balanceado"),
        ("data-structures/stack/balanced-parentheses-main.cpp", "([)]", "desbalanceado"),
        ("data-structures/stack/balanced-parentheses-main.cpp", ")", "desbalanceado"),
        ("data-structures/queue/queue-example.cpp", "2 Ana Bia", "Ana Bia"),
        ("data-structures/set/set-example.cpp", "4 3 1 3 8", "1 3 8"),
        ("data-structures/map/frequency-map.cpp", "4 3 3 8 3", "3: 3 8: 1"),
        ("data-structures/priority-queue/priority-queue-example.cpp", "4 -3 9 9 2", "9 9 2 -3"),
        ("basics/useful-operations/vector-operations.cpp", "4 3 1 3 8 3", "indice=0 ocorrencias=2 1 3 3 8"),
        ("basics/useful-operations/vector-operations.cpp", "0 3", "indice=-1 ocorrencias=0"),
        ("algorithms/searching/linear-search.cpp", "3 8 1 8 8", "0"),
        ("algorithms/searching/linear-search.cpp", "0 8", "-1"),
        ("algorithms/searching/binary-search-main.cpp", "4 1 3 3 8 3", "1"),
        ("algorithms/searching/binary-search-main.cpp", "0 8", "-1"),
        ("algorithms/prefix-sum/prefix-sum-main.cpp", "3 2 -1 4 2 0 2 1 1", "5 -1"),
        ("algorithms/prefix-sum/prefix-sum-main.cpp", "2 3000000000 3000000000 1 0 1", "6000000000"),
        ("algorithms/sorting/sorting-example.cpp", "3 2 1 3", "1 2 3 3 2 1"),
        ("algorithms/greedy/intervals.cpp", "0", "0"),
        ("math/number-theory.cpp", "12 18", "1 2 3 4 6 12 false 6 36"),
        ("math/number-theory.cpp", "1 1", "1 false 1 1"),
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
            answer = run("algorithms/two-pointers/two-pointers.cpp", data)
            exists = any(a+b == target for a,b in itertools.combinations(v, 2))
            assert (answer != ["-1"]) == exists
            if exists:
                i,j = map(int, answer)
                assert 0 <= i < j < len(v) and v[i]+v[j] == target
            index = next((i for i,x in enumerate(v) if x >= target), -1)
            assert run("algorithms/searching/binary-search-main.cpp", data) == [str(index)]
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
            assert run("algorithms/greedy/intervals.cpp", data) == [str(best)]
        for n in range(1, 61):
            divisors = [d for d in range(1, n+1) if n%d == 0]
            expected = [*map(str, divisors), str(len(divisors)==2).lower(),
                        str(math.gcd(n,18)), str(math.lcm(n,18))]
            assert run("math/number-theory.cpp", f"{n} 18") == expected
        for a,b,m in [(2,10,1000), (0,0,1), (9,0,7), (10**18,99,10**9)]:
            assert run("math/modular-power.cpp", f"{a} {b} {m}") == [str(pow(a,b,m))]
        assert run("math/number-theory.cpp", "2 9223372036854775807")[-1] == "overflow"
        print(f"OK: {len(binaries)} executáveis; {checks} execuções verificadas.")


if __name__ == "__main__":
    main()
