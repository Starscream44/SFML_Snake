#include "Apple.h"
#include "Utils.h"

namespace SnakeGame
{
    static sf::Vector2f CellCenterPixels(const Position2D& c)
    {
        return sf::Vector2f(
            (c.x + 0.5f) * CellSize,
            (c.y + 0.5f) * CellSize
        ) + FieldOffset();
    }

    void Apple::Init(Position2D cell, const sf::Texture& tex)
    {
        m_cell = cell;
        m_sprite.setTexture(tex);

        const auto ts = tex.getSize();
        if (ts.x == 0 || ts.y == 0) return; // на всякий, если файл не загрузился

        m_sprite.setOrigin(ts.x * 0.5f, ts.y * 0.5f);
        m_sprite.setScale((float)CellSize / ts.x, (float)CellSize / ts.y);
        m_sprite.setPosition(CellCenterPixels(m_cell));
    }

    void Apple::Draw(sf::RenderWindow& window) const
    {
        window.draw(m_sprite);
    }
}
