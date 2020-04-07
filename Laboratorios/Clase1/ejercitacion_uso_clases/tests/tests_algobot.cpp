#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "algobot.h"

using namespace std;

TEST_CASE("LU :: Constructor") {
    LU lu1("123/45");
    REQUIRE(lu1.numero() == 123);
    REQUIRE(lu1.anio() == 45);

    LU lu2("008/09");
    REQUIRE(lu2.numero() == 8);
    REQUIRE(lu2.anio() == 9);

    LU lu3("123/45;");
    REQUIRE(lu1.numero() == 123);
    REQUIRE(lu1.anio() == 45);
}

TEST_CASE("Mail :: libretas") {
    Mail m1("123/45", 0, false);
    REQUIRE(set<LU>{LU("123/45")} == m1.libretas());

    Mail m2("123/45;009/08", 0, false);
    REQUIRE(set<LU>{LU("123/45"), LU("009/08")} == m2.libretas());

    Mail m3("123/45;009/08;", 0, false);
    REQUIRE(set<LU>{LU("123/45"), LU("009/08")} == m3.libretas());

    Mail m4("009/08;123/45", 0, false);
    REQUIRE(set<LU>{LU("123/45"), LU("009/08")} == m4.libretas());
}
