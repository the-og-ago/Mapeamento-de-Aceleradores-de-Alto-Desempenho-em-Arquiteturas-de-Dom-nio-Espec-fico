#ifndef CONDICAO_HPP
#define CONDICAO_HPP
class Condicao
{
private:
    int _index;
    int _limite;
public:
    Condicao(int max_index,int min,int max);
    Condicao();
    int get_limit();
    int get_index();
    bool is_valid(int *amostra);
    ~Condicao();
};
#endif