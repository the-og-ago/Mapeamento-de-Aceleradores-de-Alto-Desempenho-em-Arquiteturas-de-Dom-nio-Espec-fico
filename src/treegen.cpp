#include "treegen.hpp"
#include <cstdlib>

Node* Arvore::construir_subarvore(int current_depth, int max_index, int min_val, int max_val, int num_classes)
{
    if (current_depth >= _max_depth)
    {
        int classe_sorteada = std::rand() % num_classes;
        return new Node(current_depth, _max_depth, classe_sorteada);
    }

    Node *v_node = construir_subarvore(current_depth + 1, max_index, min_val, max_val, num_classes);
    Node *f_node = construir_subarvore(current_depth + 1, max_index, min_val, max_val, num_classes);

    Condicao condicao(max_index, min_val, max_val);

    return new Node(current_depth, _max_depth, condicao, v_node, f_node);
}

Arvore::Arvore(int max_depth, int max_index, int min_val, int max_val, int num_classes)
    : _max_depth(max_depth)
{
    _raiz = construir_subarvore(0, max_index, min_val, max_val, num_classes);
}

Arvore::~Arvore()
{
    delete _raiz;
}

void Arvore::avaliar(int *amostra, int index_classe)
{
    if (_raiz != nullptr)
    {
        _raiz->avaliar(amostra, index_classe);
    }
}

Node* Arvore::get_raiz()
{
    return _raiz;
}
//teste
void Arvore::imprimir()
{
    if (_raiz != nullptr)
    {
        _raiz->imprimir();
    }
}
