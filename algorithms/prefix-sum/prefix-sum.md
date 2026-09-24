# Prefix sum

Pré-processa somas acumuladas para responder intervalos em `O(1)`. Construção: `O(N)` tempo e `O(N)` espaço.

```cpp
vector<long long> pref(n + 1);
for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
long long sum = pref[r + 1] - pref[l]; // intervalo [l, r]
```

