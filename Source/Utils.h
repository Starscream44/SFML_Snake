#pragma once
#include <random>
#include "Types.h"
#include <SFML/Graphics.hpp> 
#include "Constants.h"

namespace SnakeGame
{
    Position2D RandomCell(std::mt19937& rng, int gridW, int gridH);

    inline sf::Vector2f FieldOffset()
    {
        return { 0.f, (float)HudHeight };
    }
}