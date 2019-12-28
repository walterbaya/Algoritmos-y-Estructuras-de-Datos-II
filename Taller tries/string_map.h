#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>
#include <set>

using namespace std;

template<typename T>
class string_map {
public:

    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    void insert(const pair<string, T>&par);

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;

    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    int size() const;

    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo(): definicion(NULL), siguientes(256,NULL){
        }
    };
    Nodo* raiz;
    int _size;
    bool definida(const Nodo* n, const string &key, int i) const;
    void definir(Nodo* &n, const pair<string, T> & par, int i);
    T& recorrer(Nodo* n,const string& key,int i);
    int nroDescendientes(Nodo* n);
    vector<pair<string, T>> claves;
    void reemplazar(const pair<string, T> &par);
    void borrar(Nodo* &n,int l,const string &clave);
};
#include "string_map.hpp"

#endif // STRING_MAP_H_
