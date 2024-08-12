#include <gtest/gtest.h>

#include "../Model/helper.h"
#include "../Model/model.cc"

s21::Model test;

TEST(calc, 01) {
  std::string str = "1 + 2 + 3 + 4 * 7 * 8 ^ 3 ^ 2";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.first, 3758096390);
}

TEST(calc, 02) {
  std::string str = "-1 * (888.22 * sin(888 - (+6)) / (85 - 6))";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, -7.9671827, 1e-7);
}

TEST(calc, 03) {
  std::string str = "-1 * (888.22 * sin((888 - (+6)) ^ 3) / (85 - 6))";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, 8.8517682, 1e-7);
}

TEST(calc, 04) {
  std::string str = "sin(5) * cos(10) - tan(10)";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, 0.1562452, 1e-7);
}

TEST(calc, 05) {
  std::string str = "asin(0.68) * acos(-0.2224) * atan(0.00005)";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, 0.0000671, 1e-7);
}

TEST(calc, 06) {
  std::string str = "log(0.68) * ln(0.2224) ^ 1 ^ 1 ^ 2";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, 0.2517856, 1e-7);
}

TEST(calc, 08) {
  std::string str = "(6.4 * (6 - 2 * (6 ^ (2 - 0))))";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, -422.4, 1e-7);
}

TEST(calc, 09) {
  std::string str = "1 * 1 - ";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.second, err_);
}

TEST(calc, 10) {
  std::string str = "(1 * 1)) 90 - )";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.second, err_);
}

TEST(calc, 11) {
  std::string str = "1 - 3 - 5 * 3 / 3";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.first, -7);
}

TEST(calc, 12) {
  std::string str = "6.3 * (7.2 - sqrt(5.6)) * 6 mod 2";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  EXPECT_NEAR(l.first, 0.7088736, 1e-7);
}

TEST(calc, 13) {
  std::string str = "5 + x * x";
  test.input_(str, 2);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.first, 9);
}

TEST(calc, 14) {
  std::string str = "";
  test.input_(str);
  std::pair<double, int> l = test.pursing_expr();
  ASSERT_EQ(l.second, err_);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
