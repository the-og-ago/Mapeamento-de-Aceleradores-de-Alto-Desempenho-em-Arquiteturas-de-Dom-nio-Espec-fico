#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "gerador.hpp"
#include "treegen.hpp"

int main()
{
    std::srand(std::time(nullptr));

    int linhas = 1000000;
    int colunas = 10;
    int max_depth = 2;
    int num_classes = 3;
    int min_val = 0;
    int max_val = 100;
    int index_classe = colunas - 1;
    int max_attr_index = colunas - 2;

    Gerador gerador(linhas, colunas);
    gerador.randomizar(max_val, min_val);

    auto t_start_gen = std::chrono::high_resolution_clock::now();
    Arvore arvore(max_depth, max_attr_index, min_val, max_val, num_classes);
    auto t_end_gen = std::chrono::high_resolution_clock::now();

    int **tabela = gerador.get_tabela();

    auto t_start_eval = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < linhas; ++i)
    {
        arvore.avaliar(tabela[i], index_classe);
    }
    auto t_end_eval = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms_gen = t_end_gen - t_start_gen;
    std::chrono::duration<double, std::milli> ms_eval = t_end_eval - t_start_eval;

    std::cout << "Geracao: " << ms_gen.count() << " ms" << std::endl;
    std::cout << "Avaliacao: " << ms_eval.count() << " ms" << std::endl;

    //teste
    arvore.imprimir();
    /*for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            std::cout << tabela[i][j] << " ";
        }
        std::cout << "\n";
    }*/
    return 0;
}