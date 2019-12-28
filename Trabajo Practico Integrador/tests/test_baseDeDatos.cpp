#include "gtest-1.8.1/gtest.h"
#include "../src/BaseDeDatos.h"
#include "../src/Tabla.h"
#include "../src/Registro.h"
#include "../src/Consulta.h"
#include <fstream>


TEST(testBaseDeDatos, AgregarTabla) {

}

TEST(testBaseDeDatos, resolverFrom) {
    Registro r;
    Registro q;
    BaseDeDatos b;
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v1", "2");
    r.definir("v3", "3");
    vector<NombreCampo> reg = {"v1", "v2", "v3"};
    Tabla t(reg, "v1");
    t.insertar(r);
    b.agregarTabla("valores", t);
    Consulta c1("from(valores)");
    linear_set<Registro> res = b.resolver(c1);
    EXPECT_TRUE(res.size() == 1);

    //DOS TABLAS
    q.definir("v1", "9");
    q.definir("v2", "8");
    q.definir("v1", "7");
    q.definir("v3", "6");
    t.insertar(q);
    b.agregarTabla("otra", t);
    Consulta c2("from(otra)");
    linear_set<Registro> res2 = b.resolver(c2);
    EXPECT_TRUE(res2.size() == 2);
}


TEST(testBaseDeDatos, test_interseccion_simple_1_registro) {
    Registro p;
    p.definir("Nombre", "Pedro");
    p.definir("Apellido", "Gimenez");
    p.definir("DNI", "16533289");
    Registro q;
    q.definir("Nombre", "Mona");
    q.definir("Apellido", "Simons");
    q.definir("DNI", "47896132");
    Registro r;
    r.definir("Nombre", "Lisa");
    r.definir("Apellido", "Simpson");
    r.definir("DNI", "47896132");
    Tabla t({"Nombre", "Apellido", "DNI"}, "DNI");
    Tabla v({"Nombre", "Apellido", "DNI"}, "DNI");
    BaseDeDatos b;
    b.agregarTabla("Empleados", t);
    b.agregarTabla("Clientes", v);
    b.registrar("Empleados", p);
    b.registrar("Clientes", p);
    Consulta c("inter(from(Empleados),from(Clientes))");

    linear_set<Registro> res = b.resolver(c);
    ASSERT_EQ(res.size(), 1);

    linear_set<Registro> esperado = {p};
    ASSERT_EQ(res, esperado);
}

TEST(testBaseDeDatos, test_interseccion_simple) {
    Registro p;
    p.definir("Nombre", "Pedro");
    p.definir("Apellido", "Gimenez");
    p.definir("DNI", "16533289");
    Registro q;
    q.definir("Nombre", "Mona");
    q.definir("Apellido", "Simons");
    q.definir("DNI", "47896132");
    Registro r;
    r.definir("Nombre", "Lisa");
    r.definir("Apellido", "Simpson");
    r.definir("DNI", "47896342");
    Tabla t({"Nombre", "Apellido", "DNI"}, "DNI");
    Tabla v({"Nombre", "Apellido", "DNI"}, "DNI");
    BaseDeDatos b;
    b.agregarTabla("Empleados", t);
    b.agregarTabla("Clientes", v);
    b.registrar("Empleados", p);
    b.registrar("Empleados", q);
    b.registrar("Empleados", r);
    b.registrar("Clientes", p);
    b.registrar("Clientes", r);
    Consulta c("inter(from(Empleados),from(Clientes))");

    linear_set<Registro> res = b.resolver(c);
    ASSERT_EQ(res.size(),2);

    linear_set<Registro> esperado = {p, r};
    ASSERT_EQ(res, esperado);
}


TEST(testBaseDeDatos, testMatch) {
    Registro p;
    p.definir("Nombre", "Pedro");
    p.definir("Apellido", "Pedro");
    p.definir("DNI", "16533289");
    Registro q;
    q.definir("Nombre", "Mona");
    q.definir("Apellido", "Mona");
    q.definir("DNI", "47896132");
    Registro r;
    r.definir("Nombre", "Lisa");
    r.definir("Apellido", "Simpson");
    r.definir("DNI", "43846432");
    Tabla t({"Nombre", "Apellido", "DNI"}, "DNI");
    Tabla v({"Nombre", "Apellido", "DNI"}, "DNI");
    BaseDeDatos b;
    b.agregarTabla("Empleados", t);
    b.agregarTabla("Clientes", v);
    b.registrar("Empleados", p);
    b.registrar("Empleados", q);
    b.registrar("Empleados", r);
    b.registrar("Clientes", p);
    b.registrar("Clientes", r);
    Consulta c("match(from(Empleados),Nombre,Apellido)");
    linear_set<Registro> res = b.resolver(c);
    ASSERT_EQ(res.size(), 2);
}

TEST(testBaseDeDatos, select_con_clave){
    Registro r;
    r.definir("1", "r1");
    r.definir("2", "r2");
    r.definir("3", "r3");
    Registro s;
    s.definir("1", "s1");
    s.definir("2", "s2");
    s.definir("3", "s3");

    Tabla t({"1", "2", "3"}, "1");
    t.insertar(r);
    t.insertar(s);
    BaseDeDatos b;
    b.agregarTabla("a", t);

    Consulta cons("select(from(a), 1, 'r1')");

    linear_set<Registro> res = b.resolver(cons);
    linear_set<Registro> esperado = {r};
    EXPECT_EQ(res, esperado);
}

TEST(testBaseDeDatos, select_sin_clave){
    Registro r;
    r.definir("1", "r1");
    r.definir("2", "i1");
    r.definir("3", "r3");
    Registro s;
    s.definir("1", "s1");
    s.definir("2", "i1");
    s.definir("3", "s3");
    Registro q;
    q.definir("1", "q1");
    q.definir("2", "q2");
    q.definir("3", "q3");

    Tabla t({"1", "2", "3"}, "1");
    t.insertar(r);
    t.insertar(s);
    t.insertar(q);
    BaseDeDatos b;
    b.agregarTabla("a", t);

    Consulta cons("select(from(a), 2, 'i1')");
    linear_set<Registro> res = b.resolver(cons);
    linear_set<Registro> esperado = {r, s};

    EXPECT_EQ(res, esperado);
}

TEST(testBaseDeDatos, seleccion_comun){
    Registro r;
    r.definir("1", "r1");
    r.definir("2", "i1");
    r.definir("3", "r3");
    Registro s;
    s.definir("1", "s1");
    s.definir("2", "i1");
    s.definir("3", "s3");
    Registro q;
    q.definir("1", "q1");
    q.definir("2", "i1");

    Tabla t({"1", "2", "3"}, "1");
    t.insertar(r);
    t.insertar(s);
    t.insertar(q);
    BaseDeDatos b;
    b.agregarTabla("a", t);

    //Consulta subCons1("select(from(a), 2, 'i1')");
    Consulta cons("select(select(from(a), 2, 'i1'), 3, 'r3')");

    linear_set<Registro> res = b.resolver(cons);
    linear_set<Registro> esperado = {r};

    EXPECT_EQ(res, esperado);
}

TEST(testBaseDeDatos, select_con_clave_de_select_sin_clave){
    Registro r;
    r.definir("1", "r1");
    r.definir("2", "i1");
    r.definir("3", "r3");
    Registro s;
    s.definir("1", "s1");
    s.definir("2", "i1");
    s.definir("3", "s3");
    Registro q;
    q.definir("1", "q1");
    q.definir("2", "i1");
    q.definir("3", "q3");

    Tabla t({"1", "2", "3"}, "1");
    t.insertar(r);
    t.insertar(s);
    t.insertar(q);
    BaseDeDatos b;
    b.agregarTabla("a", t);

    Consulta cons("select(select(from(a), 2, 'i1'), 1, 'q1')");

    linear_set<Registro> res = b.resolver(cons);
    linear_set<Registro> esperado = {q};

    EXPECT_EQ(res, esperado);
}

TEST(testBaseDeDatos, combinar) {
    BaseDeDatos bd;
    Tabla t1 = Tabla({"c1", "c2", "c3","k1", "k2", "k3"}, "c1");
    Registro r1;
    Registro r2;
    Registro r3;
    Registro r4;
    r1.definir("c1", "A");
    r1.definir("c2", "B");
    r1.definir("c3", "C");

    r2.definir("k1", "1");
    r2.definir("k2", "2");
    r2.definir("k3", "A");

    r3 = bd.combinar(r1,r2);

    r4.definir("c1", "A");
    r4.definir("c2", "B");
    r4.definir("c3", "C");
    r4.definir("k1", "1");
    r4.definir("k2", "2");
    r4.definir("k3", "A");

    t1.insertar(r4);

    EXPECT_EQ(r3,r4);
}



TEST(testBaseDeDatos, JoinConClaves) {
    BaseDeDatos bd;
    Tabla t1 = Tabla({"c1", "c2", "c3"}, "c1");
    Tabla t2 = Tabla({"k1", "k2", "k3"}, "k3");
    Registro r1;
    Registro r2;
    Registro r3;

    r1.definir("c1", "A");
    r1.definir("c2", "B");
    r1.definir("c3", "C");

    r2.definir("k1", "1");
    r2.definir("k2", "2");
    r2.definir("k3", "A");

    r3.definir("k1", "4");
    r3.definir("k2", "5");
    r3.definir("k3", "D");

    t1.insertar(r1);
    t2.insertar(r2);
    t2.insertar(r3);

    linear_set<Registro> res;
    Registro result;
    result.definir("c1", "A");
    result.definir("c2", "B");
    result.definir("c3", "C");
    result.definir("k1", "1");
    result.definir("k2", "2");
    result.definir("k3", "A");

    bd.agregarTabla("t1", t1);
    bd.agregarTabla("t2", t2);

    res.fast_insert(result);

    Consulta c("match(product(from(t1),from(t2)),c1,k3)");

    linear_set<Registro> res1 = bd.resolver(c);

    EXPECT_TRUE(res==(res1));

}


TEST(testBaseDeDatos, Interseccion_Dos_Selecciones){
    BaseDeDatos bd;
    Tabla t = Tabla({"c1", "c2"}, "c1");
    Registro r1;
    Registro r2;
    Registro r3;

    r1.definir("c1", "A1");
    r1.definir("c2", "B1");

    r2.definir("c1", "A2");
    r2.definir("c2", "B1");

    r3.definir("c1", "A3");
    r3.definir("c2", "B5");

    t.insertar(r1);
    t.insertar(r2);
    t.insertar(r3);

    linear_set<Registro> res;
    Registro res1;
    Registro res2;
    res1.definir("c1", "A1");
    res1.definir("c2", "B1");
    res2.definir("c1", "A2");
    res2.definir("c2", "B1");

    bd.agregarTabla("t", t);

    res.fast_insert(res1);
    res.fast_insert(res2);

    Consulta c("inter(select(from(t),c2,'B1'), select(from(t),c2,'B1'))");
    linear_set<Registro> resultado = bd.resolver(c);

    EXPECT_EQ(resultado, res);
}


TEST(testBaseDeDatos, Producto_simple) {
    Registro r;
    r.definir("Comida", "Milanesa");
    r.definir("Precio", "$83");
    Registro q;
    q.definir("Comida", "Hamburguesa");
    q.definir("Precio", "$120");
    Registro x;
    x.definir("Guarnicion", "Pure");
    x.definir("Precio+", "$45");
    Registro y;
    y.definir("Guarnicion", "Papas fritas");
    y.definir("Precio+", "$55");
    Registro z;
    z.definir("Guarnicion", "Ensalada");
    z.definir("Precio+", "$40");
    Tabla t({"Comida", "Precio"}, "Comida");
    Tabla u({"Guarnicion", "Precio+"}, "Guarnicion");
    BaseDeDatos b;
    b.agregarTabla("Menu", t);
    b.registrar("Menu", r);
    b.registrar("Menu", q);
    b.agregarTabla("Guarnicion", u);
    b.registrar("Guarnicion", x);
    b.registrar("Guarnicion", y);
    b.registrar("Guarnicion", z);
    Consulta C("product(from(Menu),from(Guarnicion))");
}

