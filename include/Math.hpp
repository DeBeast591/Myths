#pragma once
#include <cmath>
#include <iostream>

struct Vector2f {

    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    void print() {
        std::cout << x << ", " << y << std::endl;
    }

    void printAsInt() {
        std::cout << std::round(x) << ", " << std::round(y) << std::endl;
    }

    int getXInt() {
        return std::round(x);
    }

    int getYInt() {
        return std::round(y);
    }

    float x, y;
};