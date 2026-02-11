#include "Game.h"
#include "Constants.h"

namespace SnakeGame
{
    void Game::Run()
    {
        m_window.create(sf::VideoMode(WindowWidth, WindowHeight), "Snake");
        m_window.setFramerateLimit(60);
        m_ui.StartMenuMusic();

        const int gridW = GridW;
        const int gridH = GridH;

		//reset score
        m_score = 0;

        if (!m_ui.LoadFont("Resources/font.ttf"))
            return;

        m_ui.LoadMenuBackground("Resources/menu.png");

        m_ui.SetScore(m_score);

        if (!m_ui.LoadPlayground("Resources/playground.png"))
            return;

        if (!m_walls.LoadTexture("Resources/wall.png"))
            return;

        m_walls.Init(gridW, gridH);

        if (!m_snake.LoadTextures())
            return;

        if (!m_texApple.loadFromFile("Resources/apple.png"))
            return;

        m_snake.Init({ 10, 7 }, 4, Direction::Right);
        SpawnApples(DefaultAppleCount);

        m_records.Load(RecordsFileName);

        if (m_records.Get().empty())
        {
            m_records.Add("XYZ", 1, RecordsMaxCount);
            m_records.Save(RecordsFileName);
        }

        while (m_window.isOpen() && m_running)
        {
            const float dt = m_clock.restart().asSeconds();
            ProcessEvents();
            Update(dt);
            Render();
        }
    }

    static void PushTopToUI(UI& ui, const RecordsTable& recs)
    {
        auto top = recs.Get();
        if (top.size() > RecordsPopupCount)
            top.resize(RecordsPopupCount);

        ui.SetRecords(top);
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
            // --- Name input: read typed characters ---
            if (m_state == GameState::NameInput)
            {
				// 1) Symbols input
                if (e.type == sf::Event::TextEntered)
                {
                    const uint32_t ch = e.text.unicode;

                   
                    if (ch >= 32 && ch <= 126)
                    {
                        const char c = static_cast<char>(ch);

                        auto isAllowed = [](char x)
                            {
                                return (x >= 'A' && x <= 'Z') ||
                                    (x >= 'a' && x <= 'z') ||
                                    (x >= '0' && x <= '9') ||
                                    x == '_' || x == '-';
                            };

                        if (isAllowed(c))
                        {
							if (m_nameBuffer.size() < 12) //lenght limit
                                m_nameBuffer.push_back(c);
                        }
                    }
                }

                // 2) Backspace
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::BackSpace)
                {
                    if (!m_nameBuffer.empty())
                        m_nameBuffer.pop_back();
                }

				// 3) Enter 
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
                {
                    std::string finalName = m_nameBuffer.empty() ? "XYZ" : m_nameBuffer;

                    m_records.Add(finalName, m_score, RecordsMaxCount);
                    m_records.Save(RecordsFileName);

                    PushTopToUI(m_ui, m_records);

                    m_state = GameState::GameOver;
                    m_enterHeld = true;
                }
            }
        }

        if (e.type == sf::Event::KeyPressed && m_state == GameState::MainMenu)
        {
            if (e.key.code == sf::Keyboard::Up)
                m_ui.MainMenuMoveUp();

            if (e.key.code == sf::Keyboard::Down)
                m_ui.MainMenuMoveDown();
        }

        if (e.type == sf::Event::KeyPressed && m_state == GameState::ModeSelect)
        {
            if (e.key.code == sf::Keyboard::Up)
                m_ui.ModeMoveUp();

            if (e.key.code == sf::Keyboard::Down)
                m_ui.ModeMoveDown();

            if (e.key.code == sf::Keyboard::Return)
            {
                const int sel = m_ui.GetModeIndex(); // 0 easy, 1 medium, 2 hard

                if (sel == 0) m_difficulty = Difficulty::Easy;
                if (sel == 1) m_difficulty = Difficulty::Medium;
                if (sel == 2) m_difficulty = Difficulty::Hard;

                StartNewGame();
                m_state = GameState::Playing;
            }
         
        }

        if (e.type == sf::Event::KeyPressed && m_state == GameState::GameOver)
        {
            if (e.key.code == sf::Keyboard::Up)
                m_ui.GameOverMoveUp();

            if (e.key.code == sf::Keyboard::Down)
                m_ui.GameOverMoveDown();
        }
    }

    void Game::Update(float dt)
    {
        // ENTER for menus (one-shot)
        const bool enterNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
        if (m_state == GameState::MainMenu)
        {
            if (enterNow && !m_enterHeld)
            {
                const int sel = m_ui.GetMainMenuIndex();

                if (sel == 0)
                {
                    m_state = GameState::ModeSelect;
                    m_enterHeld = true; 
                }
                else if (sel == 1)
                {
                    auto top = m_records.Get();
                    if (top.size() > RecordsMaxCount)
                        top.resize(RecordsMaxCount);

                    m_ui.SetRecords(top);

                    m_state = GameState::Records;
                    m_enterHeld = true;
                    return;
                }
                else if (sel == 2)
                {
                    m_window.close();
                    m_enterHeld = true;
                }
            }
        }

        if (m_state == GameState::ModeSelect)
        {
            if (enterNow && !m_enterHeld)
            {
                const int sel = m_ui.GetModeIndex(); // 0 easy, 1 medium, 2 hard

                if (sel == 0) m_difficulty = Difficulty::Easy;
                if (sel == 1) m_difficulty = Difficulty::Medium;
                if (sel == 2) m_difficulty = Difficulty::Hard;

                StartNewGame();
                m_state = GameState::Playing;
                m_enterHeld = true;
                m_ui.StopMenuMusic();
                m_ui.StartGameplayMusic();
            }
        }

        if (m_state == GameState::GameOver)
        {
            m_ui.StopGameplayMusic();
            m_ui.StartMenuMusic();
            if (enterNow && !m_enterHeld)
            {
                const int sel = m_ui.GetGameOverIndex(); // 0 Restart, 1 Exit

                if (sel == 0)
                {
                    m_state = GameState::ModeSelect;
                    m_enterHeld = true;
                }
                else if (sel == 1)
                {
                    m_window.close();
                    m_enterHeld = true;
                }
 
            }
        }

        if (m_state == GameState::Records)
        {
            if (enterNow && !m_enterHeld)
            {
                m_state = GameState::MainMenu;
                m_enterHeld = true;
                return;
            }

            m_enterHeld = enterNow;
            return;
        }
       
        if (m_state == GameState::AskName)
        {
            m_ui.StopGameplayMusic();
            m_ui.StartMenuMusic();
            //NO/YES
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                m_ui.AskNameMoveUp();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                m_ui.AskNameMoveDown();



            // Enter
            if (enterNow && !m_enterHeld)
            {
                const int sel = m_ui.GetAskNameIndex(); // 0 NO, 1 YES

                if (sel == 0) // NO
                {
                    m_records.Add("XYZ", m_score, RecordsMaxCount);
                    m_records.Save(RecordsFileName);

                    PushTopToUI(m_ui, m_records);

                    m_state = GameState::GameOver;
                    m_enterHeld = true;
                    return;
                }
                else // YES
                {
                    m_nameBuffer.clear();
                    m_state = GameState::NameInput;
                    m_enterHeld = true;
                    return;
                }
            }

            
            m_enterHeld = enterNow;
            return;
        }


        // remember key state
        m_enterHeld = enterNow;

        if (m_state != GameState::Playing)
            return;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_snake.SetDirection(Direction::Up);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_snake.SetDirection(Direction::Down);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_snake.SetDirection(Direction::Left);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_snake.SetDirection(Direction::Right);

        m_snake.Update(dt);
        const auto& h = m_snake.HeadCell();

        // death by wall
        if (m_walls.IsWallCell(h))
        {
            m_ui.PlayCrashSound();
            const bool isHigh = m_records.IsHighScore(m_score, RecordsMaxCount);

            if (isHigh)
            {
                m_selectedYesNo = 0;   // default NO
                m_nameBuffer = "XYZ";  // default name
                m_state = GameState::AskName;
            }
            else
            {
                auto top = m_records.Get();
                if (top.size() > RecordsPopupCount)
                    top.resize(RecordsPopupCount);

                m_ui.SetRecords(top);
                m_state = GameState::GameOver;
            }

            m_enterHeld = true;
            return;
        }

        // death by self
        if (m_snake.IsSelfCollision())
        {
            m_ui.PlayCrashSound();
            const bool isHigh = m_records.IsHighScore(m_score, RecordsMaxCount);

            if (isHigh)
            {
                m_selectedYesNo = 0;
                m_nameBuffer = "XYZ";
                m_state = GameState::AskName;
            }
            else
            {
                auto top = m_records.Get();
                if (top.size() > RecordsPopupCount)
                    top.resize(RecordsPopupCount);

                m_ui.SetRecords(top);
                m_state = GameState::GameOver;
            }

            m_enterHeld = true;
            return;
        }

		//apple collision
        
        for (auto& a : m_apples)
        {
            if (a.Cell().x == h.x && a.Cell().y == h.y)
            {
                m_snake.Grow(1);
                RespawnApple(a);
                m_ui.PlayAppleEatSound();
                m_score += 1;

                if (m_difficulty == Difficulty::Hard)
                {
                    m_currentMoveInterval -= HardStep;
                    if (m_currentMoveInterval < HardMinInterval)
                        m_currentMoveInterval = HardMinInterval;

                    m_snake.SetMoveInterval(m_currentMoveInterval);
                }

                m_ui.SetScore(m_score);

                break;
            }
        }
    }

    void Game::Render()
    {
        m_window.clear();

        if (m_state == GameState::MainMenu)
        {
            m_ui.DrawMainMenu(m_window);
            m_window.display();
            return;
        }

        if (m_state == GameState::ModeSelect)
        {
            m_ui.DrawModeSelect(m_window);
            m_window.display();
            return;
        }

        if (m_state == GameState::GameOver)
        {
            m_ui.DrawGameOver(m_window);
            m_window.display();
            return;
        }

        if (m_state == GameState::AskName)
        {
            m_ui.DrawAskName(m_window);
            m_window.display();
            return;
        }

        if (m_state == GameState::NameInput)
        {
            m_ui.SetNameBuffer(m_nameBuffer);
            m_ui.DrawNameInput(m_window);
            m_window.display();
            return;
        }

        if (m_state == GameState::Records)
        {
            m_ui.DrawRecords(m_window);
            m_window.display();
            return;
        }


		//Draw background for HUD
        sf::RectangleShape hud;
        hud.setSize(sf::Vector2f((float)WindowWidth, (float)HudHeight));
        hud.setPosition(0.f, 0.f);
        hud.setFillColor(sf::Color(40, 80, 40));
        
        m_window.draw(hud);
        m_ui.DrawPlayground(m_window);
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

    void Game::StartNewGame()
    {
        m_score = 0;
        m_ui.SetScore(m_score);

        m_hardApplesEaten = 0;

        
        if (m_difficulty == Difficulty::Easy)
            m_baseMoveInterval = MoveInterval * 1.5f;   
        else
            m_baseMoveInterval = MoveInterval;          

        m_currentMoveInterval = m_baseMoveInterval;
        m_snake.SetMoveInterval(m_currentMoveInterval);


        m_snake.Init({ 10, 7 }, 4, Direction::Right);
        SpawnApples(DefaultAppleCount);
    }
}

