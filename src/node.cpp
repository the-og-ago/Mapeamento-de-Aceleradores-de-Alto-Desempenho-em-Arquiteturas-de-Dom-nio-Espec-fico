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
void Node::avaliar(float *amostra, int index)
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
//impressao do codigo da arvore
void Node::imprimir(int indent)
{
    std::string indentacao(indent, ' ');
    if (is_folha())
    {
        std::cout <<indentacao<<"Classe[i]="<< _classe << ";\n";
        return;
    }
    std::cout<<indentacao;
    std::cout <<"if(A[i*n_atributos+"<<_condicao.get_index()<<"]"<<_condicao.get_operador()<<_condicao.get_limit()<<"){\n";
    _v_node->imprimir(indent+4);
    std::cout<<indentacao;
    std::cout <<"} else {\n";
    _f_node->imprimir(indent+4);
    std::cout<<indentacao;
    std::cout <<"}\n";
}