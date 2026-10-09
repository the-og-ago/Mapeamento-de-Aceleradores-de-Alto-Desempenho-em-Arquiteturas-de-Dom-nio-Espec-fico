#include "gerador.hpp"
#include <cstdlib>
#include <ctime>
Gerador::Gerador(int linhas, int colunas):_linhas(linhas), _colunas(colunas)
{
    _tabela = new int*[_linhas]();
    for(int i=0;i<_linhas;i++)
    {
        _tabela[i]=new int[_colunas]();
    }
}
Gerador::~Gerador()
{
    for(int i=0;i<_linhas;i++)
    {
        delete[] _tabela[i];
    }
    delete[] _tabela;
    _tabela=nullptr;
    _linhas=NULL;
    _colunas=NULL;
}
void Gerador::randomizar(int sup_limit,int inf_limit)
{
    for(int i=0;i<_linhas;i++)
        for(int j=0;j<_colunas-1;j++)
            _tabela[i][j]=inf_limit+(std::rand() % (sup_limit-inf_limit+1));
}
int** Gerador::get_tabela()
{
    return _tabela;
}