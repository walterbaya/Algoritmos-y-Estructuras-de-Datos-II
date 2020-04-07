
#include <iostream>
#include "string_map.h"

template<typename T>
string_map<T>::string_map(): raiz(new Nodo()), _size(0), claves({}) {

}


template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    //borro hasta que quede vacio excepto la raiz
    for (int i = 0; i < claves.size(); i++) {
        pair<string, T> par = claves[i];
        if (count(par.first)) {
            erase(par.first);
        }
    }
    for (int j = 0; j < d.claves.size(); j++) {
        this->insert(d.claves[j]);
    }
}

template<typename T>
string_map<T>::~string_map() {
    for (int i = 0; i < claves.size(); i++) {
        pair<string, T> par = claves[i];
        if (count(par.first)) {
            erase(par.first);
        }
    }
    delete(raiz);
    raiz=NULL;
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    if (definida(this->raiz, clave, 0)) {
        return 1;
    } else {
        return 0;
    }
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    return recorrer(this->raiz, clave, 0);
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    return recorrer(this->raiz, clave, 0);
}



template<typename T>
void string_map<T>::erase(const string &clave) {
    Nodo * actNodo = this->raiz;
    Nodo * ultNodo = this->raiz;
    int l = 0;
    for (int i = 0; i < clave.size(); i++) {
        if (actNodo->definicion != NULL ||
            nroDescendientes(actNodo) > 1) { //caso en el que hay que mover el nodo ultNodo
            ultNodo = actNodo;
            l = i;
        }
        actNodo = actNodo->siguientes[int(clave[i])]; //avanzo el nodo a el siguiente
    }
    //al salir del for tengo mi actNodo apuntando a el nodo hasta el que quiero borrar
    //Creo un puntero a la posicion de memoria de actNodo->definicion y borro la definicion
    delete (actNodo->definicion);
    actNodo->definicion = NULL;
    //si el numero de hijos es distinto de 0 no hago nada sino borro todos los nodos desde el actNodo hasta el ultNodo
    //usando el procedimiento
    if (nroDescendientes(actNodo) == 0) {
       Nodo* siguiente = ultNodo->siguientes[int(clave[l])];
       ultNodo->siguientes[int(clave[l])]=NULL;
       l++;
       ultNodo=siguiente;
       borrar(ultNodo,l,clave);
    }
    _size--;
}

template<typename T>
void string_map<T>::borrar(string_map::Nodo *&n, int l,const string &clave) {
    if(n!=NULL){
        Nodo* siguiente = n->siguientes[int(clave[l])];
        delete n;
        n=siguiente;
        borrar(n,l+1,clave);
    }
}




template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &par) {
    definir(this->raiz, par, 0);
}


template<typename T>
bool string_map<T>::definida(const string_map::Nodo *n, const string &key, int i) const {
    //veo que pasa con la raiz
    if (i == 0 && n->siguientes[int(key[i])] == NULL) {
        return false;
    }//caso final de la recursion
    else if (i == key.size() - 1) {
        if (n->siguientes[int(key[i])] == NULL) {
            return false;
        } else {
            Nodo *temp = n->siguientes[int(key[i])];
            return temp->definicion != NULL;
        }
    } else {
        if (n->siguientes[int(key[i])] == NULL) {
            return false;
        } else {
            definida(n->siguientes[int(key[i])], key, i + 1);
        }

    }
}


template<typename T>
void string_map<T>::definir(string_map::Nodo *&n, const pair<string, T> &par, int i) {
    if (i == par.first.size() - 1) {
        if (count(par.first)) {
            T valor = par.second;
            Nodo *temp = n->siguientes[int(par.first[i])];
            *temp->definicion = valor;
            claves.push_back(par);
        } else {
            T valor = par.second;
            Nodo *temp = new Nodo();
            temp->definicion = new T;
            *temp->definicion = valor;
            n->siguientes[int(par.first[i])] = temp;
            _size++;
            claves.push_back(par);
        }
    } else {
        //CASO EN EL QUE NO ESTA DEFINIDO
        if (n->siguientes[int(par.first[i])] == NULL) {
            n->siguientes[int(par.first[i])] = new Nodo();
            definir(n->siguientes[int(par.first[i])], par, i + 1);
            //CASO EN EL QUE ESTA DEFINIDO
        } else {
            definir(n->siguientes[int(par.first[i])], par, i + 1);
        }
    }
}

template<typename T>
T &string_map<T>::recorrer(string_map::Nodo *n, const string &key, int i) {
    if (i == key.size()) {
        return *n->definicion;
    } else {
        recorrer(n->siguientes[int(key[i])], key, i + 1);
    }
}


template<typename T>
int string_map<T>::nroDescendientes(string_map::Nodo *n) {
    int cant = 0;
    for (int i = 0; i < 256; i++) {
        if (n->siguientes[i] != NULL) {
            cant++;
        }
    }
    return cant;
}


template<typename T>
void string_map<T>::reemplazar(const pair<string, T> &par) {
    for (int i = 0; i < claves.size(); i++) {
        pair<string, T> c = claves[i];
        if (c.first != par.first) {
            claves[i] = c;
        }
    }
}


/*
template<typename T>
void string_map<T>::erase(const string &clave) {
    Nodo *actNodo = this->raiz;
    Nodo *ultNodo = this->raiz;
    int l = 0;
    for (int i = 0; i < clave.size(); i++) {
        if (actNodo->definicion != NULL ||
            nroDescendientes(actNodo) > 1) { //caso en el que hay que mover el nodo ultNodo
            ultNodo = actNodo;
            l = i;
        }
        actNodo = actNodo->siguientes[int(clave[i])]; //avanzo el nodo a el siguiente
    }
    //al salir del for tengo mi actNodo apuntando a el nodo hasta el que quiero borrar
    //Creo un puntero a la posicion de memoria de actNodo->definicion y borro la definicion
    T *def = actNodo->definicion;
    delete def;
    actNodo->definicion = NULL;
    //si el numero de hijos es distinto de 0 no hago nada sino borro todos los nodos desde el actNodo hasta el ultNodo
    if (nroDescendientes(actNodo) == 0) {
        for (int j = l; j < clave.size()-1; j++) {
            Nodo *borrar = ultNodo->siguientes[int(clave[j])];
            ultNodo->siguientes[int(clave[j])] = NULL;
            delete ultNodo->siguientes[int(clave[j])];
            ultNodo = borrar;
        }
    }
    _size--;
    clavesEliminadas.push_back(clave);

}
*/






