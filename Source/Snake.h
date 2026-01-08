#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Types.h"
#include "Constants.h"

namespace SnakeGame
{
    enum class Direction { Up, Down, Left, Right };

    class Snake
    {
    public:
        bool LoadTextures();
        void Init(Position2D startCell, int startLength, Direction startDir);

        void SetDirection(Direction dir);
        void Update(float dt);
        void Draw(sf::RenderWindow& window) const;

        void Grow(int count = 1);

        const Position2D& HeadCell() const { return m_cells.front(); }

        bool OccupiesCell(const Position2D& cell) const;

    private:
        sf::Vector2f CellToPixels(const Position2D& cell) const;
        void Step(); // один “шаг” змеи по сетке

    private:
        std::vector<Position2D> m_cells;

        Direction m_dir = Direction::Right;

        float m_timer = 0.f;
        int m_pendingGrow = 0;

        sf::Texture m_texHead, m_texBody, m_texTail;
    };
}
