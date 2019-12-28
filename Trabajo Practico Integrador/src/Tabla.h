#ifndef TP3_TABLA_H
#define TP3_TABLA_H


#include "Tipos.h"
#include "modulos_basicos/string_map.h"
#include "modulos_basicos/linear_set.h"
#include "Registro.h"

class Tabla{
public:
    /**
     * Los registros deben respetar el orden dado por el vector _campos.
     */
    Tabla(vector<NombreCampo> _campos, NombreCampo _clave);

    /**
     * Constructor por defecto(necesario para usar string_map)
     */
    Tabla();

    /**
     * Pre: campos iguales, mismo orden de campos(si no, no tiene efecto).
     */
    void insertar(const Registro &r);

    void borrar(const Valor &valorClave);

    /**
     * Busco en el diccClaveRegistro, el costo es |V|.
     */
    Registro obtenerRegistro(const Valor &valorClave) const;

    /**
     * Devuelve todos los registros de la tabla en un vector.
     */
    linear_set<Registro> tablaCompleta() const;

    /**
     * Devuelve el indice correspondiente al orden del campo dentro de los registros de
     * la tabla.
     */
    int obtenerIndice(const NombreCampo &campo) const;

    /**
     * Cantidad de registros definidos en la tabla.
     */
    int size() const;

    NombreCampo clave() const;

    vector<NombreCampo> campos() const;

    bool definido(Valor valorCampoClave);

    linear_set<Valor> clavesDef() const;

private:
    /**
     * Dicc, de campos a Indice que indica el orden dentro del registro
     */
    string_map<int> diccCampoIndice;

    /**
     * Dicc, de valor campo clave a registro.(Permite buscar registro en |V|, si tengo la clave)
     */
    string_map<Registro> diccClaveRegistro;

    /**
     * Conjunto de registros para acceder a todos los registros definidos de manera rapida.
     */
    linear_set<Registro> conjRegistros;

    /**
     * Campos definidos en la tabla(con orden)
     */
    vector<NombreCampo> camposEnOrden;

    /**
     * Campo clave de los registros
     */
    NombreCampo campoClave;

};


#endif //TP3_TABLA_H

