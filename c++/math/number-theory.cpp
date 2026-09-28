// DIVISORES, PRIMALIDADE e MDC/MMC: três operações separadas dentro do main.
// Entrada: a b positivos. 12 18 -> 1 2 3 4 6 12 / false / 6 36.
// Divisores e primalidade O(sqrt(a)); memória O(D) para D divisores.
// Use para a moderado. Copie apenas o trecho necessário para sua questão.
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    if (a <= 0 || b <= 0) return 1;

    // 1. DIVISORES: se d divide a, a/d também divide.
    vector<long long> pequenos, grandes;
    for (long long d = 1; d <= a / d; d++) { // evita overflow de d*d
        if (a % d == 0) {
            pequenos.push_back(d);
            if (d != a / d) grandes.push_back(a / d); // raiz aparece só uma vez
        }
    }
    for (long long d : pequenos) cout << d << ' ';
    reverse(grandes.begin(), grandes.end()); // grandes foram encontrados decrescentes
    for (long long d : grandes) cout << d << ' ';
    cout << '\n';

    // 2. PRIMO: não pode ter divisor entre 2 e sqrt(a).
    bool primo = a >= 2;
    for (long long d = 2; d <= a / d; d++) {
        if (a % d == 0) {
            primo = false;
            break;
        }
    }
    cout << boolalpha << primo << '\n';

    // 3. MDC/MMC. gcd é uma função pronta da biblioteca <numeric>.
    long long mdc = gcd(a, b);
    long long parte = a / mdc;
    cout << mdc << ' ';
    if (parte > numeric_limits<long long>::max() / b) cout << "overflow";
    else cout << parte * b; // MMC = (a/MDC)*b
    cout << '\n';
}
