#include "node.hpp"
#include <cstddef>
#include <iostream>
Node::Node(int depth, int max_depth, Condicao condicao, Node *v_node, Node *f_node):_depth(depth),_max_depth(max_depth),
_classe(-1),_v_node(v_node),_f_node(f_node),_condicao(condicao){}

Node::Node(int depth,int max_depth,int classe):_depth(depth),_max_depth(max_depth),_classe(classe),_v_node(nullptr),_f_node(nullptr){}

bool Node::is_folha()
{
    return _v_node==nullptr&&_f_node==nullptr;
}
void Node::avaliar(int *amostra, int index)
{
    if(is_folha())
    {
        amostra[index]=_classe;
    }
    else if(_condicao.is_valid(amostra))
    {
        _v_node->avaliar(amostra,index);
    }
    else
    {
        _f_node->avaliar(amostra,index);
    }
}
Node::~Node()
{
    delete _v_node;
    delete _f_node;
}
//teste
void Node::imprimir(int indent)
{
    for (int i = 0; i < indent; ++i) std::cout << "  ";

    if (is_folha())
    {
        std::cout << "[Folha] -> Classe: " << _classe << "\n";
        return;
    }

    std::cout << "[Nó Prof " << _depth << "] Atributo["
              << _condicao.get_index() << "] > " << _condicao.get_limit() << "\n";

    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "├── (V):\n";
    _v_node->imprimir(indent + 2);

    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "└── (F):\n";
    _f_node->imprimir(indent + 2);
}