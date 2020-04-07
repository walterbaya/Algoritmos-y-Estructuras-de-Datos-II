#include "Lista.h"

template<typename T>
Lista<T>::Lista() : first(NULL), last(NULL), numElem(0) {
}

template<typename T>
Lista<T>::Lista(const Lista<T> &l) : Lista() {
    *this = l;
}

template<typename T>
Lista<T>::~Lista() {
    while(this->first!=NULL){
        this->eliminar(0);
    }
}
template<typename T>
Lista<T> &Lista<T>::operator=(const Lista<T> &aCopiar) {
    //hay que transformar el vector a el vacio
    while(this->first!=NULL){
        this->eliminar(0);
    }
    //luego agregarle los elementos
    for (int i = 0; i < aCopiar.longitud(); i++) {
        this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

template<typename T>
void Lista<T>::agregarAdelante(const T &elem) {
    Nodo *nodo = new Nodo(NULL, NULL, elem);
    nodo->before = NULL;
    nodo->next = first;
    if (nodo->next != NULL) {
        nodo->next->before = nodo;
    }
    if (nodo->next == NULL) {
        last = nodo;
    }
    first = nodo;
    numElem++;
}

template<typename T>
void Lista<T>::agregarAtras(const T &elem) {
    Nodo *nodo = new Nodo(NULL, NULL, elem);
    nodo->data = elem;
    nodo->before = last;
    nodo->next = NULL;
    if (nodo->before != NULL) {
        nodo->before->next = nodo;
    }
    if (nodo->before == NULL) {
        first = nodo;
    }
    last = nodo;
    numElem++;
}

template<typename T>
void Lista<T>::eliminar(Nat i) {
    Nodo* p=first;
    for (int j = 0; j < i; j++) {
        p=p->next;
    }
    if(this->longitud()==1){
        delete p;
        this->first=NULL;
        this->last=NULL;
        numElem--;
    }
    else{
        if(i==0){
            first=first->next;
            first->before=NULL;
            delete p;
            numElem--;
        }
        else{
            if(i==this->longitud()-1){
                last=p->before;
                last->next=NULL;
                delete p;
                numElem--;
            }
            else{
                Nodo* next=p->next;
                Nodo* prev=p->before;
                next->before=prev;
                prev->next=next;
                delete p;
                numElem--;
            }
        }
    }

}

template<typename T>
int Lista<T>::longitud() const {
    return numElem;
}


template<typename T>
const T &Lista<T>::iesimo(Nat i) const {
    Nodo *res = first;
    for (int j = 0; j < i; j++) {
        res = res->next;
    }
    return res->data;
}


template<typename T>
T &Lista<T>::iesimo(Nat i) {
    Nodo *res = first;
    for (int j = 0; j < i; j++) {
        res = res->next;
    }
    return res->data;
}

template<typename T>
void Lista<T>::mostrar(ostream &o) {
    // Completar
}