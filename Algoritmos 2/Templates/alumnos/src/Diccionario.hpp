#ifndef SOLUCION_DICCIONARIO_HPP
#define SOLUCION_DICCIONARIO_HPP
template <class Clave ,class Valor>
class Diccionario {
public:
    Diccionario();
    void definir(Clave k, Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;

private:
    struct Asociacion {
        Asociacion(Clave k, Valor v);
        Clave clave;
        Valor valor;
    };
    std::vector<Asociacion> _asociaciones;
};

template <class Clave,class Valor>
Diccionario<Clave,Valor>::Diccionario() {
}

template<class Clave,class Valor>
Diccionario<Clave,Valor>::Asociacion::Asociacion(Clave k, Valor v) : clave(k), valor(v) {
}
template<class Clave,class Valor>
void Diccionario<Clave,Valor>::definir(Clave k, Valor v) {
    for (int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            _asociaciones[i].valor = v;
            return;
        }
    }
    _asociaciones.push_back(Asociacion(k, v));
}

template <class Clave,class Valor>
bool Diccionario<Clave,Valor>::def(Clave k) const {
    for (int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return true;
        }
    }
    return false;
}

template <class Clave,class Valor>
Valor Diccionario<Clave,Valor>::obtener(Clave k) const {
    for (int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return _asociaciones[i].valor;
        }
    }
}

#endif //SOLUCION_DICCIONARIO_HPP
