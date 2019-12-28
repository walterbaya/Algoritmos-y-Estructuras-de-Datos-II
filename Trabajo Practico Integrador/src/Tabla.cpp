#include "Tabla.h"

Tabla::Tabla(vector<NombreCampo> _campos, NombreCampo _clave) : camposEnOrden(_campos), campoClave(_clave) {
    for(int i = 0; i < _campos.size(); i++){
        this->diccCampoIndice[_campos[i]] = i; //Defino los indices con el orden de entrada.
    }
}

Tabla::Tabla() = default;

void Tabla::insertar(const Registro &r) {
    Valor valorCampoClave = r.obtenerRapido(this->diccCampoIndice.at(campoClave)); //Obtengo el valor de la clave
    if(this->camposEnOrden == r.campos()){
        if(this->diccClaveRegistro.count(valorCampoClave) == 0){ //Me fijo si ya hay un registro con esa clave.
            this->conjRegistros.fast_insert(r); //Si no, lo agrego al conjunto de registro.
        }else{
            for(Registro x : this->conjRegistros){   //Si esta lo tengo que reemplazar por el nuevo registro
                if(x[campoClave] == valorCampoClave){//en el conjunto de registros.
                    x = r;
                }
            }
        }
        this->diccClaveRegistro.insert(make_pair(valorCampoClave, r)); //Defino el registro nuevo(o piso el anterior) en el dicc.
    }
}

void Tabla::borrar(const Valor &valorClave) {
    this->diccClaveRegistro.erase(valorClave);
    for(Registro x : this->conjRegistros){
        if(x[this->campoClave] == valorClave){
            this->conjRegistros.erase(x);
            break;
        }
    }
}

Registro Tabla::obtenerRegistro(const Valor &valorClave) const {
    return this->diccClaveRegistro.at(valorClave);
}

linear_set<Registro> Tabla::tablaCompleta() const{
    linear_set<Registro> res;
    for(Valor x : this->diccClaveRegistro.clavesDef()){
        Registro r = this->obtenerRegistro(x);
        res.fast_insert(r);
    }
    return res;
}

int Tabla::obtenerIndice(const NombreCampo &campo) const {
    return this->diccCampoIndice.at(campo);
}

int Tabla::size() const {
    return this->conjRegistros.size();
}

NombreCampo Tabla::clave() const {
    return this->campoClave;
}

vector<NombreCampo> Tabla::campos() const {
    return this->camposEnOrden;
}
bool Tabla::definido(Valor v) {
    return diccClaveRegistro.count(v);
}

linear_set<Valor> Tabla::clavesDef() const {
    return this->diccClaveRegistro.clavesDef();
}
