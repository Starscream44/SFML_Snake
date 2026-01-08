#include "Utils.h"

namespace SnakeGame
{
    Position2D RandomCell(std::mt19937& rng, int gridW, int gridH)
    {
        std::uniform_int_distribution<int> dx(0, gridW - 1);
        std::uniform_int_distribution<int> dy(0, gridH - 1);
        return { dx(rng), dy(rng) };
    }
}