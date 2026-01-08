#pragma once
#include <SFML/Graphics.hpp>
#include "Types.h"
#include "Constants.h"

namespace SnakeGame
{
    class Apple
    {
    public:
        void Init(Position2D cell, const sf::Texture& tex);
        void Draw(sf::RenderWindow& window) const;

        const Position2D& Cell() const { return m_cell; }

    private:
        Position2D  m_cell{ 0, 0 };
        sf::Sprite  m_sprite;
    };
}
