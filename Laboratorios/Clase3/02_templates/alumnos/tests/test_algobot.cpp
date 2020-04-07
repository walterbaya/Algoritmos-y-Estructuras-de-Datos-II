#include "gtest/gtest.h"
#include "../src/Algobot.cpp"

TEST(algobot, entrego) {
    Algobot ab;
    EXPECT_FALSE(ab.entrego(LU("001/01")));
    EXPECT_FALSE(ab.entrego(LU("002/02")));

    ab.entrega(LU("001/01"), LU("002/01"), "codigo_g1");
    EXPECT_TRUE(ab.entrego(LU("001/01")));
    EXPECT_FALSE(ab.entrego(LU("002/02")));

    ab.entrega(LU("001/02"), LU("002/02"), "codigo_g2");
    EXPECT_TRUE(ab.entrego(LU("001/01")));
    EXPECT_TRUE(ab.entrego(LU("002/02")));
}

TEST(algobot, codigo) {
    Algobot ab;
    ab.entrega(LU("001/01"), LU("002/01"), "codigo_g1");
    ab.entrega(LU("001/02"), LU("002/02"), "codigo_g2");
    EXPECT_EQ(ab.codigo(LU("001/01")), "codigo_g1");
    EXPECT_EQ(ab.codigo(LU("002/01")), "codigo_g1");
    EXPECT_EQ(ab.codigo(LU("001/02")), "codigo_g2");
    EXPECT_EQ(ab.codigo(LU("002/02")), "codigo_g2");
}

TEST(algobot, doble_entrega) {
    Algobot ab;
    ab.entrega(LU("001/01"), LU("002/01"), "codigo_v1");
    EXPECT_EQ(ab.codigo(LU("001/01")), "codigo_v1");
    ab.entrega(LU("001/01"), LU("002/01"), "codigo_v2");
    EXPECT_EQ(ab.codigo(LU("001/01")), "codigo_v2");
    ab.entrega(LU("002/01"), LU("001/01"), "codigo_v3");
    EXPECT_EQ(ab.codigo(LU("001/01")), "codigo_v3");
}
