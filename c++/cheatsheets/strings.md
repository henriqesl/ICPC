# Strings e caracteres C++

```cpp
string s = "banana";
char c = s[0];                  // exige índice válido
string part = s.substr(1, 3);   // "ana": posição + quantidade
auto p = s.find("na");          // 2; string::npos se ausente
s.replace(0, 1, "B");           // "Banana"
reverse(s.begin(), s.end());
sort(s.begin(), s.end());       // altera a string
int digit = '7' - '0';          // 7; apenas dígitos
char d = char('0' + 7);         // '7'; apenas 0..9
int pos = 'd' - 'a';            // 3; letras ASCII minúsculas
char letter = char('a' + 3);    // 'd'
char upper = char(toupper(static_cast<unsigned char>('a')));
int x = stoi("123");
long long y = stoll("123");
string text = to_string(x);
```

Casts para unsigned char evitam comportamento indefinido em cctype para chars
negativos. Essas contas de alfabeto são para ASCII, não texto UTF-8 em geral.
stoi/stoll lançam exceção para inválido/fora do limite; podem aceitar prefixo
numérico: para validar texto inteiro, use o parâmetro pos e confira s.size().
Não converta npos para int: teste antes.

Acesso O(1); substr/cópias O(K); transformações O(N); sort O(N log N).
find não é O(1), depende de texto/padrão. Comparação é lexicográfica, até O(N).
C++17 não tem starts_with/ends_with: compare substrings ou use compare.
Para separar palavras use istringstream de <sstream>; para juntar, acrescente
separador entre partes. getline preserva espaços, >> lê até espaço.
[Conversões executáveis](../strings/conversions.cpp).
