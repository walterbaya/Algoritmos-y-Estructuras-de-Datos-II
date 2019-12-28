#include "gtest-1.8.1/gtest.h"
#include "../src/Tabla.h"
#include "../src/Registro.h"

TEST(testTabla, insertarRegistro){
    vector<NombreCampo> camposTabla = {"Nombre", "Apellido", "DNI"};
    Tabla t(camposTabla, "DNI");
    Registro r;
    r.definir("Nombre", "Alan");
    r.definir("Apellido", "Gomez");
    r.definir("DNI","40073758");
    Registro q;
    q.definir("Nombre","Felipe");
    q.definir("Apellido","Lopez");
    q.definir("DNI","40651121");
    Registro s;
    s.definir("Nombre", "Lucia");
    s.definir("Apellido","Diaz");
    s.definir("DNI","31586459");

    t.insertar(r);
    t.insertar(q);
    t.insertar(s);

    linear_set<Registro> resRegs = {r, q, s};

    EXPECT_EQ(resRegs, t.tablaCompleta());
    EXPECT_EQ(3, t.size());
    EXPECT_EQ(r, t.obtenerRegistro("40073758"));
    EXPECT_EQ(0, t.obtenerIndice("Nombre"));
    EXPECT_EQ(camposTabla, t.campos());
    EXPECT_EQ("DNI", t.clave());
}

TEST(testTabla,Insertar_Registro_Invalido){
    Registro p;
    p.definir("Nombre","Alan");
    p.definir("Apellido", "Gomez");
    p.definir("DNI","40073758");
    Registro q;
    q.definir("Nombre","Felipe");
    q.definir("Apellido","Lopez");
    q.definir("DNI","40651121");
    q.definir("Nacionalidad","Argentina");
    Registro s;
    s.definir("Nombre", "Lucia");
    s.definir("Apellido","Diaz");
    s.definir("DNI","31586459");

    vector<NombreCampo> camposT = {"Nombre", "Apellido", "DNI"};
    vector<NombreCampo> camposU = {"Nombre", "Apellido", "DNI", "Nacionalidad"};
    Tabla t(camposT, "DNI");
    Tabla u(camposU, "DNI");
    t.insertar(p);
    t.insertar(q);
    t.insertar(s);
    u.insertar(p);
    u.insertar(q);
    u.insertar(s);

    EXPECT_EQ(2, t.size());
    EXPECT_EQ(1, u.size());
}

TEST(testTabla,Insertar_Y_Borrar_Varios_Registros){
    vector<NombreCampo> camposTabla = {"Producto", "Precio"};
    Tabla t(camposTabla, "Producto");
    Registro o;
    o.definir("Producto","empanada");
    o.definir("Precio","25");
    Registro p;
    p.definir("Producto","milanesa");
    p.definir("Precio","55");
    Registro q;
    q.definir("Producto","hamburguesa");
    q.definir("Precio","100");
    Registro r;
    r.definir("Producto","pancho");
    r.definir("Precio","85");
    t.insertar(o);
    t.insertar(p);
    t.insertar(q);
    t.insertar(r);

    EXPECT_EQ(4, t.size());

    t.borrar("empanada");
    EXPECT_EQ(3, t.size());

    linear_set<Registro> resReg = {p, q, r};
    EXPECT_EQ(resReg, t.tablaCompleta());

    t.borrar("milanesa");
    t.borrar("hamburguesa");
    t.borrar("pancho");
    EXPECT_EQ(0, t.size());
}

TEST(testTabla,definido){
    vector<NombreCampo> camposTabla = {"Nombre", "Apellido", "DNI"};
    Tabla t(camposTabla, "DNI");
    Registro r;
    r.definir("Nombre", "Alan");
    r.definir("Apellido", "Gomez");
    r.definir("DNI","40073758");
    Registro q;
    q.definir("Nombre","Felipe");
    q.definir("Apellido","Lopez");
    q.definir("DNI","40651121");
    Registro s;
    s.definir("Nombre", "Lucia");
    s.definir("Apellido","Diaz");
    s.definir("DNI","31586459");

    t.insertar(r);
    t.insertar(q);
    t.insertar(s);
    
    EXPECT_TRUE(t.definido("40073758"));
    EXPECT_FALSE(t.definido("39749587"));
}

TEST(testTabla, conjRegistros){
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

    linear_set<Registro> esperado = {r, s, q};
    linear_set<Registro> res = t.tablaCompleta();
    EXPECT_EQ(res, esperado);
    for(Registro x : res){
        EXPECT_TRUE(r["1"] == x["1"] || s["1"] == x["1"] || q["1"] == x["1"]);
    }

}