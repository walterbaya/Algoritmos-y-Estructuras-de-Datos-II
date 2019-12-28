#include "Registro.h"

Registro::Registro() = default;

void Registro::definir(const NombreCampo& campo, const Valor& valor) {
    int indice = this->indiceCampo(campo);
    this->campoValor.insert(make_pair(campo, valor));
    if(indice == -1){                          //Si no esta definido, los agrego al final.
        this->ordenCampos.push_back(campo);
        this->datos.push_back(valor);
    }else {
        this->datos[indice] = valor;
    }
}

void Registro::eliminarCampo(const NombreCampo &campo) {
    this->campoValor.erase(campo);
    int indice = this->indiceCampo(campo);
    this->ordenCampos.erase(this->ordenCampos.begin() + indice);
    this->datos.erase(this->datos.begin() + indice);
}

vector<NombreCampo> Registro::campos() const{
    return this->ordenCampos;
}

Registro &Registro::operator=(const Registro &r) {
    if(&r != this) {
        this->campoValor = string_map<string>();
        this->datos = vector<Valor>();
        this->ordenCampos = vector<NombreCampo>();
        for (int i = 0; i < r.campos().size(); i++) {
            this->definir(r.campos()[i], r.obtenerRapido(i));
        }
    }
    return *this;
}

bool Registro::operator==(const Registro &r) const{
    bool res=true;
    for (NombreCampo nc : r.campos()) {
        res = this->campoValor.at(nc) == r.campoValor.at(nc);
        if(!res){
            return false;
        }
    }
    return res;
}

Valor& Registro::operator[](const NombreCampo& campo) {
    return this->campoValor.at(campo);
}

Registro &Registro::renombrar(const NombreCampo &nc1, const NombreCampo &nc2) {
    int indiceNc1 = this->indiceCampo(nc1);
    this->campoValor.erase(nc1); //Elimino la clave del diccionario
    this->ordenCampos[indiceNc1] = nc2; //Pongo la clave nueva en el lugar de la anterior
    this->campoValor.insert(make_pair(nc2, this->datos[indiceNc1]));
    return *this;
}

Valor const &Registro::obtenerRapido(int i) const {
    return this->datos[i] ;
}
/**
 * La cantidad de campos es acotada! A lo sumo repito el ciclo c constante veces.
 * La comparacion es |c|.
 */
int Registro::indiceCampo(const NombreCampo &campo) const {
    for(int i = 0; i < this->ordenCampos.size(); i++){ //Para cada uno de los campos
        if(campo == this->ordenCampos[i]){ //Si es igual, lo encontre. Entonces devuelvo el indice.
            return i;
        }
    }
    return -1; //Si no lo encuentro.
}

bool Registro::estaDef(const NombreCampo &campo) const{
    return this->campoValor.count(campo) == 1;
}
