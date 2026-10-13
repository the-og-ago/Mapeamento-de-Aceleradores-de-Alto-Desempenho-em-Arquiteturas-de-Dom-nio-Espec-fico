#include "condicao.hpp"
#include <cstdlib>
#include <string>
Condicao::Condicao(int max_index,int min,int max)
{
    _index=std::rand() % (max_index+1);
    _limite=min+(std::rand() % (max-min+1));
    _operador=">";
}
Condicao::Condicao() : _index(-1), _limite(0) {}
Condicao::~Condicao(){}
int Condicao::get_index()
{
    return _index;
}
int Condicao::get_limit()
{
    return _limite;
}
std::string Condicao::get_operador()
{
    return _operador;
} 
bool Condicao::is_valid(int *amostra)
{
    return amostra[_index]>_limite;
}
