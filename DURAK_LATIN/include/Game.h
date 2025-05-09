#pragma once

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Состояния игры
enum class GameState {
    MENU,
    DEALING,
    PLAYER_TURN,
    OPPONENT_TURN,
    PLAYER_DEFENSE,
    OPPONENT_DEFENSE,
    GAME_OVER
};

class Game {
public:
    // Конструктор
    Game(unsigned int width, unsigned int height);
    
    // Запуск игры
    void run();
    
private:
    // Инициализация игры
    void initialize();
    
    // Обновление игрового состояния
    void update(float deltaTime);
    
    // Обработка событий
    void processEvents();
    
    // Отрисовка игры
    void render();
    
    // Обработка клика мыши
    void handleMouseClick(sf::Vector2f clickPos);
    
    // Методы обработки различных состояний игры
    void updateMenu();
    void updateDealing();
    void updatePlayerTurn();
    void updateOpponentTurn();
    void updatePlayerDefense();
    void updateOpponentDefense();
    void updateGameOver();
    
    // Раздача карт
    void dealCards();
    
    // Ход ИИ противника
    void makeOpponentMove();
    
    // Проверка условий окончания игры
    bool checkGameOver();
    
    // Определение победителя
    void determineWinner();
    
    // Перезапуск игры
    void restartGame();
    
    // Загрузка ресурсов
    void loadResources();
    
private:
    // Окно SFML
    sf::RenderWindow m_window;
    
    // Размеры окна
    unsigned int m_width;
    unsigned int m_height;
    
    // Игровые объекты
    Deck m_deck;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Player> m_opponent;
    
    // Атаки и защиты на столе
    std::vector<std::shared_ptr<Card>> m_attackCards;
    std::vector<std::shared_ptr<Card>> m_defenseCards;
    
    // Текущее состояние игры
    GameState m_gameState;
    
    // Кто сейчас ходит
    bool m_playerTurn;
    
    // Текстовые элементы
    sf::Font m_font;
    sf::Text m_statusText;
    sf::Text m_deckCountText;
    sf::Text m_trumpText;
    
    // Кнопки
    sf::RectangleShape m_passButton;
    sf::Text m_passButtonText;
    
    sf::RectangleShape m_takeButton;
    sf::Text m_takeButtonText;
    
    // Время с начала хода
    float m_turnTimer;
    
    // Константы
    static constexpr int INITIAL_CARDS = 6;
    static constexpr float AI_TURN_DELAY = 1.0f;
    static constexpr float CARD_DEAL_DELAY = 0.2f;
}; 