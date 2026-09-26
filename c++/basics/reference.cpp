/*
    REFERÊNCIA RÁPIDA DE C++

    Índice completo: ../README.md.
    Referências detalhadas: ../cheatsheets/cpp.md, collections.md e strings.md.
    Trechos abaixo são consulta; este arquivo não tem main.

    VECTOR
        vector<int> v(n);                 // n zeros
        v.push_back(x);                   // adiciona no final
        v.pop_back();                     // remove o último
        v.erase(v.begin() + i);           // remove pelo índice
        v.insert(v.begin() + i, x);       // insere no índice
        v.clear(); v.size(); v.empty();

        auto it = find(v.begin(), v.end(), x);
        int index = it == v.end() ? -1 : int(it - v.begin());
        v.erase(remove(v.begin(), v.end(), x), v.end()); // remove todos x

    STL MAIS USADA
        sort(v.begin(), v.end());         // O(N log N)
        reverse(v.begin(), v.end());      // O(N)
        find(...) / count(...)            // O(N)
        min(a, b) / max(a, b)             // O(1)
        accumulate(v.begin(), v.end(), 0LL)
        lower_bound(...) / upper_bound(...) // O(log N), exige ordenação
        binary_search(...)                // O(log N), exige ordenação
        swap(a, b) / abs(x)

    STRINGS E CARACTERES
        int pos = c - 'a';                // 'a' -> 0
        int digit = c - '0';              // '7' -> 7
        char upper = char(toupper(static_cast<unsigned char>(c)));
        char lower = char(tolower(static_cast<unsigned char>(c)));
        sort(s.begin(), s.end());
        reverse(s.begin(), s.end());
        bool found = s.find("abc") != string::npos;
        int x = stoi(s); long long y = stoll(s);
        string text = to_string(x);

    COMPLEXIDADE
        O(1): operação fixa.
        O(log N): divide o espaço repetidamente.
        O(N): uma passagem.
        O(N log N): ordenações eficientes.
        O(N²): dois loops dependentes de N.
        O(2^N): força bruta de subconjuntos.

    TIPOS E CUIDADOS
        int costuma ser suficiente para valores até cerca de 2 * 10^9.
        Use long long para somas e produtos potencialmente grandes.
        Um milhão de int ocupa aproximadamente 4 MB.
        Índices de um vetor vão de 0 até size() - 1.
*/
