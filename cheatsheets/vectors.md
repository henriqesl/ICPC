# `vector` — consulta rápida

```cpp
vector<int> v(n);
v.push_back(x);
v.pop_back();
v.erase(v.begin() + i);
v.insert(v.begin() + i, x);
v.clear();
v.size();
v.empty();
```

Encontrar índice:

```cpp
auto it = find(v.begin(), v.end(), x);
int index = (it == v.end() ? -1 : int(it - v.begin()));
```

Remover todas as ocorrências:

```cpp
v.erase(remove(v.begin(), v.end(), x), v.end());
```

Índices válidos vão de `0` a `v.size() - 1`. Depois de `erase`, referências e iteradores da região afetada podem ser invalidados.

