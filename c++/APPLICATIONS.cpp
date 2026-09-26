/*
    GUIA DE APLICAÇÃO DOS EXEMPLOS

    Índice completo: README.md
    Sintaxe e STL: cheatsheets/cpp.md
    Operações em estruturas: cheatsheets/collections.md
    Strings e conversões: cheatsheets/strings.md

    Somar durante a leitura sem guardar os dados:
        basics/io.cpp
    Converter letras/dígitos e ordenar texto:
        strings/conversions.cpp
    Inserir/remover nas duas pontas:
        data-structures/deque/deque-example.cpp
    Ordenar preservando índices originais:
        data-structures/pair/pair-example.cpp
    Buscar posição exata sem ordenação:
        algorithms/searching/linear-search.cpp
    Encontrar dois índices com soma alvo, em vetor ordenado:
        algorithms/two-pointers/two-pointers.cpp
    Maximizar quantidade de intervalos sem sobreposição e sem pesos:
        algorithms/greedy/intervals.cpp
    Enumerar divisores, testar primo e calcular MDC/MMC:
        math/number-theory.cpp
    Exponenciação modular (módulo até 10^9):
        math/modular-power.cpp

    PYTHON COMPLEMENTAR
        Índice completo: ../python/README.md
        Referência rápida: ../python/cheatsheets/python.md
        Algoritmos e equivalências C++: ../python/algorithms/README.md
        Template: ../python/templates/template.py

    Encontrar posição, contar ocorrências ou ordenar um vetor:
        basics/useful-operations/vector-operations.cpp
        Use find, count, índice pelo iterador e sort.

    Ordenar dados crescente e decrescente:
        algorithms/sorting/sorting-example.cpp
        Útil antes de buscas, agrupamentos, pareamentos e comparações.

    Procurar em vetor ordenado ou achar o primeiro valor >= x:
        algorithms/searching/binary-search-main.cpp
        Use busca binária em O(log N). O vetor precisa estar ordenado.

    Responder várias somas de intervalos [l, r]:
        algorithms/prefix-sum/prefix-sum-main.cpp
        Use prefix sum quando o vetor não muda após a leitura.

    Verificar parênteses, colchetes ou chaves:
        data-structures/stack/balanced-parentheses-main.cpp
        Use stack porque o último símbolo aberto deve fechar primeiro.

    Processar elementos na ordem de chegada:
        data-structures/queue/queue-example.cpp
        Queue segue FIFO: primeiro que entra, primeiro que sai.

    Remover duplicatas e manter valores ordenados:
        data-structures/set/set-example.cpp
        Set guarda cada valor uma única vez.

    Contar frequência de números ou categorias:
        data-structures/map/frequency-map.cpp
        Use map[chave]++ para contar ocorrências.

    Sempre escolher o maior elemento disponível:
        data-structures/priority-queue/priority-queue-example.cpp
        Priority queue mantém o maior valor no topo.

    COMO ADAPTAR NO CONTEST
    1. Copie a estrutura necessária para o template.cpp.
    2. Troque entrada e saída conforme o enunciado.
    3. Remova o que não for necessário.
    4. Confira as pré-condições e os limites dos índices.
*/
