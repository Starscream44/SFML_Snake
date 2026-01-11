#include "Walls.h"
#include "Utils.h"

namespace SnakeGame
{
    bool Wall::LoadTexture(const std::string& path)
    {

        if (!m_tex.loadFromFile(path)) return false;
        m_tex.setSmooth(false);  
        return true;
    }

    void Wall::Init(int gridW, int gridH)
    {
        m_gridW = gridW;
        m_gridH = gridH;

        m_cells.clear();
        if (gridW <= 0 || gridH <= 0) return;

        //up (y = 0)
        for (int x = 0; x < gridW; ++x)
            m_cells.push_back({ x, 0 });

        //down (y = gridH - 1)
        if (gridH > 1)
        {
            for (int x = 0; x < gridW; ++x)
                m_cells.push_back({ x, gridH - 1 });
        }

        //left (x = 0)
        for (int y = 1; y < gridH - 1; ++y)
            m_cells.push_back({ 0, y });

        //right (x = gridW - 1)
        if (gridW > 1)
        {
            for (int y = 1; y < gridH - 1; ++y)
                m_cells.push_back({ gridW - 1, y });
        }
    }

    bool Wall::IsWallCell(const Position2D& cell) const
    {
        
        if (m_gridW <= 0 || m_gridH <= 0) return false;
        return (cell.x == 0 || cell.y == 0 || cell.x == (m_gridW - 1) || cell.y == (m_gridH - 1));

    }

    sf::Vector2f Wall::CellToPixels(const Position2D& cell) const
    {
        return sf::Vector2f(
            static_cast<float>(cell.x * CellSize),
            static_cast<float>(cell.y * CellSize)
        ) + FieldOffset();
    }

    void Wall::Draw(sf::RenderWindow& window) const
    {

        sf::Sprite s;
        s.setTexture(m_tex);

       
        s.setOrigin(0.f, 0.f);

        auto ts = m_tex.getSize();
        s.setScale((float)CellSize / ts.x, (float)CellSize / ts.y);

        for (const auto& c : m_cells)
        {
            s.setPosition(CellToPixels(c));
            window.draw(s);
        }
    }
}