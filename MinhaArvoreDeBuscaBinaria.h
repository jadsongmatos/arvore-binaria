#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.h"
#include <cassert>
#include <utility>

/**
 * @brief Representa uma árvore binária de busca.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template<typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
protected:
    void quantidade_andar(int *q,Nodo<T>* tmp)const {
        if(tmp != nullptr){
            q++;
            if(tmp->filhoDireita != nullptr){
                quantidade_andar(q,tmp->filhoDireita);
            }
            if(tmp->filhoEsquerda != nullptr){
                quantidade_andar(q,tmp->filhoEsquerda);
            }
        }
    }
    void altura_andar(T chave,std::optional<int> *q,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            if(tmp->chave != chave){
                q++;
                if(tmp->filhoDireita != nullptr){
                    altura_andar(chave,q,tmp->filhoDireita);
                }
                if(tmp->filhoEsquerda != nullptr){
                    altura_andar(chave,q,tmp->filhoEsquerda);
                }
            }
        }
    }
    void contem_rec(T chave,bool * result,Nodo<T>* tmp){
        if(tmp != nullptr){
            if(tmp->chave != chave){
                if(tmp->filhoDireita != nullptr){
                    contem_rec(chave,tmp->filhoDireita);
                }
                if(tmp->filhoEsquerda != nullptr){
                    contem_rec(chave,tmp->filhoEsquerda);
                }
            } else {
                *result = true;
            }
        }
    }
    void filhoEsquerdaDe_rec(T chave,std::optional<T> *filho,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            if(tmp->chave != chave){
                if(tmp->filhoDireita != nullptr){
                    filhoEsquerdaDe_rec(chave,filho,tmp->filhoDireita);
                }
                if(tmp->filhoEsquerda != nullptr){
                    filhoEsquerdaDe_rec(chave,filho,tmp->filhoEsquerda);
                }
            } else {
                *filho = tmp->filhoEsquerda->chave;
            }
        }
    }
    void filhoDireitaDe_rec(T chave,std::optional<T> *filho,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            if(tmp->chave != chave){
                if(tmp->filhoDireita != nullptr){
                    filhoEsquerdaDe_rec(chave,filho,tmp->filhoDireita);
                }
            } else {
                *filho = tmp->filhoDireita->chave;
            }
        }
    }
    void emOrdem_rec(MinhaListaEncadeada<T>* lista,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            emOrdem_rec(lista,tmp->filhoEsquerda);
            lista->inserirNoFim(tmp->chave);
            emOrdem_rec(lista,tmp->filhoDireita);
        }
    }
    void preOrdem_rec(MinhaListaEncadeada<T>* lista,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            lista->inserirNoFim(tmp->chave);
            preOrdem_rec(lista,tmp->filhoEsquerda);
            preOrdem_rec(lista,tmp->filhoDireita);
        }
    }
    void posOrdem_rec(MinhaListaEncadeada<T>* lista,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            posOrdem_rec(lista,tmp->filhoEsquerda);
            posOrdem_rec(lista,tmp->filhoDireita);
            lista->inserirNoFim(tmp->chave);

        }
    }
    void inserir_rec(T chave,Nodo<T>* tmp){
        if(chave >= tmp->chave){
            if(tmp->filhoDireita == nullptr){
                tmp->filhoDireita = new Nodo<T>;
                tmp->filhoDireita->chave = chave;
            } else {
                inserir_rec(chave,tmp->filhoDireita);
            }
        } else {
            if(tmp->filhoEsquerda == nullptr){
                tmp->filhoEsquerda = new Nodo<T>;
                tmp->filhoEsquerda->chave = chave;
            } else {
                inserir_rec(chave,tmp->filhoEsquerda);
            }
        }
        tmp->altura = tmp->altura / 2;
        tmp->altura++;
    }
    void remover_rec(T chave,Nodo<T>* tmp){
        if(tmp->filhoDireita == chave){
            if(tmp->filhoDireita->filhoDireita != nullptr){

            }
            if(tmp->filhoEsquerda->filhoEsquerda != nullptr){

            }
            delete tmp->filhoDireita;
        }
        if(tmp->filhoEsquerda == chave){
            if(tmp->filhoDireita->filhoDireita != nullptr){

            }
            if(tmp->filhoEsquerda->filhoEsquerda != nullptr){

            }
            tmp->filhoEsquerda;
        }
        tmp->altura = tmp->altura / 2;
        tmp->altura--;
    }
public:
    //MinhaArvoreDeBuscaBinaria();
    ~MinhaArvoreDeBuscaBinaria(){

    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    bool vazia() const {
        return this->_raiz == nullptr ? true : false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidade() const {
        int *q;
        *q = 0;
        quantidade_andar(q,this->_raiz);
        return *q;
    };

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    bool contem(T chave) const{
        bool * result;
        *result = false;
        return *result;
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> altura(T chave) const{
        std::optional<int> *q;
        altura_andar(chave,q,this->_raiz);
        return *q;
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    void inserir(T chave){
        if(this->_raiz != nullptr){
            inserir_rec(chave,this->_raiz);
            this->_raiz->altura = this->_raiz->filhoEsquerda->altura + 1;
        } else {
            this->_raiz = new Nodo<T>;
            this->_raiz->chave = chave;
        }
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */
    void remover(T chave){
        if(this->_raiz != nullptr){
            remover_rec(chave,this->_raiz);
        }
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T> filhoEsquerdaDe(T chave) const{
        std::optional<T> *filho;
        filhoEsquerdaDe_rec(chave,filho,this->_raiz);
        return *filho;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    std::optional<T> filhoDireitaDe(T chave) const{
        std::optional<T> *filho;
        filhoDireitaDe_rec(chave,filho,this->_raiz);
        return *filho;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    ListaEncadeadaAbstrata<T>* emOrdem() const{
        MinhaListaEncadeada<T>* result = new MinhaListaEncadeada<T>();
        if(this->_raiz != nullptr){
            emOrdem_rec(result,this->_raiz);
        }
        return result;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    ListaEncadeadaAbstrata<T>* preOrdem() const{
        MinhaListaEncadeada<T>* result = new MinhaListaEncadeada<T>();
        if(this->_raiz != nullptr){
            preOrdem_rec(result,this->_raiz);
        }
        return result;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    ListaEncadeadaAbstrata<T>* posOrdem() const{
        MinhaListaEncadeada<T>* result = new MinhaListaEncadeada<T>();
        if(this->_raiz != nullptr){
            posOrdem_rec(result,this->_raiz);
        }
        return result;
    };
};

#endif
