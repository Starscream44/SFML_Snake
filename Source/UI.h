#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Records.h"

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

        // AskName popup (NO/YES)
        void DrawAskName(sf::RenderWindow& window) const;
        void AskNameMoveUp();
        void AskNameMoveDown();
        int GetAskNameIndex() const; // 0 NO, 1 YES

        // Name input popup (only drawing for now)
        void DrawNameInput(sf::RenderWindow& window) const;
        void SetNameBuffer(const std::string& name);

        void SetRecords(const std::vector<RecordEntry>& records);

        void DrawRecords(sf::RenderWindow& window) const;

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

        // AskName popup texts
        sf::Text m_askNameTitle;
        sf::Text m_askNo;
        sf::Text m_askYes;
        int m_askNameIndex = 0;
        void UpdateAskNameVisual();

        std::vector<sf::Text> m_recordsText;

        // Name input popup texts
        sf::Text m_nameInputTitle;
        sf::Text m_nameInputValue;
        std::string m_nameBuffer = "XYZ";

    };
}