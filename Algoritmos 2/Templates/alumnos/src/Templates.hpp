//
// Created by walter on 1/10/19.
//

#ifndef SOLUCION_TEMPLATES_HPP
#define SOLUCION_TEMPLATES_HPP

template<class T>T cuadrado(T x) {
    return x * x;
}

template<class Contenedor, class Elem> bool contiene(Contenedor s, Elem c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

template<class Contenedor> bool esPrefijo(Contenedor a, Contenedor b){
    bool res=true;
    if(a.size()<b.size()){
        for (int i = 0; i < a.size()&&res; i++) {
            res = a[i] == b[i];
        }
    }
    else{
        res=false;
    }
return res;
}
template <class Contenedor, class Elem> Elem maximo(Contenedor c){
    Elem maximoTemp=c[0];
    for (int i = 0; i < c.size(); i++) {
        if(c[i]>maximoTemp){
            maximoTemp=c[i];
        }
    }
    return maximoTemp;
}

#endif //SOLUCION_TEMPLATES_HPP
