"""Na raiz icpc/: python -B c++/test_graphs_2.py. Testa os sete programas reais."""
import itertools
import random
import shutil
from pathlib import Path

from test_search import BuildDirectory, compile_source, run


def main():
    root = Path(__file__).resolve().parent / "grafos 2"
    names = ["dijkstra.cpp", "floyd_warshall.cpp", "bellman_ford.cpp",
             "dsu_path_compression.cpp", "kruskal.cpp", "modelagem_estados.cpp",
             "dsu_union_by_size.cpp"]
    sources = [(root / name).read_text(encoding="utf-8") for name in names]
    compiler = shutil.which("g++")
    assert compiler, "g++ precisa estar no PATH"
    rng = random.Random(20261018)
    checks = 0
    def input_graph(n, edges, source=0):
        return f"{n} {len(edges)} {source+1}\n" + "".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
    def floyd(n, edges):
        d = [[None]*n for _ in range(n)]
        for u in range(n): d[u][u]=0
        for u,v,w in edges:
            if d[u][v] is None or w < d[u][v]: d[u][v]=w
        for k in range(n):
            for u in range(n):
                for v in range(n):
                    if d[u][k] is None or d[k][v] is None: continue
                    nd = d[u][k]+d[k][v]
                    if d[u][v] is None or nd < d[u][v]: d[u][v]=nd
        return d
    def output(ds): return [str(x) if x is not None else "INF" for x in ds]
    def mst(n, edges):
        best=None
        for subset in itertools.combinations(edges, n-1):
            reached={0}
            for _ in range(n):
                for u,v,w in subset:
                    if u in reached: reached.add(v)
                    if v in reached: reached.add(u)
            if len(reached) == n:
                cost=sum(w for u,v,w in subset)
                best=cost if best is None else min(best,cost)
        return ["IMPOSSIVEL"] if best is None else [str(best)]
    with BuildDirectory(prefix="icpc-grafos2-") as tmp:
        bins=[]
        for i,src in enumerate(sources):
            bins.append(compile_source(compiler,Path(tmp),f"template-{i}",src))
            print(f"Compilou: {i+1}/{len(sources)}",flush=True)
        def expect(i, data, expected):
            nonlocal checks
            actual=" ".join(run(bins[i],data)).split()
            assert actual==expected,(i,data,actual,expected)
            checks+=1
        expect(3,"4 5\n2 1 2\n1 1 2\n2 1 2\n1 2 3\n2 1 3\n",["NAO","SIM","SIM"])
        expect(6,"4 5\n2 1 2\n1 1 2\n2 1 2\n1 2 3\n2 1 3\n",["NAO","SIM","SIM"])
        cases=[(1,[],0),(3,[],0),(3,[(0,1,4000000000),(1,2,5000000000)],0),
               (4,[(0,1,9),(0,1,2),(1,2,0),(0,2,7)],0)]
        for _ in range(35):
            n=rng.randint(1,7)
            edges=[(rng.randrange(n),rng.randrange(n),rng.randrange(12)) for _ in range(rng.randrange(16))]
            cases.append((n,edges,rng.randrange(n)))
        for n,edges,s in cases:
            d=floyd(n,edges)
            expect(0,input_graph(n,edges,s),output(d[s]))
            expect(2,input_graph(n,edges,s),output(d[s]))
        weighted=[(1,[],0),(3,[(0,1,-4),(1,2,1),(0,2,9)],0),
                  (4,[(2,3,-4),(3,2,1)],0),
                  (3,[(0,1,3000000000000),(1,2,-1000000000000)],0)]
        for _ in range(45):
            n=rng.randint(1,7)
            potential=[rng.randint(-20,20) for _ in range(n)]
            edges=[(u,v,rng.randrange(10)+potential[v]-potential[u])
                   for u,v in [(rng.randrange(n),rng.randrange(n)) for _ in range(rng.randrange(18))]]
            weighted.append((n,edges,rng.randrange(n)))
        for n,edges,s in weighted:
            d=floyd(n,edges)
            expect(2,input_graph(n,edges,s),output(d[s]))
            data=f"{n} {len(edges)} {n*n}\n"+"".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
            data+="".join(f"{u+1} {v+1}\n" for u in range(n) for v in range(n))
            expect(1,data,output([x for row in d for x in row]))
        negative=[(1,[(0,0,-1)],0),(2,[(0,1,-1),(1,0,0)],0),
                  (4,[(0,1,1),(2,3,-4),(3,2,1)],0)]
        for _ in range(40):
            n=rng.randint(1,6)
            negative.append((n,[(rng.randrange(n),rng.randrange(n),rng.randint(-8,8))
                               for _ in range(rng.randrange(14))],rng.randrange(n)))
        for n,edges,s in negative:
            d=floyd(n,edges)
            cycle=any(d[s][v] is not None and d[v][v]<0 for v in range(n))
            expect(2,input_graph(n,edges,s),["CICLO","NEGATIVO"] if cycle else output(d[s]))
        trees=[(1,[]),(3,[]),(3,[(0,1,4000000000),(1,2,5000000000)]),
               (3,[(0,1,-8),(0,1,-4),(1,2,3),(0,2,9),(2,2,-99)])]
        for _ in range(40):
            n=rng.randint(1,6)
            trees.append((n,[(rng.randrange(n),rng.randrange(n),rng.randint(-10,15))
                            for _ in range(rng.randrange(10))]))
        for n,edges in trees:
            data=f"{n} {len(edges)}\n"+"".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
            expect(4,data,mst(n,edges))

        for _ in range(35):
            n=rng.randint(1,12)
            groups=list(range(n))
            commands=[]
            expected=[]
            for _ in range(40):
                u,v=rng.randrange(n),rng.randrange(n)
                typ=rng.choice([1,2])
                commands.append((typ,u,v))
                if typ==1:
                    oldgroup=groups[v]
                    groups=[groups[u] if g==oldgroup else g for g in groups]
                else:
                    expected.append("SIM" if groups[u]==groups[v] else "NAO")
            data=f"{n} {len(commands)}\n"+"".join(f"{t} {u+1} {v+1}\n" for t,u,v in commands)
            expect(3,data,expected)
            expect(6,data,expected)
        coupon_cases=[(1,[],0,0),(2,[],0,1),(2,[(0,1,7)],0,1),
                      (3,[(0,1,8),(1,2,2),(0,2,20)],0,2)]
        for _ in range(45):
            n=rng.randint(1,6)
            edges=[(rng.randrange(n),rng.randrange(n),rng.randrange(30)) for _ in range(rng.randrange(16))]
            coupon_cases.append((n,edges,rng.randrange(n),rng.randrange(n)))
        for n,edges,s,t in coupon_cases:
            expanded=[]
            for u,v,w in edges:
                expanded.extend([(2*u,2*v,w),(2*u+1,2*v+1,w),(2*u,2*v+1,w//2)])
            ds=floyd(2*n,expanded)[2*s]
            reachable=[ds[2*t+c] for c in (0,1) if ds[2*t+c] is not None]
            expected=[str(min(reachable))] if reachable else ["INF"]
            data=f"{n} {len(edges)} {s+1} {t+1}\n"+"".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
            expect(5,data,expected)

        probes = {
            3: """
    DSU d(20000);
    assert(d.pai.size() == 20001);
    for (int i = 1; i < 20000; i++) assert(d.join(i + 1, i));
    assert(d.pai[1] == 2);
    assert(d.find(1) == 20000);
    for (int i = 1; i <= 20000; i++) assert(d.pai[i] == 20000);
    assert(!d.join(1, 20000));
    """,
            6: """
    DSU d(8);
    d.join(1, 2); d.join(3, 4); d.join(1, 3);
    assert(d.pai[4] == 3);
    auto before = d.pai;
    assert(d.find(4) == 1);
    assert(d.pai == before); // sem compressao
    assert(d.sz[d.find(4)] == 4);
    DSU large(20000);
    for (int i = 1; i < 20000; i++) assert(large.join(i + 1, i));
    assert(large.same(1, 20000));
    assert(large.sz[large.find(20000)] == 20000);
    """,
            4: """
    DSU d(8);
    d.join(1, 2); d.join(3, 4); d.join(1, 3);
    assert(d.pai[4] == 3);
    assert(d.find(4) == 1);
    assert(d.pai[4] == 1); // comprime
    assert(d.sz[d.find(4)] == 4);
    assert(!d.join(4, 2));
    """
        }
        for index, probe in probes.items():
            definition = sources[index].split("int main()", 1)[0]
            harness = definition + "\n#include <cassert>\nint main() {\n" + probe + "\n}\n"
            executable = compile_source(compiler, Path(tmp), f"dsu-invariants-{index}", harness)
            assert run(executable) == []
            checks += 1

        n = 20000
        edges = [(u, u+1, 1) for u in range(n-1)]
        expect(0, input_graph(n, edges), list(map(str, range(n))))
        data = f"{n} {len(edges)} 1 {n}\n" + "".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
        expect(5, data, [str(n-2)])
        data = f"{n} {len(edges)}\n" + "".join(f"{u+1} {v+1} {w}\n" for u,v,w in edges)
        expect(4, data, [str(n-1)])

    print(f"OK: 7 programas, {checks} execucoes; DSU separado, caminhos, MST e estados.", flush=True)


if __name__ == "__main__":
    main()
