//
// Created by Dmitriy on 07.03.2025.
//
#include <gtest/gtest.h>
#include <iostream>
#include <tuple>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для решения системы уравнений
tuple<int, double, double> solveSystem(double a, double b, double c, double d, double e, double f) {
    if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0)) {
        return {5, 0, 0}; // Бесконечно много решений
    }

    double det = a * d - c * b;
    if (det != 0) {
        double x = (d * e - b * f) / det;
        double y = (a * f - c * e) / det;
        return {2, x, y}; // Одно решение
        cout << "DEBUG: x = " << x << ", y = " << y << endl;
    }

    if ((e * d - b * f != 0) || (a * f - c * e != 0)) {
        return {0, 0, 0}; // Нет решений
    }

    if (a == 0 && c == 0) {
        return {4, e / b, 0}; // y = const
    }
    if (b == 0 && d == 0) {
        return {3, e / a, 0}; // x = const
    }

    return {1, -a / b, e / b}; // Прямая kx + b
}

// Тесты для различных случаев
TEST(SolveSystemTest, NoSolutions) {
    auto result = solveSystem(1, 1, 1, 1, 2, 3);
    EXPECT_EQ(get<0>(result), 0);
}

TEST(SolveSystemTest, UniqueSolution) {
    auto result = solveSystem(2, 3, 1, 4, 5, 6);
    EXPECT_EQ(get<0>(result), 2);
    EXPECT_NEAR(get<1>(result), 0.4, 1e-6);
    EXPECT_NEAR(get<2>(result), 1.4, 1e-6);
}

TEST(SolveSystemTest, InfiniteSolutions) {
    auto result = solveSystem(0, 0, 0, 0, 0, 0);
    EXPECT_EQ(get<0>(result), 5);
}

TEST(SolveSystemTest, VerticalLine) {
    auto result = solveSystem(1, 0, 1, 0, 4, 4);
    EXPECT_EQ(get<0>(result), 3);
    EXPECT_EQ(get<1>(result), 4);
}

TEST(SolveSystemTest, HorizontalLine) {
    auto result = solveSystem(0, 1, 0, 1, 3, 3);
    EXPECT_EQ(get<0>(result), 4);
    EXPECT_EQ(get<1>(result), 3);
}

TEST(SolveSystemTest, GeneralLine) {
    auto result = solveSystem(2, 4, 1, 2, 6, 3);
    EXPECT_EQ(get<0>(result), 1);
    EXPECT_NEAR(get<1>(result), -0.5, 1e-6);
    EXPECT_NEAR(get<2>(result), 1.5, 1e-6);
}

TEST(SolveSystemTest, DegenerateNoSolutions) {
    auto result = solveSystem(0, 0, 0, 1, 1, 1);
    EXPECT_EQ(get<0>(result), 0);
}

TEST(SolveSystemTest, ParallelLinesNoSolutions) {
    auto result = solveSystem(1, 1, 1, 1, 2, 3);
    EXPECT_EQ(get<0>(result), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}