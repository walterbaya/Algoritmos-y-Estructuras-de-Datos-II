//////////////
// PRELUDIO //
//////////////

// Typedef
typedef int Anio;
typedef int Mes;
typedef int Dia;

// MESES
const Mes ENERO = 1;
const Mes FEBRERO = 2;
const Mes MARZO = 3;
const Mes ABRIL = 4;
const Mes MAYO = 5;
const Mes JUNIO = 6;
const Mes JULIO = 7;
const Mes AGOSTO = 8;
const Mes SEPTIEMBRE = 9;
const Mes OCTUBRE = 10;
const Mes NOVIEMBRE = 11;
const Mes DICIEMBRE = 12;

// Ejercicio 1: esBisiesto
bool esBisiesto(Anio anio) {
}

// Ejercicio 2: diasEnMes
//
//

// Para ejercicio 6
class Periodo;

class Fecha {
 public:
  // pre: anio > 0, mes \in [1, 12], dia \in [1, diasEnMes(anio, mes)]
  Fecha(Anio anio, Mes mes, Dia dia);

  Anio anio() const;
  Mes mes() const;
  Dia dia() const;

  bool operator==(Fecha o) const;
  bool operator<(Fecha o) const;

  // Ejercicio 7: sumar período a fecha

 private:
  Anio _anio;
  Mes _mes; 
  Dia _dia;

  // Ejercicio 7: sumar a fecha
  void sumar_anios(int anios);
  void sumar_meses(int meses);
  void sumar_dias(int dias);
};

// Ejercicio 3: Constructor y métodos de Fecha
Fecha::Fecha(Anio anio, Mes mes, Dia dia) {
}

Anio Fecha::anio() const {
}

// Fecha::mes()

// dia


// Ejercicio 4: comparadores
bool Fecha::operator==(Fecha o) const {
}

// Fecha::operator<


// Ejercicio 5: comparador distinto
bool operator!=(Fecha f1, Fecha f2) {
}

// Ejercicio 6: clase período
class Periodo {
};


// Ejercicio 8: clase Intervalo
