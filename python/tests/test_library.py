"""Execute na raiz icpc: python -B python/tests/test_library.py."""
import importlib.util
import itertools
from pathlib import Path
import random
import re
import subprocess
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
PYTHON = ROOT / "python"
sys.dont_write_bytecode = True


def load(relative):
    path = PYTHON / relative
    spec = importlib.util.spec_from_file_location(path.stem, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class LibraryTests(unittest.TestCase):
    def test_search(self):
        mod = load("algorithms/searching.py")
        for values in ([], [3], [1, 3, 3, 8], [-5, -1, 0]):
            for target in range(-6, 11):
                expected = next((i for i, x in enumerate(values) if x >= target), len(values))
                self.assertEqual(mod.first_at_least(values, target), expected)
                exact = next((i for i, x in enumerate(values) if x == target), -1)
                self.assertEqual(mod.linear_search(values, target), exact)

    def test_prefix(self):
        mod = load("algorithms/prefix_sum.py")
        self.assertEqual(mod.build_prefix([]), [0])
        values = [2, -3, 0, 10**30, -10**30]
        prefix = mod.build_prefix(values)
        for left in range(len(values)):
            for right in range(left, len(values)):
                self.assertEqual(mod.range_sum(prefix, left, right), sum(values[left:right + 1]))
        with self.assertRaises(ValueError):
            mod.range_sum(prefix, -1, 0)

    def test_pairs_against_brute_force(self):
        mod = load("algorithms/two_pointers.py")
        rng = random.Random(42)
        for _ in range(200):
            values = sorted(rng.randrange(-8, 9) for _ in range(rng.randrange(12)))
            target = rng.randrange(-16, 17)
            exists = any(a + b == target for a, b in itertools.combinations(values, 2))
            answer = mod.pair_sum(values, target)
            self.assertEqual(answer is not None, exists)
            if answer is not None:
                i, j = answer
                self.assertLess(i, j)
                self.assertEqual(values[i] + values[j], target)

    def test_greedy_against_subsets(self):
        mod = load("algorithms/greedy.py")
        rng = random.Random(9)
        for _ in range(80):
            intervals = []
            for _ in range(rng.randrange(8)):
                start = rng.randrange(-5, 6)
                intervals.append((start, start + rng.randrange(1, 6)))
            best = 0
            for mask in range(1 << len(intervals)):
                subset = sorted(x for i, x in enumerate(intervals) if mask & (1 << i))
                if all(a[1] <= b[0] for a, b in zip(subset, subset[1:])):
                    best = max(best, len(subset))
            chosen = mod.select_intervals(intervals)
            self.assertEqual(len(chosen), best)
            self.assertTrue(all(a[1] <= b[0] for a, b in zip(chosen, chosen[1:])))

    def test_number_theory(self):
        import math
        mod = load("math/number_theory.py")
        for n in range(1, 250):
            divs = [d for d in range(1, n + 1) if n % d == 0]
            self.assertEqual(mod.divisors(n), divs)
            self.assertEqual(mod.is_prime(n), len(divs) == 2)
        for n in [-3, 0, 1]:
            self.assertFalse(mod.is_prime(n))
        for a in range(-10, 11):
            for b in range(-10, 11):
                self.assertEqual(mod.lcm(a, b), math.lcm(a, b))
        with self.assertRaises(ValueError):
            mod.divisors(0)

    def test_collections_and_strings(self):
        from bisect import bisect_left, bisect_right, insort
        from collections import deque
        import heapq
        lists = load("collections/lists.py")
        self.assertEqual(lists.first_index([], 1), -1)
        self.assertEqual(lists.first_index([4, 1, 4], 4), 0)
        values = [3, 1, 3]
        values.remove(3)
        self.assertEqual(values, [1, 3])
        self.assertEqual({1, 2} & {2, 3}, {2})
        self.assertEqual({1, 2} | {2, 3}, {1, 2, 3})
        self.assertEqual({1, 2} - {2, 3}, {1})
        self.assertEqual(load("collections/frequency.py").frequencies([2, 2, -1]), {2: 2, -1: 1})
        q = deque([2]); q.appendleft(1); q.append(3)
        self.assertEqual((q.popleft(), q.pop()), (1, 3))
        for values in ([], [3], [-4, 2, 2, 9]):
            self.assertEqual(list(load("collections/heap.py").descending(values)), sorted(values, reverse=True))
        h = [4, 2]; heapq.heapify(h); heapq.heappush(h, 1)
        self.assertEqual(heapq.heappop(h), 1)
        v = [1, 3, 3, 8]
        self.assertEqual((bisect_left(v, 3), bisect_right(v, 3)), (1, 3))
        insort(v, 4)
        self.assertEqual(v, [1, 3, 3, 4, 8])
        strings = load("strings/conversions.py")
        for i in range(26):
            self.assertEqual(strings.letter_position(chr(97 + i)), i)
        with self.assertRaises(ValueError):
            strings.letter_position("AA")
        self.assertEqual("banana".find("na"), 2)
        self.assertEqual("aaaa".count("aa"), 2)
        self.assertEqual("-".join("a  b".split()), "a-b")
        self.assertEqual(str(int("00123")), "123")
        self.assertEqual(load("algorithms/sorting.py").by_second([(1, 2), (0, 2), (4, 1)]),
                         [(4, 1), (1, 2), (0, 2)])

    def test_balanced(self):
        balanced = load("collections/balanced.py").balanced
        for text in ["", "abc", "([{}])", "()[]{}"]:
            self.assertTrue(balanced(text))
        for text in ["(", ")", "([)]", "(()"]:
            self.assertFalse(balanced(text))

    def test_cli_examples(self):
        cases = [
            ("basics/io.py", "4\n1 2\n3 4\n", "10\n"),
            ("basics/io.py", "", ""),
            ("templates/template.py", "", ""),
            ("collections/lists.py", "", "0\n[1, 3]\n[1, 3, 8]\n"),
            ("collections/sets.py", "", "[2]\n[1, 2, 3]\n[1]\n"),
            ("strings/conversions.py", "", "3 4 7 d\nabc\n123\n"),
            ("collections/frequency.py", "4 3 3 8 3", "3: 3\n8: 1\n"),
            ("collections/queue.py", "2 Ana Bia", "Ana\nBia\n"),
            ("collections/heap.py", "3 2 9 4", "9 4 2\n"),
            ("collections/balanced.py", "([{}])\n", "balanceado\n"),
            ("collections/balanced.py", "([)]\n", "desbalanceado\n"),
            ("algorithms/searching.py", "4 1 3 3 8 3", "1\n"),
            ("algorithms/searching.py", "0 7", "-1\n"),
            ("algorithms/prefix_sum.py", "3 2 -1 4 2 0 2 1 1", "5\n-1\n"),
            ("algorithms/sorting.py", "3 2 1 3", "1 2 3\n3 2 1\n"),
            ("algorithms/two_pointers.py", "4 1 3 5 8 9", "0 3\n"),
            ("algorithms/two_pointers.py", "1 4 8", "-1\n"),
            ("algorithms/greedy.py", "3 0 2 1 4 2 3", "2\n"),
            ("math/number_theory.py", "12 18", "1 2 3 4 6 12\nFalse\n6 36\n"),
        ]
        for relative, data, expected in cases:
            with self.subTest(file=relative, data=data):
                proc = subprocess.run([sys.executable, "-B", str(PYTHON / relative)],
                                      input=data, text=True, capture_output=True, timeout=5)
                self.assertEqual(proc.returncode, 0, proc.stderr)
                self.assertEqual(proc.stdout, expected)

    def test_local_links(self):
        # Verifica destinos de links; as âncoras são conferidas na revisão.
        docs = [ROOT / "README.md", *PYTHON.rglob("*.md"), *(ROOT / "c++").rglob("*.md")]
        for path in docs:
            for target in re.findall(r"\]\(([^)]+)\)", path.read_text(encoding="utf-8")):
                if "://" not in target:
                    self.assertTrue((path.parent / target.split("#")[0]).exists(), f"{path}: {target}")


if __name__ == "__main__":
    unittest.main(verbosity=2)
