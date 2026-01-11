#include "Game.h"
#include "Constants.h"

namespace SnakeGame
{
    void Game::Run()
    {
        m_window.create(sf::VideoMode(WindowWidth, WindowHeight), "Snake");
        m_window.setFramerateLimit(60);

        const int gridW = GridW;
        const int gridH = GridH;

		//reset score
        m_score = 0;

        if (!m_ui.LoadFont("Resources/font.ttf"))
            return;

        m_ui.SetScore(m_score);

        if (!m_walls.LoadTexture("Resources/wall.png"))
            return;

        m_walls.Init(gridW, gridH);

        if (!m_snake.LoadTextures())
            return;

        if (!m_texApple.loadFromFile("Resources/apple.png"))
            return;

        m_snake.Init({ 10, 7 }, 4, Direction::Right);
        SpawnApples(DefaultAppleCount);

        while (m_window.isOpen() && m_running)
        {
            const float dt = m_clock.restart().asSeconds();
            ProcessEvents();
            Update(dt);
            Render();
        }
    }

    void Game::ProcessEvents()
    {
        sf::Event e{};
        while (m_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                m_window.close();

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
                m_window.close();
        }
    }

    void Game::Update(float dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_snake.SetDirection(Direction::Up);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_snake.SetDirection(Direction::Down);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_snake.SetDirection(Direction::Left);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_snake.SetDirection(Direction::Right);

        m_snake.Update(dt);

		//apple collision
        const auto& h = m_snake.HeadCell();
        for (auto& a : m_apples)
        {
            if (a.Cell().x == h.x && a.Cell().y == h.y)
            {
                m_snake.Grow(1);
                RespawnApple(a);

                m_score += 1;
                m_ui.SetScore(m_score);

                break;
            }
        }
    }

    void Game::Render()
    {
        m_window.clear();

		//Draw background for HUD
        sf::RectangleShape hud;
        hud.setSize(sf::Vector2f((float)WindowWidth, (float)HudHeight));
        hud.setPosition(0.f, 0.f);
        hud.setFillColor(sf::Color(40, 80, 40));
        m_window.draw(hud);

        m_walls.Draw(m_window);

        for (const auto& a : m_apples)
            a.Draw(m_window);

        m_snake.Draw(m_window);
        m_ui.Draw(m_window);
        m_window.display();
    }

    Position2D Game::RandomCell()
    {
        const int gridW = GridW;
        const int gridH = GridH;

        std::uniform_int_distribution<int> dx(0, gridW - 1);
        std::uniform_int_distribution<int> dy(0, gridH - 1);

        return { dx(m_rng), dy(m_rng) };
    }

    bool Game::IsAppleCellFree(const Position2D& cell) const
    {
        if (m_snake.OccupiesCell(cell))
            return false;

        for (const auto& a : m_apples)
            if (a.Cell().x == cell.x && a.Cell().y == cell.y)
                return false;

        if (m_walls.IsWallCell(cell))
            return false;

        return true;
    }

    void Game::RespawnApple(Apple& a)
    {
        int attempts = 0;
        const int maxAttempts = 500;

        Position2D c{};
        do
        {
            c = RandomCell();
            ++attempts;
        } while (!IsAppleCellFree(c) && attempts < maxAttempts);

        if (attempts < maxAttempts)
            a.Init(c, m_texApple);
    }

    void Game::SpawnApples(int count)
    {
        m_apples.clear();
        m_apples.reserve(count);

        int spawned = 0;
        int attempts = 0;
        const int maxAttempts = count * 200;

        while (spawned < count && attempts < maxAttempts)
        {
            ++attempts;
            const auto c = RandomCell();

            if (!IsAppleCellFree(c))
                continue;

            Apple a;
            a.Init(c, m_texApple);
            m_apples.push_back(std::move(a));
            ++spawned;
        }
    }
}
