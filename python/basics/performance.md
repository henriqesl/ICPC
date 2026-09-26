# Performance no contest

Python costuma ter constantes maiores que C++. A mesma complexidade pode passar
em C++ e exceder o tempo em Python: depende do juiz, operações, dados e interpretador.

- Evite percursos repetidos: calcular count para cada elemento pode virar O(N²);
  conte tudo uma vez com Counter.
- Para consultas repetidas, set/dict dão O(1) médio; construir o set custa O(N).
- Para fila use deque.popleft, não list.pop(0).
- sys.stdin.readline ajuda com muitas linhas. buffer.read().split() é prático
  para tokens, mas mantém toda a entrada em memória e não serve para interativos.
- Monte respostas com uma lista e "\n".join(respostas); isso também usa memória.
- Para textos, prefira "".join(partes) à concatenação repetida em loops.
- Prefira funções nativas como sum/sorted quando expressarem o problema.
- Listas armazenam referências e os inteiros são objetos: não use a estimativa
  de 4 bytes por int de C++ para prever memória de Python.
- Inteiros grandes têm custo proporcional ao número de dígitos; não assuma O(1).
- Recursão profunda pode gerar RecursionError; prefira pilha explícita quando possível.
  Aumentar o limite não resolve automaticamente consumo de memória.

Não há um N mágico que assegure aprovação. Meça com dados representativos.
[Erros comuns](../debugging/README.md).
