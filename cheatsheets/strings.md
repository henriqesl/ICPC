# Strings e caracteres

```cpp
char c = s[i];
int pos = c - 'a';       // 'a' -> 0
int digit = c - '0';     // '7' -> 7
char upper = toupper(c);
char lower = tolower(c);
sort(s.begin(), s.end());
reverse(s.begin(), s.end());
bool found = s.find("abc") != string::npos;
int x = stoi(s);
long long y = stoll(s);
string text = to_string(x);
```

`char` armazena um caractere; `string`, uma sequência. Confirme os limites antes de converter caracteres por aritmética.

