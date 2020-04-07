#include "SistemaDeMensajes.h"

SistemaDeMensajes::SistemaDeMensajes() : _conns{nullptr, nullptr, nullptr, nullptr}{

}

bool SistemaDeMensajes::registrado(int id) const {
    bool res=true;
    if(_conns[id]== nullptr){
        res=false;
    }
    return res;
}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    _conns[id]=new ConexionJugador(ip);  //reservo un espacio en memoria para id
    *_conns[id]=ConexionJugador(ip);
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    _conns[id]->enviarMensaje(mensaje);
}

string SistemaDeMensajes::ipJugador(int id) const {
    _conns[id]->ip();
}

SistemaDeMensajes::~SistemaDeMensajes() {
    delete
}




