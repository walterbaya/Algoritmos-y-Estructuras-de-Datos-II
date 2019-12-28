#ifndef __REGISTRO_H__
#define __REGISTRO_H__

#include <set>
#include "modulos_basicos/string_map.h"
#include "Tipos.h"

using namespace std;

class Registro {
public:
    Registro();

    void definir(const NombreCampo& campo, const Valor& valor);

    void eliminarCampo(const NombreCampo &campo);

    vector<NombreCampo> campos() const;

    Registro &operator=(const Registro &r);

    bool operator==(const Registro &r)const;

    /**
     * Devuelve una referencia al valor asociado a la clave campo, si la clave no esta definida,
     * la define, y luego devuelve la referencia a la posicion donde se guarda el valor.
     */
    Valor& operator[](const NombreCampo& campo);

    /**
     * Permite renombrar un campo manteniendo su orden y su valor.
     */
    Registro &renombrar(const NombreCampo &nc1, const NombreCampo &nc2);

    /**
     * Si se tiene el indice que indica el orden del campo dentro del registro,
     * la operacion permite obtener el valor en tiempo constante.
     */
    Valor const &obtenerRapido(int i) const;

    bool estaDef(const NombreCampo &campo) const;


private:
    /**
     * Indica la posicion en la que se encuentra ordenado el campo.
     * Notar que el valor debe encontrarse en la misma posicion en su vector correspondiente.
     */
    int indiceCampo(const NombreCampo& campo) const;

    string_map<Valor> campoValor;

    /**
     * Vector de punteros a los valores definidos en el string map.
     * Guardarlos de esta manera me permite redefinir valores solo una vez en la estrucura.
     * No es necesario actualizarlo cada vez que cambio un valor, solo cuando agrego nuevos.
     */
    vector<Valor> datos;

    vector<NombreCampo> ordenCampos;
};

#endif /*__REGISTRO_H__*/
