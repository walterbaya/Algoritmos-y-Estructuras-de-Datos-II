#include "gtest-1.8.1/gtest.h"
#include "../src/Horario.cpp"

TEST(horario, constructor_y_getters) {
  Horario h(5, 30, 22);
  ASSERT_EQ(h.dame_hora(), 5);
  ASSERT_EQ(h.dame_min(), 30);
  ASSERT_EQ(h.dame_segs(), 22);
}

TEST(horario, eq) {
  Horario h(5, 30, 20);
  ASSERT_TRUE(h == Horario(5, 30, 20));
  ASSERT_FALSE(h == Horario(7, 30, 20));
  ASSERT_FALSE(h == Horario(5, 31, 20));
  ASSERT_FALSE(h == Horario(5, 30, 21));
}

TEST(horario, less) {
  ASSERT_TRUE(Horario(5, 30, 20) < Horario(6, 30, 20));
  ASSERT_TRUE(Horario(5, 30, 20) < Horario(5, 31, 20));
  ASSERT_TRUE(Horario(5, 30, 20) < Horario(5, 30, 21));

  ASSERT_FALSE(Horario(6, 30, 20) < Horario(5, 30, 20));
  ASSERT_FALSE(Horario(5, 31, 20) < Horario(5, 30, 20));
  ASSERT_FALSE(Horario(5, 30, 21) < Horario(5, 30, 20));

  ASSERT_FALSE(Horario(5, 30, 20) < Horario(5, 30, 20));
}

TEST(horario, restar_seg) {
  Horario h(0, 0, 15);
  ASSERT_EQ(h.dame_segs(), 15);

  h.restar_seg();
  ASSERT_EQ(h.dame_segs(), 14);
  
  h.restar_seg();
  ASSERT_EQ(h.dame_segs(), 13);

  Horario h1(0, 1, 1);
  h1.restar_seg();
  ASSERT_EQ(h1, Horario(0, 1, 0));
  h1.restar_seg();
  ASSERT_EQ(h1, Horario(0, 0, 59));
  h1.restar_seg();
  ASSERT_EQ(h1, Horario(0, 0, 58));
  
  Horario h2(1, 0, 1);
  h2.restar_seg();
  ASSERT_EQ(h2, Horario(1, 0, 0));
  h2.restar_seg();
  ASSERT_EQ(h2, Horario(0, 59, 59));
  h2.restar_seg();
  ASSERT_EQ(h2, Horario(0, 59, 58));
}
