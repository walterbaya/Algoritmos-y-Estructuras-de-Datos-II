#include "Conjunto.h"

template<class T>
Conjunto<T>::Conjunto() : _raiz(NULL), cantidadNodos(0) {
}

template<class T>
Conjunto<T>::~Conjunto() {
    this->destruir(this->_raiz);
}

template<class T>
void Conjunto<T>::destruir(Nodo *n) {
    if (n != NULL) {
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    Nodo *node = this->_raiz;
    bool res = false;
    if (node == NULL) {

    } else {
        while (!res && node != NULL) {
            if (node->valor == clave) {
                res = true;
            } else {
                if (node->valor < clave) {
                    node = node->der;
                } else {
                    node = node->izq;
                }
            }
        }
    }
    return res;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    Nodo *node = this->_raiz;
    bool esta = false;
    if (node == NULL) {
        this->_raiz = new Nodo(clave);
        cantidadNodos++;
    } else {
        if (this->pertenece(clave)) {

        } else {
            while (!esta) {
                if (node->valor < clave) {
                    if (node->der == NULL) {
                        node->der = new Nodo(clave);
                        node->der->padre = node;
                        esta = true;
                        cantidadNodos++;
                    } else {
                        node = node->der;
                    }
                } else {
                    if (node->izq == NULL) {
                        node->izq = new Nodo(clave);
                        node->izq->padre = node;
                        esta = true;
                        cantidadNodos++;
                    } else {
                        node = node->izq;
                    }
                }
            }
        }
    }
}


template<class T>
void Conjunto<T>::remover(const T &clave) {
    Nodo *borrar = this->obtenerBuscado(clave);
    Nodo *padre = borrar->padre;
    //si el nodo buscado es una hoja lo borro
    if (borrar->izq == NULL && borrar->der == NULL) {
        if (borrar->valor == _raiz->valor) {
            delete borrar;
            this->_raiz = NULL;
            cantidadNodos--;
        } else {
            if (padre->valor < borrar->valor) {
                padre->der = NULL;
                delete borrar;
                cantidadNodos--;
            } else {
                padre->izq = NULL;
                delete borrar;
                cantidadNodos--;
            }
        }
    } else
        //Si el nodo buscado tiene un hijo reemplazo el nodo por su hijo
    {
        if (borrar->der != NULL && borrar->izq == NULL) { //si el nodo es la cabeza
            if (padre == NULL) {
                _raiz = borrar->der;
                _raiz->padre = NULL;
                delete borrar;
                cantidadNodos--;
            } else { //si el nodo esta en el cuerpo
                if (padre->valor < borrar->valor) {
                    padre->der = borrar->der;
                    borrar->der->padre = padre;
                    delete borrar;
                    cantidadNodos--;
                } else {
                    padre->izq = borrar->der;
                    borrar->der->padre = padre;
                    delete borrar;
                    cantidadNodos--;
                }
            }

        } else {  //si el subarbol izquierdo es no nulo
            if (borrar->izq != NULL && borrar->der == NULL) {
                padre = borrar->padre;
                if (padre == NULL) {
                    _raiz = borrar->izq;
                    _raiz->padre = NULL;
                    delete borrar;
                    cantidadNodos--;
                } else {
                    if (padre->valor < borrar->valor) {
                        padre->der = borrar->izq;
                        borrar->izq->padre = padre;
                        delete borrar;
                        cantidadNodos--;
                    } else {
                        padre->izq = borrar->izq;
                        borrar->izq->padre = padre;
                        delete borrar;
                        cantidadNodos--;
                    }
                }

            } else { //si tiene dos hijos
                Nodo* sucesor = this->sucesor(clave);
                Nodo* padreSuc=sucesor->padre;
                if(sucesor->valor==borrar->der->valor){  // si el nodo es simple
                    borrar->valor=sucesor->valor;
                    borrar->der=sucesor->der;
                    delete sucesor;
                    cantidadNodos--;
                }
                else{ //nodo complejo
                    borrar->valor=sucesor->valor;
                    if(sucesor->der!=NULL){
                        padreSuc->izq=sucesor->der;
                        sucesor->der->padre=padreSuc;
                        cantidadNodos--;
                        delete sucesor;
                    }
                    else{
                        padreSuc->izq=NULL;
                        cantidadNodos--;
                        delete sucesor;
                    }
                }
            }
        }
    }
}

template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    return this->sucesor(clave)->valor;
}

template<class T>
const T &Conjunto<T>::minimo() const {
    Nodo *n = this->_raiz;
    T *res;
    while (n->izq != NULL) {
        n = n->izq;
        res = &n->valor;
    }
    return *res;
}

template<class T>
const T &Conjunto<T>::maximo() const {
    Nodo *n = this->_raiz;
    T *res;
    while (n->der != 0) {
        n = n->der;
        res = &n->valor;
    }
    return *res;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return cantidadNodos;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::obtenerBuscado(const T &clave) {
    Nodo *n = this->_raiz;
    bool encontrado = false;
    while (!encontrado) {
        if (n->valor == clave) {
            encontrado = true;
        } else {
            if (n->valor < clave) {
                n = n->der;
            } else {
                n = n->izq;
            }
        }
    }
    return n;
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::sucesor(const T &clave) {
    Nodo *n = this->obtenerBuscado(clave);
    if (n->der != NULL) {
        //busco el minimo dentro del subarbol derecho
        Nodo *minimoDer = n->der;
        while (minimoDer->izq != NULL) {
            minimoDer = minimoDer->izq;
        }
        return minimoDer;
    } else {
        if (n->valor == n->padre->izq->valor) {
            return n->padre;
        } else {
            while (n->padre->izq == NULL) {
                n = n->padre;
            }
            return n;
        }
    }
}













