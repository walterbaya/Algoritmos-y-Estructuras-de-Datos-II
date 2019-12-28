#include "gtest-1.8.1/gtest.h"
#include "../src/Registro.h"

TEST(testRegistro, definirVarios){
    Registro r;
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v1", "2");
    r.definir("v3", "3");
    vector<string> res = {"v1", "v2", "v3"};

    EXPECT_TRUE(r.campos() == res);
    EXPECT_TRUE(r["v1"] == "2");
    EXPECT_TRUE(r.obtenerRapido(0) == "2");
    EXPECT_TRUE(r.obtenerRapido(2) == "3");
}

TEST(testRegistro, NingunCampo){
    Registro r;
    EXPECT_TRUE(r.campos().size()==0);
}

TEST(testRegistro, obtenerConOperador){
    Registro r;
    r.definir("c1", "1");
    r.definir("c2", "2");

    string res = r["c1"];
    EXPECT_TRUE(res == "1");
    r["c2"] = "4";
    EXPECT_TRUE(r["c2"] == "4");
}

/*TEST(testRegistro, definirConOperador){
    Registro r;
    r["clave1"] = "valor1";
    EXPECT_TRUE(r["clave1"] == "valor1");
    EXPECT_TRUE(r.campos().size() == 1);
}*/

TEST(testRegistro, eliminarCampo){
    Registro r;
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v3", "3");

    r.eliminarCampo("v2");
    EXPECT_TRUE(r.obtenerRapido(1) == "3");
    vector<NombreCampo> res = {"v1", "v3"};
    EXPECT_TRUE(res == r.campos());
}

TEST(testRegistro, operadorIgual){
    Registro r;
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v3", "3");

    Registro res = r;

    EXPECT_EQ(r.campos(), res.campos());
    EXPECT_EQ(r["v1"], res["v1"]);
    EXPECT_EQ(r.obtenerRapido(0), res.obtenerRapido(0));
    EXPECT_EQ(r.obtenerRapido(2), res.obtenerRapido(2));
}

TEST(testRegistro, operadorIgualIgual){
    Registro r;
    Registro r1;

    EXPECT_TRUE(r == r1);
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v3", "3");


    r1.definir("v1", "1");
    r1.definir("v2", "2");
    r1.definir("v3", "3");

    EXPECT_TRUE(r == r1);

    r1["v1"] = "10";

    EXPECT_FALSE(r1 == r);
}

TEST(testRegistro, renombrar){
    Registro r;
    r.definir("v1", "1");
    r.definir("v2", "2");
    r.definir("v3", "3");
    r.renombrar("v1", "nuevo");

    EXPECT_TRUE(r.obtenerRapido(0) == "1");
    EXPECT_EQ("1", r["nuevo"]);
}