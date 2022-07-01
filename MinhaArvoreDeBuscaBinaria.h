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
            (*q)++;
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
            if(tmp != nullptr){
                if(chave == tmp->chave) {
                    *q = tmp->altura;
                    return;
                } else if (chave > tmp->chave) {
                    tmp = tmp->filhoDireita;
                } else if(chave < tmp->chave) {
                    tmp = tmp->filhoEsquerda;
                }
                altura_andar(chave,q,tmp);
            }
        }
    }
    bool contem_rec(T chave,Nodo<T>* tmp)const{
        if(tmp != nullptr){
            if(tmp != nullptr){
                if(chave == tmp->chave) {
                    return true;
                } else if (chave > tmp->chave) {
                    tmp = tmp->filhoDireita;
                } else if(chave < tmp->chave) {
                    tmp = tmp->filhoEsquerda;
                }
                return contem_rec(chave,tmp);
            }
        }
    }
    std::optional<T> filhoEsquerdaDe_rec(T chave,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            if(tmp->filhoEsquerda != nullptr && chave == tmp->chave) {
                return tmp->filhoEsquerda->chave;
            } else if (chave > tmp->chave) {
                tmp = tmp->filhoDireita;
            } else if(chave < tmp->chave) {
                tmp = tmp->filhoEsquerda;
            }
            return filhoEsquerdaDe_rec(chave,tmp);
        }
    }
    std::optional<T> filhoDireitaDe_rec(T chave,Nodo<T>* tmp) const{
        if(tmp != nullptr){
            if(tmp->filhoDireita != nullptr && chave == tmp->chave) {
                return tmp->filhoDireita->chave;
            } else if (chave > tmp->chave) {
                tmp = tmp->filhoDireita;
            } else if(chave < tmp->chave) {
                tmp = tmp->filhoEsquerda;
            }
            return filhoDireitaDe_rec(chave,tmp);
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
    void remover_rec(Nodo<T> * root,T chave){
        if (root != nullptr) {
            if (chave > root->chave) {
                remover_rec(root->filhoDireita, chave);
                if (root->filhoDireita != nullptr){
                    if (root->filhoDireita->altura == -1){
                        Nodo<T> * tmp = root->filhoDireita;
                        root->filhoDireita = nullptr;
                        delete tmp;
                    }
                }
                if (root->filhoEsquerda != nullptr){
                    if (root->filhoEsquerda->altura == -1){
                        Nodo<T> * tmp = root->filhoEsquerda;
                        root->filhoEsquerda = nullptr;
                        delete tmp;
                    }
                }
                root->altura--;
            } else if (chave < root->chave) {
                remover_rec(root->filhoEsquerda, chave);
                if (root->filhoDireita != nullptr){
                    if (root->filhoDireita->altura == -1){
                        Nodo<T> * tmp = root->filhoDireita;
                        root->filhoDireita = nullptr;
                        delete tmp;
                    }
                }
                if (root->filhoEsquerda == nullptr){
                    if (root->filhoEsquerda->altura == -1){
                        Nodo<T> * tmp = root->filhoEsquerda;
                        root->filhoEsquerda = nullptr;
                        delete tmp;
                    }
                }
                root->altura--;
            } else {
                if (root->filhoDireita == nullptr && root->filhoEsquerda == nullptr){
                    root->altura = -1;
                } else if (root->filhoDireita && root->filhoEsquerda){
                    Nodo<T> * predecessor = get_max(root->filhoDireita);

                    root->chave = predecessor->chave;
                    remover_rec(root->filhoDireita, predecessor->chave);
                    root->altura--;
                } else {
                    Nodo<T> * child = (root->filhoDireita)? root->filhoDireita: root->filhoEsquerda;
                    Nodo<T> * curr = root;

                    root = child;
                    delete curr;
                }
            }
        }
    }
    void get_rec(Nodo<T>* tmp, T chave,Nodo<T>* filho){
        if(tmp != nullptr){
            if(tmp->chave != chave){
                filho = tmp;
                if (chave > tmp->chave) {
                    tmp = tmp->filhoDireita;
                }
                else {
                    tmp = tmp->filhoEsquerda;
                }
            }
            get_rec(tmp);
        }
    }
    Nodo<T>* get_max(Nodo<T>* tmp)
    {
        while (tmp->filhoEsquerda != nullptr) {
            tmp = tmp->filhoEsquerda;
        }
        return tmp;
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
        bool result = false;

        result = contem_rec(chave,this->_raiz);

        return result;
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
        remover_rec(this->_raiz,chave);
        int a = 0;
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<T> filhoEsquerdaDe(T chave) const{
        std::optional<T> filho;
        if(this->_raiz != nullptr){
            if(this->_raiz->chave != chave){
                filho = filhoEsquerdaDe_rec(chave,this->_raiz);
            } else {
                filho = this->_raiz->filhoEsquerda->chave;
            }
        }


        return filho;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    std::optional<T> filhoDireitaDe(T chave) const{
        std::optional<T> filho;
        if(this->_raiz != nullptr){
            if(this->_raiz->chave != chave){
                filho = filhoDireitaDe_rec(chave,this->_raiz);
            } else {
                if(this->_raiz->filhoDireita != nullptr){
                    filho = this->_raiz->filhoDireita->chave;
                }
            }
        }
        return filho;
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
