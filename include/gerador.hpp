#ifndef GERADOR_HPP
#define GERADOR_HPP
class Gerador{
    private:
    int _linhas;
    int _colunas;
    float*_tabela;
    public:
    Gerador(int linhas,int colunas);
    void randomizar(float sup_limit,float inf_limit);
    float* get_tabela();
    ~Gerador();
};
#endif