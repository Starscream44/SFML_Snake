#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <string>

#include "Constants.h"
#include "Types.h"
#include "Snake.h"
#include "Apple.h"
#include "Walls.h"
#include "Records.h"
#include "UI.h"

namespace SnakeGame
{
    enum class GameState
    {
        MainMenu,
        Records,
        ModeSelect,
        Playing,
        AskName,
        NameInput,
        GameOver
    };

    enum class Difficulty
    {
        Easy,
        Medium,
        Hard
    };

    class Game
    {
    public:
        void Run();

        GameState m_state = GameState::MainMenu;
        Difficulty m_difficulty = Difficulty::Medium;

    private:
        void ProcessEvents();
        void Update(float dt);
        void Render();

        //apples
        void SpawnApples(int count);
        void RespawnApple(Apple& a);
        Position2D RandomCell();
        bool IsAppleCellFree(const Position2D& cell) const;

        sf::RenderWindow m_window;
        sf::Clock m_clock;
        bool m_running = true;

        Snake m_snake;

        //score points 
        UI m_ui;
        int m_score = 0;

        //apples
        sf::Texture m_texApple;
        std::vector<Apple> m_apples;

		//for random positions
        std::mt19937 m_rng{ std::random_device{}() };

        Wall m_walls;

        bool m_enterHeld = false;

        void StartNewGame();

        float m_baseMoveInterval = MoveInterval;
        int m_hardApplesEaten = 0;

		// Hard mode speedup
        float m_currentMoveInterval = MoveInterval;
        static constexpr float HardMinInterval = 0.06f;  
        static constexpr float HardStep = 0.005f;

        RecordsTable m_records;

        int m_selectedYesNo = 0;        // 0 = NO, 1 = YES
        std::string m_nameBuffer = "XYZ";
    };

   

}

