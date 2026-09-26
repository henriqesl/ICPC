# C++17: consulta rápida

## Entrada, saída e funções

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr); // não misture cin/cout com scanf/printf após isso
int n; cin >> n;
vector<int> v(n);
for (int& x : v) cin >> x; // & altera o elemento
int t; cin >> t;
while (t--) { /* apenas quando houver T no enunciado */ }
cout << fixed << setprecision(2) << 1.0 / 3 << '\n';
```

[Exemplo de I/O](../basics/io.cpp). Para interativo, faça flush quando necessário.
`getline(cin, s)` lê espaços. Após >>, descarte a quebra com
`cin.ignore(numeric_limits<streamsize>::max(), '\n')`.
`getline(cin >> ws, s)` é alternativa somente se espaços iniciais/linhas vazias não importarem.

```cpp
long long sum(const vector<int>& v) { // referência sem cópia; não altera v
    return accumulate(v.begin(), v.end(), 0LL);
}
void add_one(int& x) { ++x; } // altera argumento
int doubled(int x) { return 2*x; } // cópia; resultado deve caber em int
```

## Tipos, overflow e divisão

int normalmente 32 bits; long long pelo menos 64. Use numeric_limits<T> para limites.
float tem tipicamente ~6 dígitos significativos; double ~15; long double varia.
bool representa verdadeiro/falso; char é uma unidade de caractere; string é sequência.
`long long product = 1LL * a * b;` promove ANTES da multiplicação.
`long long product = a * b;` não evita overflow de int.
Mesmo long long pode estourar; signed overflow é comportamento indefinido.
`7/2 == 3`; `7.0/2 == 3.5`; `-7/2 == -3`; `-7%2 == -1`.
Precisão na saída não corrige erros de cálculo. abs do menor inteiro do tipo não cabe.

## STL (vetores, intervalos [begin,end))

| Operação | Retorno | Tempo |
|---|---|---|
| sort(v.begin(),v.end()) | void; altera | O(N log N) |
| reverse(v.begin(),v.end()) | void; altera | O(N) |
| find(v.begin(),v.end(),x) | iterador, end se ausente | O(N) |
| count(v.begin(),v.end(),x) | quantidade | O(N) |
| min(a,b), max(a,b) | valor/referência ao extremo | O(1) para números |
| min_element / max_element | iterador; end se vazio | O(N) |
| accumulate(v.begin(),v.end(),0LL) | soma long long | O(N) |
| lower_bound / upper_bound | primeiro >=x / >x | O(log N) comparações |
| binary_search(v.begin(),v.end(),x) | bool | O(log N) |
| swap(a,b) | void; troca | O(1) para números e vectors usuais |
| abs(x) | magnitude | O(1) para tipos numéricos nativos |

Buscas binárias exigem ordenação; em iteradores não aleatórios pode haver O(N)
avanços. Em set, prefira s.lower_bound(x).
`auto it = min_element(v.begin(),v.end()); if(it != v.end()) cout << *it;`

Headers: algorithm (sort/buscas), numeric (accumulate/gcd/lcm), iomanip
(setprecision), limits, vector, iostream, string. Os exemplos antigos usam
bits/stdc++.h, extensão do GCC, não header padrão do C++17.
