# Debug com VS Code, MSYS2 e GDB

Compile com símbolos e sem otimização:

```bash
g++ -std=c++17 -g -O0 -Wall -Wextra main.cpp -o main.exe
```

No VS Code, use a extensão **C/C++** e uma configuração `cppdbg` com o caminho do `gdb.exe`. Coloque breakpoint ao lado do número da linha, inicie com `F5`, use `F10` para avançar e `F11` para entrar em funções.

Pelo terminal:

```text
gdb main.exe
break main
run
next
step
print nome_da_variavel
continue
quit
```

`cin` não mostra prompt sozinho. Quando chegar à leitura, digite no terminal onde o programa está rodando.

