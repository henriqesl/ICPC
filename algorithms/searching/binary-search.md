# Busca binária

## Consulta rápida

Use em vetor ordenado ou em uma propriedade monotônica. Tempo `O(log N)`, espaço `O(1)`.

```cpp
int first_at_least(const vector<int>& v, int x) {
    int lo = 0, hi = int(v.size());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo; // pode ser v.size()
}
```

Confirme se o índice retornado está dentro do vetor antes de acessá-lo.

