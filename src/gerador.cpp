#include "gerador.hpp"
#include <ctime>
#include <random>
Gerador::Gerador(int linhas, int colunas):_linhas(linhas), _colunas(colunas)
{
    _tabela = new float[_linhas*_colunas]();
}
Gerador::~Gerador()
{
    delete[] _tabela;
    _tabela=nullptr;
    _linhas=0;
    _colunas=0;
}
void Gerador::randomizar(float sup_limit,float inf_limit)
{
    std::mt19937 generator(std::time(nullptr));
    std::uniform_real_distribution<float> dist(inf_limit, sup_limit);
    for(int i=0;i<_linhas*_colunas;i++)
        _tabela[i]=dist(generator);
}
float* Gerador::get_tabela()
{
    return _tabela;
}