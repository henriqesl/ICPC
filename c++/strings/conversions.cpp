// Aplicação: mapear letras/dígitos para índices de frequência.
// Sem entrada; saída: 3 4 7 d / abc / 123.
// Conversões de char O(1); ordenar string O(N log N).
// Aritmética das letras pressupõe ASCII; stoi exige número no limite de int.
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
int main() {
    char c = 'd';
    std::cout << c-'a' << ' ' << c-'a'+1 << ' ' << '7'-'0' << ' '
              << char('a'+3) << '\n';
    std::string s = "Cab";
    for (char& ch : s) ch = char(std::tolower(static_cast<unsigned char>(ch)));
    std::sort(s.begin(), s.end());
    std::cout << s << '\n' << std::to_string(std::stoi("00123")) << '\n';
}
