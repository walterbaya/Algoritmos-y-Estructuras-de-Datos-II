#include "BaseDeDatos.h"


BaseDeDatos::BaseDeDatos() = default;

void BaseDeDatos::agregarTabla(const NombreTabla &nt, const Tabla &t) {
    this->bd.insert(make_pair(nt, t));
}

void BaseDeDatos::borrar(const NombreTabla &nt) {
    this->bd.erase(nt);
}

void BaseDeDatos::registrar(const NombreTabla &nt, const Registro &r) {
    this->bd.at(nt).insertar(r);
}

Tabla &BaseDeDatos::obtenerTabla(NombreTabla &nombreTabla) {
    return this->bd[nombreTabla];
}

linear_set<Registro> &BaseDeDatos::resolver(const Consulta &cons) {

    if (cons.tipo_consulta() == FROM) {
        this->resConsulta = tablaCompleta(cons.nombre_tabla());
    } else if (cons.tipo_consulta() == SELECT) {
        hacerSelect(cons);
    } else if (cons.tipo_consulta() == MATCH) {
        hacerMatch(cons);
    } else if (cons.tipo_consulta() == PROJ) {
        hacerProj(cons);
    } else if (cons.tipo_consulta() == RENAME) {
        linear_set<Registro> res = resolver(cons.subconsulta1());
        linear_set<Registro> nuevo;
        for (Registro r : res) {
            nuevo.fast_insert(r.renombrar(cons.campo1(), cons.campo2()));
        }
        this->resConsulta = nuevo;
    } else if (cons.tipo_consulta() == INTER) {
        hacerInter(cons);
    } else if (cons.tipo_consulta() == PRODUCT) {
        hacerProduct(cons);
    } else {
        hacerUnion(cons);
    }
    return this->resConsulta;
}

linear_set<Registro> BaseDeDatos::tablaCompleta(const NombreTabla &nt) {
    Tabla tabla = this->bd.at(nt);
    return tabla.tablaCompleta();
}

void BaseDeDatos::selectConClave(const Tabla &t, const Clave &c, const Valor &v) {
    this->resConsulta = {t.obtenerRegistro(v)};
}


void BaseDeDatos::selectSinClave(Tabla &t, const NombreCampo &c, const Valor &v) {
    linear_set<Registro> res;
    int indiceCampo = t.obtenerIndice(c);
    for (Valor x : t.clavesDef()) {
        Registro r = t.obtenerRegistro(x);
        if (r.obtenerRapido(indiceCampo) == v) {
            res.fast_insert(r);
        }
    }
    this->resConsulta = res;
}

//Combina poniendo el primer registro adelante y el segundo atras
//Complejidad O(v+c)
Registro BaseDeDatos::combinar(Registro &r1, Registro &r2) {
    Registro final;
    vector<NombreCampo> campos1;
    vector<NombreCampo> campos2;
    for (NombreCampo nc : r1.campos()) {
        campos1.push_back(nc);
    }
    for (NombreCampo nc : r2.campos()) {
        campos2.push_back(nc);
    }
    for (int i = 0; i < campos1.size(); i++) {
        final.definir(campos1[i],
                      r1.operator[](campos1[i]));  //O(v+c)*O(1) se considera la cantidad de campos constantes
    }
    for (int i = 0; i < campos2.size(); i++) {
        if (final.estaDef(campos2[i])) {

        } else {
            final.definir(campos2[i], r2.operator[](campos2[i]));
        }
    }
    return final;
}

void BaseDeDatos::joinConClaves(const Consulta &c, const NombreCampo &c1, const NombreCampo &c2) {
    linear_set<Registro> res;
    NombreCampo clave;
    Tabla &t1 = bd.at(c.subconsulta1().subconsulta1().nombre_tabla()); //las tablas se obtienen por referencia
    Tabla &t2 = bd.at(c.subconsulta1().subconsulta2().nombre_tabla());
    Tabla *masChica;
    Tabla *masGrande;
    //ver cual es la tabla con menos registros
    if (t1.tablaCompleta().size() < t2.tablaCompleta().size()) {
        masChica = &t1;  //mas referencias...
        masGrande = &t2;
        clave = t1.clave();
    } else {
        masChica = &t2;
        masGrande = &t1;
        clave = t2.clave();
    }


    for (Registro r : masChica->tablaCompleta()) { //O(min(n1,n2)) tabla completa devuelve por referencia la tabla
        if (!masGrande->definido(r[clave])) { //O(V)

        } else {
            Registro r2 = masGrande->obtenerRegistro(r[clave]);
            Registro f = combinar(r, r2);  // O(V+C)
            res.fast_insert(f);
        }
    }
    this->resConsulta = res; //devolver por copia O(k.....)
}

void BaseDeDatos::selectConClaveDeSelectSinClave(Tabla &t, const Valor &valorClave, const NombreCampo &campo2,
                                            const Valor &valor2) {
    Registro miRegistro = t.obtenerRegistro(valorClave);
    linear_set<Registro> res;
    if (miRegistro[campo2] == valor2) {
        res.fast_insert(miRegistro);
    }
    this->resConsulta = res;
}

void BaseDeDatos::interseccionDosSelecciones(Tabla &t1, Tabla &t2, const NombreCampo &c1, const NombreCampo &c2,
                                        const Valor &v1, const Valor &v2) {
    linear_set<Registro> res;
    int indiceCampo1 = t1.obtenerIndice(c1);
    int indiceCampo2 = t2.obtenerIndice(c2);
    for (Registro r: t1.tablaCompleta()) {
        if (r.obtenerRapido(indiceCampo1) == v1 && r.obtenerRapido(indiceCampo2) == v2) {
            res.fast_insert(r);
        }
    }
    this->resConsulta = res;
}


void BaseDeDatos::hacerSelect(const Consulta &cons) {
    linear_set<Registro> res;
    if (cons.subconsulta1().tipo_consulta() == FROM) {
        if (cons.campo1() ==
            bd.at(cons.subconsulta1().nombre_tabla()).clave()) {          //me fijo que el campo1 sea campo clave
            selectConClave(bd.at(cons.subconsulta1().nombre_tabla()), cons.campo1(), cons.valor());
        } else {
            selectSinClave(bd.at(cons.subconsulta1().nombre_tabla()), cons.campo1(),
                                 cons.valor()); //sino es campo clave hago un select sin clave
        }
    } else {
        if (cons.subconsulta1().tipo_consulta() == SELECT &&
            cons.subconsulta1().subconsulta1().tipo_consulta() == FROM &&
            cons.campo1() == bd.at(cons.subconsulta1().subconsulta1().nombre_tabla()).clave() &&
            cons.subconsulta1().campo1() != bd.at(cons.subconsulta1().subconsulta1().nombre_tabla()).clave()) {
            selectConClaveDeSelectSinClave(bd.at(cons.subconsulta1().subconsulta1().nombre_tabla()), cons.valor(),
                                                 cons.subconsulta1().campo1(), cons.subconsulta1().valor());
        } else {
            resolver(cons.subconsulta1());
            for (Registro r : this->resConsulta) {
                if (r.operator[](cons.campo1()) == cons.valor()) {
                    res.fast_insert(r);
                }
            }
            this->resConsulta = res;
        }
    }
}

void BaseDeDatos::hacerMatch(const Consulta &cons) { //Corregir
    linear_set<Registro> res;
    if (cons.subconsulta1().tipo_consulta() == PRODUCT && cons.subconsulta1().subconsulta1().tipo_consulta() == FROM &&
        cons.subconsulta1().subconsulta2().tipo_consulta() == FROM) {
        joinConClaves(cons, cons.campo1(), cons.campo2());
    } else {
        linear_set<Registro> res_1 = resolver(cons.subconsulta1());
        NombreCampo campo1 = cons.campo1();
        NombreCampo campo2 = cons.campo2();
        for (Registro r : res_1) {
            if (r[campo1] == r[campo2]) {
                res.fast_insert(r);
            }
        }
        this->resConsulta = res;
    }
}

void BaseDeDatos::hacerProj(const Consulta &cons) {
    set<NombreCampo> campos = cons.conj_campos();
    linear_set<Registro> res_1 = resolver(cons.subconsulta1());
    linear_set<Registro> res;
    for (Registro r : res_1) {
        Registro aux;
        for (NombreCampo c : campos) {
            aux.definir(c, r[c]);
        }
        res.fast_insert(aux);
    }
    this->resConsulta = res;
}

bool esInterDosSelecciones(const Consulta &cons) {
    return cons.subconsulta1().tipo_consulta() == SELECT &&
           cons.subconsulta2().tipo_consulta() == SELECT &&
           cons.subconsulta1().subconsulta1().tipo_consulta() == FROM &&
           cons.subconsulta2().subconsulta1().tipo_consulta() == FROM &&
           cons.subconsulta2().subconsulta1().nombre_tabla() == cons.subconsulta1().subconsulta1().nombre_tabla();
}

void BaseDeDatos::hacerInter(const Consulta &cons) {
    if (esInterDosSelecciones(cons)) {
        Tabla t1 = this->bd.at(cons.subconsulta1().subconsulta1().nombre_tabla());
        Tabla t2 = this->bd.at(cons.subconsulta2().subconsulta1().nombre_tabla());
        Valor valor1 = cons.subconsulta1().valor();
        Valor valor2 = cons.subconsulta2().valor();
        NombreCampo campo1 = cons.subconsulta1().campo1();
        NombreCampo campo2 = cons.subconsulta2().campo1();
        interseccionDosSelecciones(t1, t2, campo1, campo2, valor1, valor2);
    } else {
        linear_set<Registro> res;
        linear_set<Registro> res1 = resolver(cons.subconsulta1());
        linear_set<Registro> res2 = resolver(cons.subconsulta2());
        for (Registro r1 : res1) {
            for (Registro r2: res2) {
                if (r1 == r2) {
                    res.fast_insert(r1);
                }
            }
        }
        this->resConsulta = res;
    }
}

void BaseDeDatos::hacerUnion(const Consulta &cons) {
    linear_set<Registro> res1 = resolver(cons.subconsulta1());
    linear_set<Registro> res2 = resolver(cons.subconsulta2());
    linear_set<Registro> res;
    for (const Registro &r : res1) {
        res.fast_insert(r);
    }
    for (const Registro &r : res2) {
        if(!res.count(r)){
            res.fast_insert(r);
        }
    }

    this->resConsulta = res;
}

void BaseDeDatos::hacerProduct(const Consulta &cons) {
    linear_set<Registro> res_1 = resolver(cons.subconsulta1());
    linear_set<Registro> res_2 = resolver(cons.subconsulta2());
    linear_set<Registro> res;
    if (!(res_1.empty() || res_2.empty())) {
        for (Registro r : res_1) {
            for (Registro p : res_2) {
                Registro q;
                for (NombreCampo n : r.campos()) {
                    Valor v = r[n];
                    q.definir(n, v);
                }
                for (NombreCampo m : p.campos()) {
                    if (!r.estaDef(m)) {
                        Valor w = p[m];
                        q.definir(m, w);
                    }
                }
                res.fast_insert(q);
            }
        }
    }
    this->resConsulta = res;
}





