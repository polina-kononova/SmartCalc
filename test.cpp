#include <gtest/gtest.h>

#include "model.h"

TEST(calc_test, number) {
    char str[] = "-35";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(-35, model.getResult());
}

TEST(calc_test, sum) {
    char str[] = "2 + 3";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(5, model.getResult());
}

TEST(calc_test, mulsum) {
    char str[] = "3 * 2 + 1 + 2";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(9, model.getResult());
}

TEST(calc_test, power) {
    char str[] = "2 + 3 ^ 2 * 2 + 5 * 7 ^ 2";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(265, model.getResult());
}

TEST(calc_test, br) {
    char str[] = "( 2 * 3 ) + 1";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(7, model.getResult());
}

TEST(calc_test, br_d) {
    char str[] = "1 + 2 * ( 3 + 4 / 2 - ( 1 + ( 5 - 4 ) * 2 ) ) * 2 + 1";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(10, model.getResult());
}

TEST(calc_test, unary) {
    char str[] = "+3 + -2.2";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(3 - 2.2, model.getResult());
}

TEST(calc_test, sin) {
    char str[] = "sin 0 + 2 mod 2";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(sin(0), model.getResult());
}

TEST(calc_test, cos_br) {
    char str[] = "cos 0 + sin ( 1 - 1 )";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(cos(0), model.getResult());
}

TEST(calc_test, sqrt) {
    char str[] = " sqrt ( sqrt 16 )";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(2, model.getResult());
}

TEST(calc_test, func) {
    char str[] = "tan 0 + asin 0 * acos 1 + sqrt 1 - log 1 + ln 1 + atan 0";
    s21::Model model;
    model.calc(str);
    ASSERT_EQ(1, model.getResult());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
