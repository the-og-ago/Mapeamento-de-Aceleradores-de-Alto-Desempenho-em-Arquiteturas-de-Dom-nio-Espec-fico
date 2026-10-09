#ifndef TREEGEN_HPP
#define TREEGEN_HPP
#include "node.hpp"

class Arvore
{
private:
    Node *_raiz;
    int _max_depth;

    Node* construir_subarvore(int current_depth, int max_index, int min_val, int max_val, int num_classes);

public:
    Arvore(int max_depth, int max_index, int min_val, int max_val, int num_classes);
    ~Arvore();

    void avaliar(int *amostra, int index_classe);
    Node* get_raiz();
    //teste
    void imprimir();
};

#endif