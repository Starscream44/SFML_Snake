#include "UI.h"
#include "Constants.h" 

namespace SnakeGame
{
    bool UI::LoadFont(const std::string& path)
    {
        if (!m_font.loadFromFile(path))
            return false;

        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(28);   
        m_scoreText.setFillColor(sf::Color::White);

        UpdateText();
        return true;
    }

    void UI::SetScore(int score)
    {
        m_score = score;
        UpdateText();
    }

    void UI::UpdateText()
    {
        m_scoreText.setString("SCORE " + std::to_string(m_score));

        
        auto b = m_scoreText.getLocalBounds();
        m_scoreText.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);

      
        m_scoreText.setPosition((float)WindowWidth * 0.5f, (float)HudHeight * 0.5f);
    }

    void UI::Draw(sf::RenderWindow& window) const
    {
        window.draw(m_scoreText);
    }
}
