#include "condicao.hpp"
#include <cstdlib>
#include <ctime>
Condicao::Condicao(int max_index,int min,int max)
{
    _index=std::rand() % (max_index+1);
    _limite=min+(std::rand() % (max-min+1));
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
bool Condicao::is_valid(int *amostra)
{
    return amostra[_index]>_limite;
}