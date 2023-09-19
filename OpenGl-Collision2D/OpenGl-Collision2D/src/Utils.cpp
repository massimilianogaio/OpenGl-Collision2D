#include "Utils.h"

glm::vec2 halfWindowsSize = glm::vec2(750.0f, 400.0f);

float GetRandomNumber(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}