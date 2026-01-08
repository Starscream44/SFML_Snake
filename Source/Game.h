#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Constants.h"
#include "Types.h"
#include "Snake.h"
#include "Apple.h"
#include "Walls.h"
#include "UI.h"

namespace SnakeGame
{
    class Game
    {
    public:
        void Run();

    private:
        void ProcessEvents();
        void Update(float dt);
        void Render();

        // €блоки
        void SpawnApples(int count);
        void RespawnApple(Apple& a);
        Position2D RandomCell();
        bool IsAppleCellFree(const Position2D& cell) const;

    private:
        sf::RenderWindow m_window;
        sf::Clock m_clock;
        bool m_running = true;

        Snake m_snake;

        //счетчик очков
        UI m_ui;
        int m_score = 0;

        // €блоки
        sf::Texture m_texApple;
        std::vector<Apple> m_apples;

        // рандом
        std::mt19937 m_rng{ std::random_device{}() };

        Wall m_walls;
    };
}

