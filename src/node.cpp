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
void Node::imprimir(int n_atributos)
{   std::ofstream arquivo;
    arquivo.open("arvore_gerada.cu");

    //cabecalho
    arquivo << "__global__ void avaliar(float *A, int linhas, int n_atributos) {\n";
    arquivo << "    int i = blockIdx.x * blockDim.x + threadIdx.x;\n";
    arquivo << "    if(i < linhas) {\n";

    this->imprimir(8,n_atributos,arquivo);

    arquivo << "    }\n";
    arquivo << "}\n";

    arquivo.close();
}
void Node::imprimir(int indent,int n_atributos,std::ofstream &arquivo)
{
    
    std::string indentacao(indent, ' ');
    if (is_folha())
    {
        arquivo << indentacao << "A[i*n_atributos+" << (n_atributos - 1) << "]=" << _classe << ";\n";
        return;
    }
    arquivo<<indentacao;
    arquivo <<"if(A[i*n_atributos+"<<_condicao.get_index()<<"]"\
    <<_condicao.get_operador()<<_condicao.get_limit()<<".0f){\n";
    _v_node->imprimir(indent+4,n_atributos,arquivo);
    arquivo<<indentacao;
    arquivo <<"} else {\n";
    _f_node->imprimir(indent+4,n_atributos,arquivo);
    arquivo<<indentacao;
    arquivo <<"}\n";
}