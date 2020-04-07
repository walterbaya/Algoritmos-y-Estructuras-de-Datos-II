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

bool esBisiesto(Anio anio) {
  bool p = anio % 4 == 0;
  bool q = anio % 100 == 0;
  bool r = anio % 400 == 0;
  return p and ((not q) or r);
}

int diasEnMes(int anio, int mes) {
  if (mes == FEBRERO) {
    if (esBisiesto(anio)) {
      return 29;
    } else {
      return 28;
    }
  }
  // No es febrero
  if (mes < AGOSTO) {
    if (mes % 2 == ENERO % 2) {
      return 31;
    } else {
      return 30;
    }
  } else {
    if (mes % 2 == AGOSTO % 2) {
      return 31;
    } else {
      return 30;
    }
  }
}

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

  void sumar_periodo(Periodo p);

 private:
  Anio _anio;
  Mes _mes; 
  Dia _dia;

  void ajustar_fecha();
  void sumar_anios(Anio anios);
  void sumar_meses(Mes meses);
  void sumar_dias(Dia dias);
};

Fecha::Fecha(Anio anio, Mes mes, Dia dia) {
  _anio = anio;
  _mes = mes;
  _dia = dia;
}

Anio Fecha::anio() const {
  return _anio;
}

Mes Fecha::mes() const {
  return _mes;
}

Dia Fecha::dia() const {
  return _dia;
}

bool Fecha::operator==(Fecha o) const {
  return (_anio == o.anio() and _mes == o.mes() and _dia == o.dia());
}

bool Fecha::operator<(Fecha o) const {
  return (_anio < o.anio() or
          (_anio == o.anio() and _mes < o.mes()) or
          (_anio == o.anio() and _mes == o.mes() and _dia < o.dia()));
}

bool operator!=(Fecha f1, Fecha f2) {
  return not (f1 == f2);
}

class Periodo {
 public:
  Periodo(int anios, int meses, int dias);

  int anios() const;
  int meses() const;
  int dias() const;

 private:
  int _anios;
  int _meses;
  int _dias;
};

Periodo::Periodo(int anios, int meses, int dias) : _anios(anios), 
    _meses(meses), _dias(dias) {};

int Periodo::anios() const {
  return _anios;
}

int Periodo::meses() const {
  return _meses;
}

int Periodo::dias() const {
  return _dias;
}

void Fecha::ajustar_fecha() {
  while (_mes > 12 || _dia > diasEnMes(_anio, _mes)) {
    if (_mes > 12) {
      _mes -= 12;
      _anio += 1;
    } else {
      _dia -= diasEnMes(_anio, _mes);
      _mes += 1;
    }
  }
}

void Fecha::sumar_anios(int anios) {
  _anio += anios;
  ajustar_fecha();
}

void Fecha::sumar_meses(int meses) {
  _mes += meses;
  ajustar_fecha();
}

void Fecha::sumar_dias(int dias) {
  _dia += dias;
  ajustar_fecha();
}

void Fecha::sumar_periodo(Periodo p) {
  sumar_anios(p.anios());
  sumar_meses(p.meses());
  sumar_dias(p.dias());
}

class Intervalo {
 public:
  // pre: desde < hasta
  Intervalo(Fecha desde, Fecha hasta);

  Fecha desde() const;
  Fecha hasta() const;

  int enDias() const;

 private:
  Fecha _desde;
  Fecha _hasta;
};

Intervalo::Intervalo(Fecha desde, Fecha hasta) : _desde(desde), _hasta(hasta) {};

Fecha Intervalo::desde() const {
  return _desde;
}

Fecha Intervalo::hasta() const {
  return _hasta;
}

int Intervalo::enDias() const {
  Fecha actual = _desde;
  int dias = 0;
  while (actual != _hasta) {
    dias++;
    actual.sumar_periodo(Periodo(0, 0, 1));
  }
  return dias;
}
