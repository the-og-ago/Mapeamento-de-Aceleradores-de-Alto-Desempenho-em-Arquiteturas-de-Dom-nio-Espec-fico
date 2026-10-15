#ifndef CONDICAO_HPP
#define CONDICAO_HPP
#include <string>
class Condicao
{
private:
    int _index;
    int _limite;
    std::string _operador;
public:
    Condicao(int max_index,int min,int max);
    Condicao();
    int get_limit();
    int get_index();
    std::string get_operador();
    bool is_valid(float *amostra);
    ~Condicao();
};
#endif