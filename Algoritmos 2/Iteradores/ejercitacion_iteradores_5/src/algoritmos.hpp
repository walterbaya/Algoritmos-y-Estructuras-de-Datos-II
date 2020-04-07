#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H
using namespace std;

#include <utility>
#include <iterator>
#include <vector>
//Ejercicio 1

template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor &c) {
    typename Contenedor::const_iterator it = c.begin();
    typename Contenedor::value_type min = *it;
    while (it != c.end()) {
        if (min > *it) {
            min = *it;
        }
        ++it;
    }
    return min;
}

template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor &c) {
    typename Contenedor::value_type suma = 0;
    int cant = 0;
    for (typename Contenedor::const_iterator it = c.begin(); it != c.end(); ++it) {
        suma = suma + *it;
        cant++;
    }
    return suma / cant;
}

template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator &desde, const Iterator &hasta) {
    typename Iterator::value_type min = *desde;
    for (Iterator it = desde; it != hasta; ++it) {
        if (min > *it) {
            min = *it;
        }
    }
    return min;
}

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator &desde, const Iterator &hasta) {
    typename Iterator::value_type suma = 0;
    int cant = 0;
    for (Iterator it = desde; it != hasta; ++it) {
        suma = suma + *it;
        cant++;
    }
    return suma / cant;
}

//Ejercicio 4
template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type &elem) {
    for (typename Contenedor::iterator it = c.begin(); it != c.end(); ++it) {
        if (elem == *it) {
            c.erase(it);
        }
    }
}

//Ejercicio 5
template<class Contenedor>
bool ordenado(const Contenedor &c) {
    bool res=true;
    typename Contenedor::const_iterator it=c.begin();
    typename Contenedor::value_type ValorAnterior = *it;
    while (it != c.end()) {
        if(ValorAnterior>*it){
            res=false;
        }
        ++it;
    }
    return res;
}



#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
