# Debugging — consulta rápida

```bash
g++ -std=c++17 -g -O0 -Wall -Wextra main.cpp -o main.exe
gdb main.exe
```

No GDB: `break main`, `run`, `next`, `step`, `print variavel`, `continue`, `quit`.

No VS Code: breakpoint, `F5` inicia, `F10` avança, `F11` entra na função e `Shift+F5` encerra. `cin` não mostra prompt sozinho; a entrada deve ser digitada no terminal do processo.

