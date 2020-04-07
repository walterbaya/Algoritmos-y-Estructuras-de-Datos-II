#include "../src/Horario.cpp"
#include <iostream>

using namespace std;

bool test_constructor_y_getters() {
  Horario h(5, 30, 22);
  bool res = true;
  res = res and (h.dame_hora() == 5);
  res = res and (h.dame_min() == 30);
  res = res and (h.dame_segs() == 22);
  return res;
}

bool test_eq() {
  Horario h(5, 30, 20);
  bool res = true;
  res = res and (h == Horario(5, 30, 20));
  res = res and not (h == Horario(7, 30, 20));
  res = res and not (h == Horario(5, 31, 20));
  res = res and not (h == Horario(5, 30, 21));
  return res;
}

bool test_less() {
  bool res = true;
  res = res and (Horario(5, 30, 20) < Horario(6, 30, 20));
  res = res and (Horario(5, 30, 20) < Horario(5, 31, 20));
  res = res and (Horario(5, 30, 20) < Horario(5, 30, 21));

  res = res and not (Horario(6, 30, 20) < Horario(5, 30, 20));
  res = res and not (Horario(5, 31, 20) < Horario(5, 30, 20));
  res = res and not (Horario(5, 30, 21) < Horario(5, 30, 20));

  res = res and not (Horario(5, 30, 20) < Horario(5, 30, 20));
  return res;
}

bool test_restar_seg() {
  bool res = true;

  Horario h(0, 0, 15);
  res = res and (h.dame_segs() == 15);

  h.restar_seg();
  res = res and (h.dame_segs() == 14);
  
  h.restar_seg();
  res = res and (h.dame_segs() == 13);

  Horario h1(0, 1, 1);
  h1.restar_seg();
  res = res and (h1 == Horario(0, 1, 0));
  h1.restar_seg();
  res = res and (h1 == Horario(0, 0, 59));
  h1.restar_seg();
  res = res and (h1 == Horario(0, 0, 58));
  
  Horario h2(1, 0, 1);
  h2.restar_seg();
  res = res and (h2 == Horario(1, 0, 0));
  h2.restar_seg();
  res = res and (h2 == Horario(0, 59, 59));
  h2.restar_seg();
  res = res and (h2 == Horario(0, 59, 58));
  return res;
}

int main() {
  bool ok_test_constructor = test_constructor_y_getters();
  bool ok_test_eq = test_eq();
  bool ok_test_less = test_less();
  bool ok_test_restar_seg = test_restar_seg();

  if (not ok_test_constructor) {
    cout << "Falló test_constructor" << endl;
  }
  if (not ok_test_eq) {
    cout << "Falló test_eq" << endl;
  }
  if (not ok_test_less) {
    cout << "Falló test_less" << endl;
  }
  if (not ok_test_restar_seg) {
    cout << "Falló test_restar_seg" << endl;
  }
  
  if (ok_test_constructor and ok_test_eq and ok_test_less and
      ok_test_restar_seg) {
    cout << "OK" << endl;
  }
}
