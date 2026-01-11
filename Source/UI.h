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

    private:
        void UpdateText();

        sf::Font m_font;
        sf::Text m_scoreText;

        int m_score = 0;
    };
}
