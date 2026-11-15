#ifndef NODE_HPP
#define NODE_HPP
#include "condicao.hpp"
#include <fstream>
class Node
{
private:
    int _depth, _max_depth;
    int _classe;
    Node *_v_node;
    Node *_f_node;
    Condicao _condicao;
    //metodo de impressao interno
    void imprimir(int indent,int n_atributos, std::ofstream &arquivo);
public:
    Node(int depth, int max_depth, Condicao condicao, Node *v_node, Node *f_node);
    bool is_folha();
    Node(int depth,int max_depth,int classe);
    void avaliar(float *amostra,int index);
    //teste
    void imprimir(int n_atributos);
    ~Node();
};
#endif