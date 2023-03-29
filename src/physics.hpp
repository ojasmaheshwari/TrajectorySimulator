#pragma once
#include<cmath>
#define gravity 9.8

namespace trajectory{
    float getYPosition(const float theta, const float u, const float x){
        // Utilizes Equation of Trajectory to calculate Y
        return x * std::tan(theta) - (gravity * std::pow(x, 2))/(2 * std::pow(u, 2) * std::pow(std::cos(theta), 2));
    }

    float getRange(const float theta, const float u){
        return std::pow(u, 2) * std::sin(2 * theta) / gravity;
    }
}
