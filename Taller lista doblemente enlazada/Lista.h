#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

#include <string>
#include <ostream>

using namespace std;

typedef unsigned long Nat;

template <typename T>
class Lista {
public:

    /**
     * Constructor por defecto de la clase Lista.
     */
    Lista();

    /**
     * Constructor por copia de la clase Lista.
     */
    Lista(const Lista& l);

    /**
     * Destructor de la clase Lista.
     */
    ~Lista();

    /**
     * Operador asignacion
     * @param aCopiar
     * @return
     */
    Lista& operator=(const Lista& aCopiar);

    /**
     * Agrega un elemento al principio de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAdelante(const T& elem);

    /**
     * Agrega un elemento al final de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAtras(const T& elem);

    /**
     * Elimina el i-ésimo elemento de la Lista.
     * @param i posición del elemento a eliminar
     */
    void eliminar(Nat i);

    /**
     * Devuelve la cantidad de elementos que contiene la Lista.
     * @return
     */
    int longitud() const;

    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia no modificable
     */
    const T& iesimo(Nat i) const;
    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia modificable
     */
    T& iesimo(Nat i);

    /**
     * Muestra la lista en un ostream
     * formato de salida: [a_0, a_1, a_2, ...]
     * donde a_i es el resultado del "mostrar" del alumno i de la lista (ya definido)
     * @param o
     */
    void mostrar(ostream& o);

    /**
     * Utiliza el método mostrar(os) para sobrecargar el operador <<
     */
    friend ostream& operator<<(ostream& os, Lista& l) {
        l.mostrar(os);
        return os;
    }

private:

    struct Nodo{
        Nodo(Nodo* a,Nodo* b,const T& d);
        Nodo* next;
        Nodo* before;
        T data; //los datos del nodo  se podrian a modificar
    };
    Nodo* first;
    Nodo* last;
    int numElem;
};

template<typename T>
Lista<T>::Nodo::Nodo(Lista::Nodo  *a, Lista::Nodo *b,const T& d) : next(a), before(b), data(d){

}


#include "Lista.hpp"

#endif
