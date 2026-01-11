#include "Snake.h"
#include "Utils.h"

namespace SnakeGame
{
    static float RotationForDir(SnakeGame::Direction dir)
    {
        switch (dir)
        {
        case SnakeGame::Direction::Right: return 0.f;
        case SnakeGame::Direction::Down:  return 90.f;
        case SnakeGame::Direction::Left:  return 180.f;
        case SnakeGame::Direction::Up:    return 270.f;
        }
        return 0.f;
    }

    static SnakeGame::Direction DirFromTo(const SnakeGame::Position2D& from, const SnakeGame::Position2D& to)
    {
        if (to.x > from.x) return SnakeGame::Direction::Right;
        if (to.x < from.x) return SnakeGame::Direction::Left;
        if (to.y > from.y) return SnakeGame::Direction::Down;
        return SnakeGame::Direction::Up;
    }

    bool Snake::LoadTextures()
    {
        const bool okH = m_texHead.loadFromFile("Resources/snake_head.png");
        const bool okB = m_texBody.loadFromFile("Resources/snake_body.png");
        const bool okT = m_texTail.loadFromFile("Resources/snake_tail.png");
        return okH && okB && okT;
    }

    void Snake::Init(Position2D startCell, int startLength, Direction startDir)
    {
        m_cells.clear();
        m_cells.reserve(startLength);

        m_dir = startDir;
        m_timer = 0.f;
        m_pendingGrow = 0;

        // head
        Position2D cell = startCell;
        m_cells.push_back(cell);

        // body behind head
        for (int i = 1; i < startLength; ++i)
        {
            switch (startDir)
            {
            case Direction::Right: cell.x -= 1; break;
            case Direction::Left:  cell.x += 1; break;
            case Direction::Up:    cell.y += 1; break;
            case Direction::Down:  cell.y -= 1; break;
            }
            m_cells.push_back(cell);
        }
    }

    void Snake::SetDirection(Direction dir)
    {
        const bool opposite =
            (m_dir == Direction::Right && dir == Direction::Left) ||
            (m_dir == Direction::Left && dir == Direction::Right) ||
            (m_dir == Direction::Up && dir == Direction::Down) ||
            (m_dir == Direction::Down && dir == Direction::Up);

        if (!opposite) m_dir = dir;
    }

    void Snake::Update(float dt)
    {
        m_timer += dt;
        while (m_timer >= m_moveInterval)
        {
            m_timer -= m_moveInterval;
            Step();
        }
    }


    void Snake::Grow(int count)
    {
        m_pendingGrow += count;
    }

    void Snake::Step()
    {
        Position2D newHead = m_cells.front();

        switch (m_dir)
        {
        case Direction::Right: newHead.x += 1; break;
        case Direction::Left:  newHead.x -= 1; break;
        case Direction::Up:    newHead.y -= 1; break; 
        case Direction::Down:  newHead.y += 1; break;
        }

      

        m_cells.insert(m_cells.begin(), newHead);

        if (m_pendingGrow > 0)
            m_pendingGrow--;
        else
            m_cells.pop_back();
    }

    sf::Vector2f Snake::CellToPixels(const Position2D& cell) const
    {
        return sf::Vector2f{
            static_cast<float>(cell.x * CellSize),
            static_cast<float>(cell.y * CellSize)
        } + FieldOffset();
    }

    void Snake::Draw(sf::RenderWindow& window) const
    {
        for (size_t i = 0; i < m_cells.size(); ++i)
        {
            sf::Sprite s;

            if (i == 0) s.setTexture(m_texHead);
            else if (i == m_cells.size() - 1) s.setTexture(m_texTail);
            else s.setTexture(m_texBody);

            if (i == 0)
            {
				//head move direction
                s.setRotation(RotationForDir(m_dir));
            }
            else if (i == m_cells.size() - 1 && m_cells.size() >= 2)
            {
				//tail last segment direction
                auto tailDir = DirFromTo(m_cells[m_cells.size() - 2], m_cells[m_cells.size() - 1]);
                s.setRotation(RotationForDir(tailDir));
            }
            else
            {
				//body segment direction
                auto bodyDir = DirFromTo(m_cells[i - 1], m_cells[i]);

                if (bodyDir == Direction::Left || bodyDir == Direction::Right)
                    s.setRotation(0.f);
                else
                    s.setRotation(90.f);
            }


            auto ts = s.getTexture()->getSize();

			//rotate around center
            s.setOrigin(ts.x * 0.5f, ts.y * 0.5f);

			//scale to cell size
            s.setScale((float)CellSize / ts.x, (float)CellSize / ts.y);

			//position to center of cell
            sf::Vector2f pos = CellToPixels(m_cells[i]) + sf::Vector2f(CellSize * 0.5f, CellSize * 0.5f);
            s.setPosition(pos);

            window.draw(s);
        }
    }

    bool Snake::OccupiesCell(const Position2D& cell) const
    {
        for (const auto& c : m_cells)
            if (c.x == cell.x && c.y == cell.y)
                return true;
        return false;
    }

    void Snake::SetMoveInterval(float seconds)
    {
        m_moveInterval = seconds;
    }

    bool Snake::IsSelfCollision() const
    {
        if (m_cells.size() < 4) 
            return false;

        const auto& h = m_cells.front();
        for (size_t i = 1; i < m_cells.size(); ++i)
        {
            if (m_cells[i].x == h.x && m_cells[i].y == h.y)
                return true;
        }
        return false;
    }
}
