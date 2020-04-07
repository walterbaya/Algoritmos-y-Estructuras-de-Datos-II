#include <iostream>
#include <fstream>
#include "gtest-1.8.1/gtest.h"

#include "../src/DiccHash.h"

using namespace std;

TEST(DiccHash, vacio) {
    DiccHash<int> dicc;
    ASSERT_EQ( dicc.cantClaves(), 0);
}

TEST(DiccHash, definido) {
    DiccHash<int> dicc;

    ASSERT_FALSE(dicc.definido(""));
    ASSERT_FALSE(dicc.definido(" ") );
    ASSERT_FALSE(dicc.definido("hola") );

    dicc.definir("hola", 100);
    ASSERT_TRUE(dicc.definido("hola") );
    ASSERT_FALSE(dicc.definido("holas") );
    ASSERT_FALSE(dicc.definido("hol") );
    ASSERT_EQ( dicc.cantClaves(), 1);
}

TEST(DiccHash, definir) {
    DiccHash<char> dicc;
    ASSERT_FALSE(dicc.definido(""));

    dicc.definir("a",'a');
    dicc.definir("ab",'a');

    ASSERT_FALSE(dicc.definido(""));
    ASSERT_TRUE(dicc.definido("a"));
    ASSERT_TRUE(dicc.definido("ab"));
    ASSERT_FALSE(dicc.definido("abc"));
    ASSERT_FALSE(dicc.definido("ab "));
    ASSERT_FALSE(dicc.definido(" ab"));
    ASSERT_EQ( dicc.cantClaves(), 2);
}

TEST(DiccHash, string_vacio) {
    DiccHash<char> dicc;
    ASSERT_FALSE(dicc.definido(""));

    dicc.definir("",'a');
    ASSERT_TRUE(dicc.definido(""));
    ASSERT_FALSE(dicc.definido(" "));

    ASSERT_TRUE(dicc.significado("") == 'a');

    dicc.borrar("");
    ASSERT_FALSE(dicc.definido(""));
}

TEST(DiccHash, significado) {
    DiccHash<char> dicc;
    ASSERT_FALSE(dicc.definido("a"));

    dicc.definir("a",'a');
    dicc.definir("ab",'a');

    ASSERT_TRUE( dicc.significado("a") == 'a');
    ASSERT_TRUE( dicc.significado("a") != 'b');
}

TEST(DiccHash, borrar) {
    DiccHash<int> dicc;

    dicc.definir("juanca",40);
    dicc.definir("moncho",38);

    ASSERT_TRUE( dicc.definido("juanca") );
    ASSERT_TRUE( dicc.definido("moncho")  );

    dicc.borrar("juanca");
    ASSERT_FALSE(dicc.definido("juanca") );
    dicc.borrar("moncho");
    ASSERT_FALSE(dicc.definido("moncho") );
}

TEST(DiccHash, cantClaves) {
    DiccHash<int> dhi;
    ASSERT_EQ( dhi.cantClaves(), 0);

    dhi.definir("juanca",40);
    dhi.definir("moncho",38);
    ASSERT_EQ( dhi.cantClaves(), 2 );

    dhi.definir("moncho",56);
    ASSERT_EQ( dhi.cantClaves(), 2);

    dhi.borrar("juanca");
    ASSERT_EQ( dhi.cantClaves(), 1);

    dhi.borrar("moncho");
    ASSERT_EQ( dhi.cantClaves(), 0);
}

TEST(DiccHash, claves) {
    DiccHash<int> dhi;
    set<string> claves;

    claves = dhi.claves();
    ASSERT_EQ( dhi.cantClaves(), 0);

    dhi.definir("juanca",40);
    dhi.definir("moncho",38);

    claves = dhi.claves();
    ASSERT_EQ( dhi.cantClaves(), 2);

    set<string> conj_claves = {"juanca","moncho"};
    ASSERT_EQ( dhi.claves(), conj_claves);

    set<string> conj_claves2 = {"juanca","moncho",""};
    ASSERT_NE( dhi.claves(), conj_claves2);

    set<string> conj_claves3 = {"juanca"};
    ASSERT_NE( dhi.claves(), conj_claves3);

    set<string> conj_claves4 = {"moncho"};
    dhi.borrar("juanca");
    claves = dhi.claves();
    ASSERT_EQ( dhi.cantClaves(), 1);
    ASSERT_EQ( dhi.claves(), conj_claves4);
    ASSERT_NE( dhi.claves(), conj_claves3);

    dhi.borrar("moncho");
    claves = dhi.claves();
    ASSERT_EQ( dhi.cantClaves(), 0);
    ASSERT_NE( dhi.claves(), conj_claves4);
    ASSERT_NE( dhi.claves(), conj_claves3);
}

TEST(DiccHash, colisiones_uniforme) {
    // Lee los datos del archivo y los define en el diccionario.
    DiccHash<int> dh;

    char delim = '\n';
    std::string archnom = "data/uniforme.txt";

    int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT_TRUE(archin.good());

    while(getline(archin,str,delim) && archin.good()) {
        dh.definir(str, val);
        val++;

        if (val == 50)
            break;
    }
    archin.close();

    ASSERT_EQ(dh.cantClaves(),val);

    // Si no pasa este chequeo significa que tienen muchas colisiones,
    // por lo cual deberían reformular la función de hash.
    ASSERT_TRUE(dh.colisiones() < 20);
}

TEST(DiccHash, colisiones_gaussiana) {
    // Lee los datos del archivo y los define en el diccionario.
    DiccHash<int> dh;

    char delim = '\n';
    std::string archnom = "data/gauss.txt";

    int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT_TRUE(archin.good());

    while(getline(archin,str,delim) && archin.good()) {
        dh.definir(str, val);
        val++;

        if (val == 50)
            break;
    }
    archin.close();


    ASSERT_EQ(dh.cantClaves(),val);

    // Si no pasa este chequeo significa que tienen muchas colisiones,
    // por lo cual deberían reformular la función de hash.
    ASSERT_TRUE(dh.colisiones() < 30);
}

TEST(DiccHash, colisiones_libretas) {
    // Lee las datos del archivo y los define en el diccionario.
    DiccHash<int> dh;

    char delim = '\n';
    std::string archnom = "data/libretas.txt";

    int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT_TRUE(archin.good());

    while(getline(archin,str,delim) && archin.good()) {
        dh.definir(str, val);
        val++;

        if (val == 50)
            break;
    }
    archin.close();

    ASSERT_EQ(dh.cantClaves(), val);

    // Si no pasa este chequeo significa que tienen muchas colisiones,
    // por lo cual deberían reformular la función de hash.
    ASSERT_TRUE(dh.colisiones() < 26);
}

TEST(DiccHash, redimensionado) {
    DiccHash<int> dh;

    char delim = '\n';
    std::string archnom = "data/uniforme.txt";

    unsigned int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT_TRUE(archin.good());

    while(getline(archin,str,delim) && archin.good()) {
        dh.definir(str, val);
        val++;
    }
    archin.close();

    ASSERT_EQ(dh.cantClaves(),val);

    int eval = 0;
    archin.open(archnom.c_str());
    while(getline(archin,str) && archin.good()) {
        ASSERT_TRUE(dh.definido(str));
        ASSERT_EQ(dh.significado(str),eval);
        eval++;
    }
    archin.close();

    ASSERT_EQ(eval,val);

    ASSERT_LE(dh.factorCarga(), UMBRAL_FC);
}

