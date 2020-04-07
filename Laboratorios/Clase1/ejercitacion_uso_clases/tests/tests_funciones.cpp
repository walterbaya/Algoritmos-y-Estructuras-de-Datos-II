#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "funciones.cpp"

#include <set>

set<int> v2s(vector<int> v) {
  set<int> ret;
  for (int x : v) {
    ret.insert(x);
  }
  return ret;
}

void test_ej1(vector<int> (*qr)(vector<int>)) {
  REQUIRE(v2s((*qr)(vector<int>{})) == set<int>{});
  REQUIRE(v2s((*qr)(vector<int>{1, 1, 1, 1, 1})) == set<int>{1});
  REQUIRE(v2s((*qr)(vector<int>{1, 1, 2, 2, 3, 3})) == set<int>{1, 2, 3});
  REQUIRE(v2s((*qr)(vector<int>{1, 1, 2, 3, 3})) == set<int>{1, 2, 3});
}

void test_ej3(bool (*me)(vector<int>, vector<int>)) {
  REQUIRE((*me)(vector<int>{}, vector<int>{}));
  REQUIRE((*me)(vector<int>{1, 1, 1}, vector<int>{1}));
  REQUIRE((*me)(vector<int>{1, 2, 3}, vector<int>{1, 2, 3}));
  REQUIRE((*me)(vector<int>{3, 2, 1}, vector<int>{1, 2, 3}));
  REQUIRE(!(*me)(vector<int>{4, 3, 2, 1}, vector<int>{1, 2, 3}));
  REQUIRE((*me)(vector<int>{3, 3, 2, 1}, vector<int>{1, 2, 3}));
  REQUIRE(!(*me)(vector<int>{3, 3, 2, 1}, vector<int>{1, 3}));
}

TEST_CASE("EJ 01") { test_ej1(quitar_repetidos); }

TEST_CASE("EJ 02") { test_ej1(quitar_repetidos_v2); }

TEST_CASE("Ej 03") { test_ej3(mismos_elementos); }

TEST_CASE("Ej 04") { test_ej3(mismos_elementos_v2); }

TEST_CASE("Ej 05") {
  REQUIRE(contar_apariciones(vector<int>{}) == map<int, int>{});
  REQUIRE(contar_apariciones(vector<int>{1, 2, 3}) ==
          map<int, int>{{1, 1}, {2, 1}, {3, 1}});
  REQUIRE(contar_apariciones(vector<int>{1, 2, 3, 1}) ==
          map<int, int>{{1, 2}, {2, 1}, {3, 1}});
  REQUIRE(contar_apariciones(vector<int>{1, 1}) == map<int, int>{{1, 2}});
}

TEST_CASE("Ej 06") {
  REQUIRE(v2s(filtrar_repetidos(vector<int>{})) == set<int>());
  REQUIRE(v2s(filtrar_repetidos(vector<int>{1, 1})) == set<int>());
  REQUIRE(v2s(filtrar_repetidos(vector<int>{1, 1, 2})) == set<int>{2});
  REQUIRE(v2s(filtrar_repetidos(vector<int>{1, 2})) == set<int>{2, 1});
}

TEST_CASE("Ej 07") {
  REQUIRE(interseccion(set<int>(), set<int>()) == set<int>());
  REQUIRE(interseccion(set<int>{1, 2, 3}, set<int>()) == set<int>());
  REQUIRE(interseccion(set<int>{1, 2, 3}, set<int>{4}) == set<int>());
  REQUIRE(interseccion(set<int>{1, 2, 3}, set<int>{2, 4}) == set<int>{2});
  REQUIRE(interseccion(set<int>{1, 2, 3}, set<int>{2, 1, 4}) == set<int>{1, 2});
}

TEST_CASE("Ej 08") {
  REQUIRE(agrupar_por_unidades(vector<int>{}) == map<int, set<int>>{});
  REQUIRE(
      agrupar_por_unidades(vector<int>{1, 2, 3}) ==
      map<int, set<int>>{{1, set<int>{1}}, {2, set<int>{2}}, {3, set<int>{3}}});
  REQUIRE(
      agrupar_por_unidades(vector<int>{1, 2, 3, 1}) ==
      map<int, set<int>>{{1, set<int>{1}}, {2, set<int>{2}}, {3, set<int>{3}}});
  REQUIRE(agrupar_por_unidades(vector<int>{1, 2, 3, 1, 12}) ==
          map<int, set<int>>{
              {1, set<int>{1}}, {2, set<int>{2, 12}}, {3, set<int>{3}}});
  REQUIRE(agrupar_por_unidades(vector<int>{1, 2, 3, 1, 12, 20}) ==
          map<int, set<int>>{{1, set<int>{1}},
                             {2, set<int>{2, 12}},
                             {0, set<int>{20}},
                             {3, set<int>{3}}});
  REQUIRE(agrupar_por_unidades(vector<int>{1, 2, 3, 1, 12, 20, 1101}) ==
          map<int, set<int>>{{1, set<int>{1, 1101}},
                             {2, set<int>{2, 12}},
                             {0, set<int>{20}},
                             {3, set<int>{3}}});
}

vector<char> s2v(string str) {
  vector<char> v;
  for (char c : str) {
    v.push_back(c);
  }
  return v;
}

string v2s(vector<char> v) {
  stringstream ss;
  for (char c : v) {
    ss << c;
  }
  return ss.str();
}

TEST_CASE("Ej 09") {
  REQUIRE(traducir(vector<pair<char, char>>{}, s2v("Hola")) == s2v("Hola"));
  REQUIRE(traducir(vector<pair<char, char>>{{'H', 'h'}}, s2v("Hola")) ==
          s2v("hola"));
  REQUIRE(traducir(
              vector<pair<char, char>>{
                  {'H', 'h'},
                  {'x', 'h'},
              },
              s2v("Hola")) == s2v("hola"));
  REQUIRE(traducir(
              vector<pair<char, char>>{
                  {'H', 'h'},
                  {'x', 'h'},
                  {'o', 'h'},
                  {'h', 'A'},
              },
              s2v("Hola")) == s2v("hhla"));
}

Mail mfs(string asunto) { return Mail(asunto, 0, false); }

TEST_CASE("Ej 10") {
  REQUIRE(!integrantes_repetidos(vector<Mail>{mfs("123/45"), mfs("111/11")}));
  REQUIRE(!integrantes_repetidos(
      vector<Mail>{mfs("123/45;222/11"), mfs("111/11")}));
  REQUIRE(!integrantes_repetidos(
      vector<Mail>{mfs("123/45;222/11"), mfs("111/11;222/22")}));
  REQUIRE(!integrantes_repetidos(vector<Mail>{
      mfs("123/45;222/11"), mfs("111/11;222/22"), mfs("123/45;222/11")}));
  REQUIRE(!integrantes_repetidos(
      vector<Mail>{mfs("123/45;222/11"), mfs("111/11;222/22"),
                   mfs("111/11;222/22"), mfs("123/45;222/11")}));
  REQUIRE(
      integrantes_repetidos(vector<Mail>{mfs("123/45"), mfs("123/45;222/22")}));
  REQUIRE(integrantes_repetidos(
      vector<Mail>{mfs("111/45;222/22"), mfs("123/45;222/22")}));
}

using dict_entrega = map<set<LU>, Mail>;

set<LU> pg(string s) { return mfs(s).libretas(); }

TEST_CASE("Ej 11") {
  Mail e11 = Mail("123/45", 10, true);
  REQUIRE(entregas_finales(vector<Mail>{e11}) ==
          dict_entrega{{pg("123/45"), e11}});
  
  Mail e12 = Mail("123/45", 20, true);
  REQUIRE(entregas_finales(vector<Mail>{e11, e12}) ==
          dict_entrega{{pg("123/45"), e12}});
  
  Mail e13 = Mail("123/45", 25, false);
  REQUIRE(entregas_finales(vector<Mail>{e11, e12, e13}) ==
          dict_entrega{{pg("123/45"), e12}});
  
  Mail e14 = Mail("123/45", 15, false);
  REQUIRE(entregas_finales(vector<Mail>{e11, e12, e13, e14}) ==
          dict_entrega{{pg("123/45"), e12}});
  
  Mail e21 = Mail("007/11", 15, true);
  REQUIRE(entregas_finales(vector<Mail>{e21, e11, e12, e13, e14}) ==
          dict_entrega{{pg("123/45"), e12},
                       {pg("007/11"), e21}});
  
  Mail e22 = Mail("007/11", 25, true);
  REQUIRE(entregas_finales(vector<Mail>{e21, e22, e11, e12, e13, e14}) ==
          dict_entrega{{pg("123/45"), e12},
                       {pg("007/11"), e22}});
  
  Mail e23 = Mail("007/11", 35, false);
  REQUIRE(entregas_finales(vector<Mail>{e21, e22, e23, e11, e12, e13, e14}) ==
          dict_entrega{{pg("123/45"), e12},
                       {pg("007/11"), e22}});
}
