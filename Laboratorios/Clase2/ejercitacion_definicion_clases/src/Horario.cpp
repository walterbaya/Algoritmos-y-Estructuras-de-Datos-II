class Horario {
public:
    //pre: hora \in [0; 23], min \in [0; 59], segs \in [0; 59]
    Horario(int hora, int min, int segs);

    int dame_hora() const;
    int dame_min() const ;
    int dame_segs() const;

    void restar_seg();

    bool operator<(Horario o) const;
    bool operator==(Horario o) const;

private:
    int _hora, _min, _segs;

};

Horario::Horario(int h, int m, int s) : _hora(h), _min(m), _segs(s) {
}

int Horario::dame_hora() const{
  return _hora;
}

int Horario::dame_min() const {
  return _min;
}

int Horario::dame_segs() const {
  return _segs;
}

void Horario::restar_seg() {
  if (_segs > 0) {
    _segs--;
  } else if (_segs == 0 and (_min > 0 or _hora > 0)) {
    _segs = 59;
    if (_min == 0 and _hora > 0) {
      _min = 59;
      _hora--;
    } else {
      _min--;
    }
  }
}

bool Horario::operator<(Horario o) const {
  return (_hora < o._hora or
          (_hora == o._hora and _min < o._min) or
          (_hora == o._hora and _min == o._min and _segs < o._segs));
}

bool Horario::operator==(Horario o) const {
  return (_hora == o._hora and _min == o._min and _segs == o._segs);
}

Horario operator-(Horario h1, Horario h2) {
  if (not (h1 < h2)) {
    return h2 - h1;
  }
  int d_horas = h2.dame_hora() - h1.dame_hora();
  int d_min = h2.dame_min() - h1.dame_min();
  if (d_min < 0) {
    d_horas--;
    d_min = 60 + d_min;
  }
  int d_segs = h2.dame_segs() - h1.dame_segs();
  if (d_segs < 0) {
    if (d_min > 0) {
      d_min--;
    } else {
      d_horas--;
      d_min = 59;
    }
    d_segs = 60 + d_segs;
  }
  return Horario(d_horas, d_min, d_segs);
}
