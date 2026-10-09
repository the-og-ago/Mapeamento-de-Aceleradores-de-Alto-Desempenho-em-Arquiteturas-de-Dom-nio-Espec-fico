#ifndef NODE_HPP
#define NODE_HPP
#include "condicao.hpp"
class Node
{
private:
    int _depth, _max_depth;
    int _classe;
    Node *_v_node;
    Node *_f_node;
    Condicao _condicao;
public:
    Node(int depth, int max_depth, Condicao condicao, Node *v_node, Node *f_node);
    bool is_folha();
    Node(int depth,int max_depth,int classe);
    void avaliar(int *amostra,int index);
    //teste
    void imprimir(int indent = 0);
    ~Node();
};
#endif