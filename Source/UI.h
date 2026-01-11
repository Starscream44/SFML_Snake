#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace SnakeGame
{
    class UI
    {
    public:
        bool LoadFont(const std::string& path = "Resources/font.ttf");

        void SetScore(int score);
        void Draw(sf::RenderWindow& window) const;

        void DrawMainMenu(sf::RenderWindow& w) const;

        void MainMenuMoveUp();
        void MainMenuMoveDown();

        int GetMainMenuIndex() const;

        void DrawModeSelect(sf::RenderWindow& window) const;

        void ModeMoveUp();
        void ModeMoveDown();

        int GetModeIndex() const;
        
		//game over screen
        void DrawGameOver(sf::RenderWindow& window) const;
        void GameOverMoveUp();
        void GameOverMoveDown();
        int GetGameOverIndex() const; // 0 Restart, 1 Exit

    private:
        void UpdateText();

        sf::Font m_font;
        sf::Text m_scoreText;

        int m_score = 0;

		// Main Menu Texts
        sf::Text m_titleText;
        sf::Text m_menuStart;
        sf::Text m_menuRecords;
        sf::Text m_menuExit;

        int m_mainMenuIndex = 0;
        void UpdateMainMenuVisual();

		// Mode Select Texts
        sf::Text m_modeTitle;
        sf::Text m_modeEasy;
        sf::Text m_modeMedium;
        sf::Text m_modeHard;

        int m_modeIndex = 0;
        void UpdateModeVisual();

		// Game Over Texts
        sf::Text m_gameOverTitle;
        sf::Text m_goRestart;
        sf::Text m_goExit;

        int m_gameOverIndex = 0;
        void UpdateGameOverVisual();
    };
}