#include "game.h"
#include "colors.h"
#include "fileManager.h"
#include "scoreLogger.h"
#include "window.h"
#include <fstream>
#include <iostream>
#include <ncurses.h>

using namespace std;

Game::Game(double verticalVelocity, double horizontalVelocity)
    : IDrawable(), m_target_vertical(5), m_target_horizontal(5), m_gameOver(false), m_score(0), m_keyLock(false),
      m_penetrableWalls(true), m_pace(100), m_snake(Snake(1, 1))
{
    gameOverLabel = string("* * * GAME OVER * * *");

    int settings{0};

    int mapSize{1};
    int speedSetting{1};
    int penetrableWalls;

    try
    {
        ifstream settingsFile(FileManager::getFilePath("settings"), ifstream::binary);
        settingsFile.read((char*)&settings, sizeof(int));
        settingsFile.close();

        mapSize = (settings >> 4 * 0) & 0b1111;
        speedSetting = (settings >> 4 * 1) & 0b1111;
        penetrableWalls = (settings >> 4 * 2) & 0b1111;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }

    switch (mapSize)
    {
    case 0:
        // small window
        m_playWindowHeight = 10;
        m_playWindowWidth = 30;
        break;
    case 1:
        // medium window
        m_playWindowHeight = 20;
        m_playWindowWidth = 50;
        break;
    case 2:
        // large window
        m_playWindowHeight = 30;
        m_playWindowWidth = 100;
        break;
    default:
        m_playWindowHeight = 20;
        m_playWindowWidth = 50;
        break;
    }

    switch (penetrableWalls)
    {
    case 0:
        m_penetrableWalls = true;
        break;

    case 1:
        m_penetrableWalls = false;
        break;

    default:
        m_penetrableWalls = true;
        break;
    }
    m_pace = (3 - speedSetting) * 100;

    std::random_device rd;
    m_generator = std::default_random_engine(rd());
    m_horizontalDistribution = std::uniform_int_distribution<int>(1, (m_playWindowWidth - 1));
    m_verticalDistribution = std::uniform_int_distribution<int>(1, (m_playWindowHeight - 1));
}

Game::~Game()
{
    ScoreLogger log;
    log.logScore(m_score);
}

void Game::draw(const IGraphicsEngine& engine)
{
    lock_guard<mutex> guard(m_mutex);
    drawWalls(engine);
    engine.draw(("Score: " + to_string(m_score)), m_playWindowHeight + 1, (int)m_playWindowWidth * 0.5, Color::white,
                 Color::black);
    engine.draw("X", m_target_vertical, m_target_horizontal, Color::black, Color::yellow);
    m_snake.draw(engine);

    if (m_gameOver)
    {
        engine.draw(gameOverLabel, (int)(0.5 * m_playWindowHeight),
                     (int)(0.5 * (m_playWindowWidth - gameOverLabel.size())), Color::white, Color::black);
    }
}

void Game::notify(int ch)
{
    lock_guard<mutex> guard(m_mutex);

    if (!m_keyLock)
    {
        if (ch == KEY_LEFT && m_snake.getDirection() != Direction::right)
        {
            m_snake.setDirection(Direction::left);
            m_keyLock = true;
        }
        else if (ch == KEY_RIGHT && m_snake.getDirection() != Direction::left)
        {
            m_snake.setDirection(Direction::right);
            m_keyLock = true;
        }
        else if (ch == KEY_UP && m_snake.getDirection() != Direction::down)
        {
            m_snake.setDirection(Direction::up);
            m_keyLock = true;
        }
        else if (ch == KEY_DOWN && m_snake.getDirection() != Direction::up)
        {
            m_snake.setDirection(Direction::down);
            m_keyLock = true;
        }
    }
}

void Game::update()
{
    lock_guard<mutex> guard(m_mutex);
    if (!m_gameOver)
    {

        if (m_snake.getDirection() == Direction::left || m_snake.getDirection() == Direction::right)
        {
            m_counter += 2;
        }
        else
        {
            m_counter++;
        }

        if (m_counter >= m_pace)
        {
            m_counter = 0;
            if (m_snake.getHeadYposition() == m_target_vertical && m_snake.getHeadXposition() == m_target_horizontal)
            {
                m_target_horizontal = m_horizontalDistribution(m_generator);
                m_target_vertical = m_verticalDistribution(m_generator);
                m_score++;
                m_snake.stretch();
            }
            else
            {
                m_snake.advance();
            }

            m_keyLock = false;
        }

        if (m_snake.biteItself())
        {
            m_gameOver = true;
        }

        if (m_snake.getHeadYposition() <= 0)
        {
            if (!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_snake.teleportHeadTo(m_playWindowHeight - 1, m_snake.getHeadXposition());
            }
        }
        else if (m_snake.getHeadYposition() >= m_playWindowHeight)
        {
            if (!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_snake.teleportHeadTo(1, m_snake.getHeadXposition());
            }
        }

        if (m_snake.getHeadXposition() <= 0)
        {
            if (!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_snake.teleportHeadTo(m_snake.getHeadYposition(), m_playWindowWidth - 1);
            }
        }
        else if (m_snake.getHeadXposition() >= m_playWindowWidth)
        {
            if (!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_snake.teleportHeadTo(m_snake.getHeadYposition(), 1);
            }
        }
    }
}

void Game::drawWalls(const IGraphicsEngine& engine)
{
    for (int i = 0; i <= m_playWindowWidth; i++)
    {
        engine.draw(" ", 0, i, Color::red, Color::white);
        engine.draw(" ", m_playWindowHeight, i, Color::red, Color::white);
    }

    for (int i = 0; i <= m_playWindowHeight; i++)
    {
        engine.draw(" ", i, 0, Color::red, Color::white);
        engine.draw(" ", i, m_playWindowWidth, Color::red, Color::white);
    }
}
