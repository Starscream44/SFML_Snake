#include "Walls.h"
#include "Utils.h"

namespace SnakeGame
{
    bool Wall::LoadTexture(const std::string& path)
    {

        if (!m_tex.loadFromFile(path)) return false;
        m_tex.setSmooth(false);   // важно: убирает "швы" при масштабировании
        return true;
    }

    void Wall::Init(int gridW, int gridH)
    {
        m_gridW = gridW;
        m_gridH = gridH;

        m_cells.clear();
        if (gridW <= 0 || gridH <= 0) return;

        // верхняя строка (y = 0)
        for (int x = 0; x < gridW; ++x)
            m_cells.push_back({ x, 0 });

        // нижняя строка (y = gridH - 1)
        if (gridH > 1)
        {
            for (int x = 0; x < gridW; ++x)
                m_cells.push_back({ x, gridH - 1 });
        }

        // левая колонка (x = 0), без углов (чтобы не дублировать)
        for (int y = 1; y < gridH - 1; ++y)
            m_cells.push_back({ 0, y });

        // правая колонка (x = gridW - 1), без углов
        if (gridW > 1)
        {
            for (int y = 1; y < gridH - 1; ++y)
                m_cells.push_back({ gridW - 1, y });
        }
    }

    bool Wall::IsWallCell(const Position2D& cell) const
    {
        // Быстрая проверка по границе, без перебора массива
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

        // ВАЖНО: для стен — без центра
        s.setOrigin(0.f, 0.f);

        // Если wall.png = 32x32 и CellSize=32, то масштаб = 1
        // Но оставим формулу, чтобы не зависеть от размеров файла
        auto ts = m_tex.getSize();
        s.setScale((float)CellSize / ts.x, (float)CellSize / ts.y);

        for (const auto& c : m_cells)
        {
            s.setPosition(CellToPixels(c));   // <-- вот так
            window.draw(s);
        }
    }
}