#ifndef __TIPOS_H__
#define __TIPOS_H__

#include <iostream>
#include <string>

using namespace std;

typedef string NombreTabla;
typedef string NombreCampo;
typedef string Valor;
typedef string Clave;
typedef int Indice;

#define COMPLETAR(X)    { \
    cerr << "ERROR --- El método " #X " está incompleto." << endl; \
    exit(1); \
}

#endif /*__TIPOS_H__*/
