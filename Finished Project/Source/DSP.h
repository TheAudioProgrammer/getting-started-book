#pragma once

#include <cmath>

/**
  Calculates panning using equal power curves formula. Panning must be [-1, 1].
 */
inline void panningEqualPower(float panning, float& left, float& right)
{
    float x = 0.7853981633974483f * (panning + 1.0f);
    left = std::cos(x);
    right = std::sin(x);
}
