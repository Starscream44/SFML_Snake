#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Types.h"
#include "Constants.h"

namespace SnakeGame
{
    class Wall
    {
    public:
        bool LoadTexture(const std::string& path = "Resources/wall.png");
        void Init(int gridW, int gridH);

        void Draw(sf::RenderWindow& window) const;

        bool IsWallCell(const Position2D& cell) const;

    private:
        sf::Vector2f CellToPixels(const Position2D& cell) const;

    private:
        int m_gridW = 0;
        int m_gridH = 0;

        std::vector<Position2D> m_cells; // все клетки стен по периметру
        sf::Texture m_tex;
    };
}

