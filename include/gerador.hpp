#ifndef GERADOR_HPP
#define GERADOR_HPP
class Gerador{
    private:
    int _linhas;
    int _colunas;
    int **_tabela;
    public:
    Gerador(int linhas,int colunas);
    void randomizar(int sup_limit,int inf_limit);
    int** get_tabela();
    ~Gerador();
};
#endif