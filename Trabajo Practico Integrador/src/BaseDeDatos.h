#ifndef TP3_BASEDEDATOS_H
#define TP3_BASEDEDATOS_H


#include "modulos_basicos/string_map.h"
#include "Tabla.h"
#include "Registro.h"
#include "modulos_basicos/linear_set.h"
#include "Consulta.h"

class BaseDeDatos {
public:
    BaseDeDatos();
    void agregarTabla(const NombreTabla &nt, const Tabla &t);
    void borrar(const NombreTabla &nt);
    void registrar(const NombreTabla &nt,const Registro &r);
    linear_set<Registro> &resolver(const Consulta &cons);
    Tabla &obtenerTabla(NombreTabla &nombreTabla);
    Registro combinar(Registro &r1,Registro &r2);

private:
    string_map<Tabla> bd;
    linear_set<Registro> resConsulta;
    linear_set<Registro>tablaCompleta(const NombreTabla &nt);
    void selectConClave(const Tabla &t,const Clave &c,const Valor &v);
    void selectSinClave(Tabla &t,const NombreCampo &c,const Valor &v);
    void joinConClaves(const Consulta &c, const NombreCampo &c1,const NombreCampo &c2);
    void selectConClaveDeSelectSinClave(Tabla &t, const Valor &valorClave, const NombreCampo &campo2, const Valor &valor2);
    void interseccionDosSelecciones(Tabla &t1,Tabla &t2,const NombreCampo &c1,const NombreCampo &c2,const Valor &v1,const Valor &v2);
    void hacerSelect(const Consulta &cons);
    void hacerMatch(const Consulta &cons);
    void hacerProj(const Consulta &cons);
    void hacerInter(const Consulta &cons);
    void hacerUnion(const Consulta &cons);
    void hacerProduct(const Consulta &cons);

};



#endif //TP3_BASEDEDATOS_H
