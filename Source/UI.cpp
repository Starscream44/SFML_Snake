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
       

        // --- Main menu texts ---
        m_titleText.setFont(m_font);
        m_titleText.setString("SNAKE");
        m_titleText.setCharacterSize(64);
        m_titleText.setFillColor(sf::Color::White);
        {
            auto b = m_titleText.getLocalBounds();
            m_titleText.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_titleText.setPosition((float)WindowWidth * 0.5f, 140.0f);
        }

        auto setupItem = [&](sf::Text& t, const std::string& s, float y)
            {
                t.setFont(m_font);
                t.setString(s);
                t.setCharacterSize(36);
                t.setFillColor(sf::Color::White);

                auto b = t.getLocalBounds();
                t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
                t.setPosition((float)WindowWidth * 0.5f, y);
            };

        setupItem(m_menuStart, "START", 300.0f);
        setupItem(m_menuRecords, "RECORDS", 380.0f);
        setupItem(m_menuExit, "EXIT", 460.0f);

        m_mainMenuIndex = 0;
        UpdateMainMenuVisual();

        // --- Mode select texts ---
        m_modeTitle.setFont(m_font);
        m_modeTitle.setString("DIFFICULTY");
        m_modeTitle.setCharacterSize(48);
        m_modeTitle.setFillColor(sf::Color::White);
        {
            auto b = m_modeTitle.getLocalBounds();
            m_modeTitle.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_modeTitle.setPosition((float)WindowWidth * 0.5f, 140.0f);
        }

        auto setupModeItem = [&](sf::Text& t, const std::string& s, float y)
            {
                t.setFont(m_font);
                t.setString(s);
                t.setCharacterSize(36);
                t.setFillColor(sf::Color::White);

                auto b = t.getLocalBounds();
                t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
                t.setPosition((float)WindowWidth * 0.5f, y);
            };

        setupModeItem(m_modeEasy, "EASY", 300.0f);
        setupModeItem(m_modeMedium, "MEDIUM", 380.0f);
        setupModeItem(m_modeHard, "HARD", 460.0f);

        m_modeIndex = 1;
        UpdateModeVisual();

        // --- GameOver texts ---
        m_gameOverTitle.setFont(m_font);
        m_gameOverTitle.setString("GAME OVER");
        m_gameOverTitle.setCharacterSize(56);
        m_gameOverTitle.setFillColor(sf::Color::White);
        {
            auto b = m_gameOverTitle.getLocalBounds();
            m_gameOverTitle.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_gameOverTitle.setPosition((float)WindowWidth * 0.5f, 140.0f);
        }

        auto setupGOItem = [&](sf::Text& t, const std::string& s, float y)
            {
                t.setFont(m_font);
                t.setString(s);
                t.setCharacterSize(36);
                t.setFillColor(sf::Color::White);

                auto b = t.getLocalBounds();
                t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
                t.setPosition((float)WindowWidth * 0.5f, y);
            };

        setupGOItem(m_goRestart, "RESTART", 340.0f);
        setupGOItem(m_goExit, "EXIT", 420.0f);

        m_gameOverIndex = 0;
        UpdateGameOverVisual();

        // --- AskName popup texts ---
        m_askNameTitle.setFont(m_font);
        m_askNameTitle.setString("ENTER NAME");
        m_askNameTitle.setCharacterSize(48);
        m_askNameTitle.setFillColor(sf::Color::White);
        {
            auto b = m_askNameTitle.getLocalBounds();
            m_askNameTitle.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_askNameTitle.setPosition((float)WindowWidth * 0.5f, 240.0f);
        }

        auto setupAskItem = [&](sf::Text& t, const std::string& s, float y)
            {
                t.setFont(m_font);
                t.setString(s);
                t.setCharacterSize(56);
                t.setFillColor(sf::Color::White);

                auto b = t.getLocalBounds();
                t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
                t.setPosition((float)WindowWidth * 0.5f, y);
            };

        setupAskItem(m_askNo, "NO", 340.0f);
        setupAskItem(m_askYes, "YES", 420.0f);

        m_askNameIndex = 0;
        UpdateAskNameVisual();


        // --- NameInput popup texts ---
        m_nameInputTitle.setFont(m_font);
        m_nameInputTitle.setString("TYPE NAME");
        m_nameInputTitle.setCharacterSize(48);
        m_nameInputTitle.setFillColor(sf::Color::White);
        {
            auto b = m_nameInputTitle.getLocalBounds();
            m_nameInputTitle.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_nameInputTitle.setPosition((float)WindowWidth * 0.5f, 240.0f);
        }

        m_nameInputValue.setFont(m_font);
        m_nameInputValue.setCharacterSize(56);
        m_nameInputValue.setFillColor(sf::Color::Green);
        m_nameInputValue.setString(m_nameBuffer);
        {
            auto b = m_nameInputValue.getLocalBounds();
            m_nameInputValue.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            m_nameInputValue.setPosition((float)WindowWidth * 0.5f, 380.0f);
        }

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

    void UI::DrawMainMenu(sf::RenderWindow& window) const
    {
        window.draw(m_titleText);
        window.draw(m_menuStart);
        window.draw(m_menuRecords);
        window.draw(m_menuExit);
    }

    void UI::UpdateMainMenuVisual()
    {
        //base color
        m_menuStart.setFillColor(sf::Color::White);
        m_menuRecords.setFillColor(sf::Color::White);
        m_menuExit.setFillColor(sf::Color::White);

		//selected color
        if (m_mainMenuIndex == 0) m_menuStart.setFillColor(sf::Color::Yellow);
        if (m_mainMenuIndex == 1) m_menuRecords.setFillColor(sf::Color::Yellow);
        if (m_mainMenuIndex == 2) m_menuExit.setFillColor(sf::Color::Yellow);
    }

    void UI::MainMenuMoveUp()
    {
        m_mainMenuIndex--;
        if (m_mainMenuIndex < 0) m_mainMenuIndex = 2;
        UpdateMainMenuVisual();
    }

    void UI::MainMenuMoveDown()
    {
        m_mainMenuIndex++;
        if (m_mainMenuIndex > 2) m_mainMenuIndex = 0;
        UpdateMainMenuVisual();
    }

    int UI::GetMainMenuIndex() const
    {
        return m_mainMenuIndex;
    }

    void UI::DrawModeSelect(sf::RenderWindow& window) const
    {
        window.draw(m_modeTitle);
        window.draw(m_modeEasy);
        window.draw(m_modeMedium);
        window.draw(m_modeHard);
    }

    void UI::UpdateModeVisual()
    {
        m_modeEasy.setFillColor(sf::Color::White);
        m_modeMedium.setFillColor(sf::Color::White);
        m_modeHard.setFillColor(sf::Color::White);

        if (m_modeIndex == 0) m_modeEasy.setFillColor(sf::Color::Yellow);
        if (m_modeIndex == 1) m_modeMedium.setFillColor(sf::Color::Yellow);
        if (m_modeIndex == 2) m_modeHard.setFillColor(sf::Color::Yellow);
    }

    void UI::ModeMoveUp()
    {
        m_modeIndex--;
        if (m_modeIndex < 0) m_modeIndex = 2;
        UpdateModeVisual();
    }

    void UI::ModeMoveDown()
    {
        m_modeIndex++;
        if (m_modeIndex > 2) m_modeIndex = 0;
        UpdateModeVisual();
    }

    int UI::GetModeIndex() const
    {
        return m_modeIndex;
    }

    void UI::DrawGameOver(sf::RenderWindow& window) const
    {
        window.draw(m_gameOverTitle);
        window.draw(m_goRestart);
        window.draw(m_goExit);
        for (const auto& t : m_recordsText)
            window.draw(t);
    }

    void UI::UpdateGameOverVisual()
    {
        m_goRestart.setFillColor(sf::Color::White);
        m_goExit.setFillColor(sf::Color::White);

        if (m_gameOverIndex == 0) m_goRestart.setFillColor(sf::Color::Yellow);
        if (m_gameOverIndex == 1) m_goExit.setFillColor(sf::Color::Yellow);
    }

    void UI::GameOverMoveUp()
    {
        m_gameOverIndex--;
        if (m_gameOverIndex < 0) m_gameOverIndex = 1;
        UpdateGameOverVisual();
    }

    void UI::GameOverMoveDown()
    {
        m_gameOverIndex++;
        if (m_gameOverIndex > 1) m_gameOverIndex = 0;
        UpdateGameOverVisual();
    }

    int UI::GetGameOverIndex() const
    {
        return m_gameOverIndex;
    }

    void UI::UpdateAskNameVisual()
    {
        m_askNo.setFillColor(sf::Color::White);
        m_askYes.setFillColor(sf::Color::White);

        
        if (m_askNameIndex == 0) m_askNo.setFillColor(sf::Color::Green);
        if (m_askNameIndex == 1) m_askYes.setFillColor(sf::Color::Green);
    }

    void UI::AskNameMoveUp()
    {
        m_askNameIndex--;
        if (m_askNameIndex < 0) m_askNameIndex = 1;
        UpdateAskNameVisual();
    }

    void UI::AskNameMoveDown()
    {
        m_askNameIndex++;
        if (m_askNameIndex > 1) m_askNameIndex = 0;
        UpdateAskNameVisual();
    }

    int UI::GetAskNameIndex() const
    {
        return m_askNameIndex;
    }

    void UI::DrawAskName(sf::RenderWindow& window) const
    {
       
        sf::RectangleShape bg(sf::Vector2f(640.0f, 520.0f));
        bg.setFillColor(sf::Color::Black);
        bg.setOrigin(bg.getSize().x * 0.5f, bg.getSize().y * 0.5f);
        bg.setPosition((float)WindowWidth * 0.5f, (float)WindowHeight * 0.5f);

        
        sf::RectangleShape border = bg;
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(4.0f);

        window.draw(bg);
        window.draw(border);

        window.draw(m_askNameTitle);
        window.draw(m_askNo);
        window.draw(m_askYes);
    }

    void UI::SetNameBuffer(const std::string& name)
    {
        m_nameBuffer = name;

        m_nameInputValue.setString(m_nameBuffer);
        auto b = m_nameInputValue.getLocalBounds();
        m_nameInputValue.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
    }

    void UI::DrawNameInput(sf::RenderWindow& window) const
    {
        sf::RectangleShape bg(sf::Vector2f(640.0f, 520.0f));
        bg.setFillColor(sf::Color::Black);
        bg.setOrigin(bg.getSize().x * 0.5f, bg.getSize().y * 0.5f);
        bg.setPosition((float)WindowWidth * 0.5f, (float)WindowHeight * 0.5f);

        sf::RectangleShape border = bg;
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(4.0f);

        window.draw(bg);
        window.draw(border);

        window.draw(m_nameInputTitle);
        window.draw(m_nameInputValue);
    }

    void UI::SetRecords(const std::vector<RecordEntry>& records)
    {
        m_recordsText.clear();

        float y = 210.0f;   
        int rank = 1;

        for (const auto& r : records)
        {
            sf::Text t;
            t.setFont(m_font);
            t.setCharacterSize(28);
            t.setFillColor(sf::Color::White);

            t.setString(std::to_string(rank) + ". " + r.name + "   " + std::to_string(r.score));

            auto b = t.getLocalBounds();
            t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            t.setPosition((float)WindowWidth * 0.5f, y);

            m_recordsText.push_back(t);

            y += 34.0f;
            rank++;
        }
    }

    void UI::DrawRecords(sf::RenderWindow& window) const
    {
        window.clear();

        
        sf::Text title;
        title.setFont(m_font);
        title.setString("RECORDS");
        title.setCharacterSize(56);
        title.setFillColor(sf::Color::White);
        {
            auto b = title.getLocalBounds();
            title.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            title.setPosition((float)WindowWidth * 0.5f, 140.0f);
        }

        window.draw(title);

       
        for (const auto& t : m_recordsText)
            window.draw(t);

        
        sf::Text hint;
        hint.setFont(m_font);
        hint.setString("Press Enter to return");
        hint.setCharacterSize(22);
        hint.setFillColor(sf::Color(180, 180, 180));
        {
            auto b = hint.getLocalBounds();
            hint.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
            hint.setPosition((float)WindowWidth * 0.5f, (float)WindowHeight - 90.0f);
        }
        window.draw(hint);
    }
}