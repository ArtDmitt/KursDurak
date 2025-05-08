#include "../include/Game.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_gameState(GameState::MENU), 
      m_playerTurn(true), m_turnTimer(0.0f) {
    
    // Создаем окно SFML
    m_window.create(sf::VideoMode(width, height), "Карточная игра Дурак");
    m_window.setFramerateLimit(60);
    
    // Инициализируем игровые объекты
    initialize();
}

void Game::initialize() {
    // Загружаем ресурсы
    loadResources();
    
    // Создаем колоду
    m_deck.initialize();
    m_deck.setPosition(m_width / 2 - 150, m_height / 2);
    
    // Создаем игроков
    m_player = std::make_shared<Player>("Игрок", true);
    m_player->setPosition(m_width / 2, m_height - 100);
    
    m_opponent = std::make_shared<Player>("Компьютер", false);
    m_opponent->setPosition(m_width / 2, 100);
    
    // Очищаем карты на столе
    m_attackCards.clear();
    m_defenseCards.clear();
    
    // Устанавливаем начальное состояние игры
    m_gameState = GameState::DEALING;
    m_playerTurn = true;
    m_turnTimer = 0.0f;
    
    // Настраиваем текст статуса
    m_statusText.setFont(m_font);
    m_statusText.setCharacterSize(24);
    m_statusText.setFillColor(sf::Color::White);
    m_statusText.setPosition(20, 20);
    m_statusText.setString("Игра началась! Раздаем карты...");
    
    // Настраиваем текст количества карт в колоде
    m_deckCountText.setFont(m_font);
    m_deckCountText.setCharacterSize(18);
    m_deckCountText.setFillColor(sf::Color::White);
    m_deckCountText.setPosition(m_width / 2 - 150, m_height / 2 + 80);
    
    // Настраиваем текст козыря
    m_trumpText.setFont(m_font);
    m_trumpText.setCharacterSize(18);
    m_trumpText.setFillColor(sf::Color::Yellow);
    m_trumpText.setPosition(m_width / 2 - 150, m_height / 2 + 110);
    
    // Настраиваем кнопку "Пас"
    m_passButton.setSize(sf::Vector2f(100, 40));
    m_passButton.setFillColor(sf::Color(50, 150, 50));
    m_passButton.setPosition(m_width - 120, m_height - 60);
    
    m_passButtonText.setFont(m_font);
    m_passButtonText.setString("Пас");
    m_passButtonText.setCharacterSize(20);
    m_passButtonText.setFillColor(sf::Color::White);
    m_passButtonText.setPosition(m_width - 90, m_height - 55);
    
    // Настраиваем кнопку "Взять"
    m_takeButton.setSize(sf::Vector2f(100, 40));
    m_takeButton.setFillColor(sf::Color(150, 50, 50));
    m_takeButton.setPosition(m_width - 230, m_height - 60);
    
    m_takeButtonText.setFont(m_font);
    m_takeButtonText.setString("Взять");
    m_takeButtonText.setCharacterSize(20);
    m_takeButtonText.setFillColor(sf::Color::White);
    m_takeButtonText.setPosition(m_width - 210, m_height - 55);
}

void Game::run() {
    sf::Clock clock;
    
    while (m_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), 
                                     static_cast<float>(event.mouseButton.y));
                handleMouseClick(mousePos);
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Обновляем таймер хода
    m_turnTimer += deltaTime;
    
    // Обновляем текст количества карт в колоде
    m_deckCountText.setString("В колоде: " + std::to_string(m_deck.getCardCount()) + " карт");
    
    // Обновляем текст козыря
    std::string trumpSuitStr;
    switch (m_deck.getTrumpSuit()) {
        case Suit::HEARTS: trumpSuitStr = "Червы"; break;
        case Suit::DIAMONDS: trumpSuitStr = "Бубны"; break;
        case Suit::CLUBS: trumpSuitStr = "Трефы"; break;
        case Suit::SPADES: trumpSuitStr = "Пики"; break;
    }
    m_trumpText.setString("Козырь: " + trumpSuitStr);
    
    // Обрабатываем текущее состояние игры
    switch (m_gameState) {
        case GameState::MENU:
            updateMenu();
            break;
        case GameState::DEALING:
            updateDealing();
            break;
        case GameState::PLAYER_TURN:
            updatePlayerTurn();
            break;
        case GameState::OPPONENT_TURN:
            updateOpponentTurn();
            break;
        case GameState::PLAYER_DEFENSE:
            updatePlayerDefense();
            break;
        case GameState::OPPONENT_DEFENSE:
            updateOpponentDefense();
            break;
        case GameState::GAME_OVER:
            updateGameOver();
            break;
    }
    
    // Проверяем условия окончания игры
    if (m_gameState != GameState::GAME_OVER && checkGameOver()) {
        determineWinner();
        m_gameState = GameState::GAME_OVER;
    }
}

void Game::render() {
    m_window.clear(sf::Color(0, 100, 0)); // Зеленый фон игрового стола
    
    // Рисуем колоду
    m_deck.draw(m_window);
    
    // Рисуем карты на столе
    for (size_t i = 0; i < m_attackCards.size(); ++i) {
        m_attackCards[i]->draw(m_window);
        
        // Рисуем соответствующую карту защиты, если она есть
        if (i < m_defenseCards.size() && m_defenseCards[i]) {
            m_defenseCards[i]->draw(m_window);
        }
    }
    
    // Рисуем руки игроков
    m_player->draw(m_window);
    m_opponent->draw(m_window);
    
    // Рисуем текстовые элементы
    m_window.draw(m_statusText);
    m_window.draw(m_deckCountText);
    m_window.draw(m_trumpText);
    
    // Рисуем кнопки в зависимости от состояния игры
    if (m_gameState == GameState::PLAYER_TURN || m_gameState == GameState::PLAYER_DEFENSE) {
        if (m_gameState == GameState::PLAYER_DEFENSE) {
            m_window.draw(m_takeButton);
            m_window.draw(m_takeButtonText);
        }
        
        if (!m_attackCards.empty() || m_gameState == GameState::PLAYER_DEFENSE) {
            m_window.draw(m_passButton);
            m_window.draw(m_passButtonText);
        }
    }
    
    m_window.display();
}

void Game::handleMouseClick(sf::Vector2f clickPos) {
    // Обработка кликов по картам игрока
    if (m_gameState == GameState::PLAYER_TURN || m_gameState == GameState::PLAYER_DEFENSE) {
        if (m_player->handleCardClick(clickPos)) {
            // Если игрок выбрал карту
            if (m_player->hasSelectedCard()) {
                if (m_gameState == GameState::PLAYER_TURN) {
                    // Игрок атакует
                    auto selectedCard = m_player->removeSelectedCard();
                    m_attackCards.push_back(selectedCard);
                    selectedCard->setPosition(m_width / 2 - 50 + m_attackCards.size() * 30, m_height / 2 - 30);
                    
                    // Переходим к защите оппонента
                    m_gameState = GameState::OPPONENT_DEFENSE;
                    m_statusText.setString("Компьютер отбивается...");
                    m_turnTimer = 0.0f;
                } else if (m_gameState == GameState::PLAYER_DEFENSE) {
                    // Игрок защищается
                    auto selectedCard = m_player->getSelectedCard();
                    
                    // Проверяем, может ли выбранная карта побить последнюю атакующую карту
                    if (!m_attackCards.empty() && m_defenseCards.size() < m_attackCards.size()) {
                        auto attackCard = m_attackCards[m_defenseCards.size()];
                        if (selectedCard->canBeat(*attackCard, m_deck.getTrumpSuit())) {
                            // Успешная защита
                            selectedCard = m_player->removeSelectedCard();
                            m_defenseCards.push_back(selectedCard);
                            selectedCard->setPosition(m_width / 2 - 30 + m_defenseCards.size() * 30, m_height / 2);
                            
                            // Если отбились от всех карт, переходим к ходу игрока
                            if (m_defenseCards.size() == m_attackCards.size()) {
                                // Очищаем стол
                                m_attackCards.clear();
                                m_defenseCards.clear();
                                
                                // Добираем карты
                                dealCards();
                                
                                // Переходим к ходу игрока
                                m_gameState = GameState::PLAYER_TURN;
                                m_statusText.setString("Ваш ход!");
                            }
                        }
                    }
                }
            }
            return;
        }
    }
    
    // Обработка кликов по кнопкам
    if (m_passButton.getGlobalBounds().contains(clickPos)) {
        if (m_gameState == GameState::PLAYER_TURN && !m_attackCards.empty()) {
            // Игрок закончил атаку
            // Очищаем стол
            m_attackCards.clear();
            m_defenseCards.clear();
            
            // Добираем карты
            dealCards();
            
            // Переходим к ходу оппонента
            m_gameState = GameState::OPPONENT_TURN;
            m_statusText.setString("Ход компьютера...");
            m_turnTimer = 0.0f;
        } else if (m_gameState == GameState::PLAYER_DEFENSE) {
            // Игрок успешно отбился
            if (m_defenseCards.size() == m_attackCards.size()) {
                // Очищаем стол
                m_attackCards.clear();
                m_defenseCards.clear();
                
                // Добираем карты
                dealCards();
                
                // Переходим к ходу игрока
                m_gameState = GameState::PLAYER_TURN;
                m_statusText.setString("Ваш ход!");
            }
        }
    } else if (m_takeButton.getGlobalBounds().contains(clickPos)) {
        if (m_gameState == GameState::PLAYER_DEFENSE) {
            // Игрок берет карты
            for (auto& card : m_attackCards) {
                m_player->addCard(card);
            }
            for (auto& card : m_defenseCards) {
                if (card) {
                    m_player->addCard(card);
                }
            }
            
            // Очищаем стол
            m_attackCards.clear();
            m_defenseCards.clear();
            
            // Добираем карты
            dealCards();
            
            // Переходим к ходу оппонента
            m_gameState = GameState::OPPONENT_TURN;
            m_statusText.setString("Ход компьютера...");
            m_turnTimer = 0.0f;
        }
    }
}

void Game::updateMenu() {
    // В будущем здесь будет логика меню
    m_gameState = GameState::DEALING;
}

void Game::updateDealing() {
    // Раздаем карты игрокам
    dealCards();
    
    // Переходим к ходу игрока
    m_gameState = GameState::PLAYER_TURN;
    m_statusText.setString("Ваш ход!");
}

void Game::updatePlayerTurn() {
    // Ожидаем действий игрока
    // Логика обрабатывается в handleMouseClick
}

void Game::updateOpponentTurn() {
    // Добавляем небольшую задержку для имитации размышления компьютера
    if (m_turnTimer < AI_TURN_DELAY) {
        return;
    }
    
    // Компьютер делает ход
    makeOpponentMove();
    
    // Переходим к защите игрока
    if (!m_attackCards.empty()) {
        m_gameState = GameState::PLAYER_DEFENSE;
        m_statusText.setString("Ваша защита!");
    } else {
        // Если компьютер не смог сделать ход, переходим к ходу игрока
        m_gameState = GameState::PLAYER_TURN;
        m_statusText.setString("Ваш ход!");
    }
    
    m_turnTimer = 0.0f;
}

void Game::updatePlayerDefense() {
    // Ожидаем действий игрока
    // Логика обрабатывается в handleMouseClick
}

void Game::updateOpponentDefense() {
    // Добавляем небольшую задержку для имитации размышления компьютера
    if (m_turnTimer < AI_TURN_DELAY) {
        return;
    }
    
    // Проверяем, может ли компьютер отбиться
    if (!m_attackCards.empty() && m_defenseCards.size() < m_attackCards.size()) {
        auto attackCard = m_attackCards[m_defenseCards.size()];
        
        // Ищем подходящую карту для защиты
        auto defenseCard = m_opponent->getCardToBeat(*attackCard, m_deck.getTrumpSuit());
        
        if (defenseCard) {
            // Компьютер отбивается
            defenseCard = m_opponent->removeSelectedCard();
            m_defenseCards.push_back(defenseCard);
            defenseCard->setPosition(m_width / 2 - 30 + m_defenseCards.size() * 30, m_height / 2);
            
            // Если отбился от всех карт
            if (m_defenseCards.size() == m_attackCards.size()) {
                // Очищаем стол
                m_attackCards.clear();
                m_defenseCards.clear();
                
                // Добираем карты
                dealCards();
                
                // Переходим к ходу оппонента
                m_gameState = GameState::OPPONENT_TURN;
                m_statusText.setString("Ход компьютера...");
            } else {
                // Ждем следующей атаки игрока
                m_gameState = GameState::PLAYER_TURN;
                m_statusText.setString("Ваш ход! Можете подкинуть карту.");
            }
        } else {
            // Компьютер берет карты
            for (auto& card : m_attackCards) {
                m_opponent->addCard(card);
            }
            for (auto& card : m_defenseCards) {
                if (card) {
                    m_opponent->addCard(card);
                }
            }
            
            // Очищаем стол
            m_attackCards.clear();
            m_defenseCards.clear();
            
            // Добираем карты
            dealCards();
            
            // Переходим к ходу игрока
            m_gameState = GameState::PLAYER_TURN;
            m_statusText.setString("Ваш ход!");
        }
    }
    
    m_turnTimer = 0.0f;
}

void Game::updateGameOver() {
    // Ожидаем действий игрока для перезапуска игры
    // В будущем здесь будет логика окончания игры
}

void Game::dealCards() {
    // Раздаем карты игрокам до 6 штук, начиная с игрока
    while (!m_deck.isEmpty() && (m_player->getCardCount() < INITIAL_CARDS || m_opponent->getCardCount() < INITIAL_CARDS)) {
        // Сначала игрок берет карты
        if (m_player->getCardCount() < INITIAL_CARDS) {
            auto card = m_deck.drawCard();
            if (card) {
                card->setFaceUp(true);
                m_player->addCard(card);
            }
        }
        
        // Затем компьютер берет карты
        if (m_opponent->getCardCount() < INITIAL_CARDS) {
            auto card = m_deck.drawCard();
            if (card) {
                card->setFaceUp(false);  // Карты компьютера не видны игроку
                m_opponent->addCard(card);
            }
        }
    }
}

void Game::makeOpponentMove() {
    // Простая стратегия: компьютер ходит наименьшей картой
    if (m_opponent->getCardCount() == 0) {
        return;
    }
    
    // Находим наименьшую карту
    size_t minCardIndex = 0;
    int minRank = 15;  // Больше любого возможного ранга
    
    for (size_t i = 0; i < m_opponent->getCardCount(); ++i) {
        auto card = m_opponent->getCard(i);
        int rank = static_cast<int>(card->getRank());
        
        // Если это не козырь или все карты козыри
        if (card->getSuit() != m_deck.getTrumpSuit() || minRank == 15) {
            if (rank < minRank) {
                minRank = rank;
                minCardIndex = i;
            }
        }
    }
    
    // Ходим выбранной картой
    m_opponent->selectCard(minCardIndex);
    auto selectedCard = m_opponent->removeSelectedCard();
    
    if (selectedCard) {
        selectedCard->setFaceUp(true);  // Показываем карту
        m_attackCards.push_back(selectedCard);
        selectedCard->setPosition(m_width / 2 - 50 + m_attackCards.size() * 30, m_height / 2 - 30);
    }
}

bool Game::checkGameOver() {
    // Проверяем условия окончания игры
    
    // Если колода пуста и у одного из игроков нет карт
    if (m_deck.isEmpty() && (m_player->getCardCount() == 0 || m_opponent->getCardCount() == 0)) {
        return true;
    }
    
    return false;
}

void Game::determineWinner() {
    // Определяем победителя
    if (m_player->getCardCount() == 0 && m_opponent->getCardCount() > 0) {
        m_statusText.setString("Вы выиграли! Поздравляем!");
    } else if (m_opponent->getCardCount() == 0 && m_player->getCardCount() > 0) {
        m_statusText.setString("Компьютер выиграл. Попробуйте еще раз!");
    } else {
        m_statusText.setString("Ничья!");
    }
}

void Game::restartGame() {
    // Перезапускаем игру
    initialize();
}

void Game::loadResources() {
    // Загружаем шрифт
    bool fontLoaded = false;
    
    // Пробуем загрузить шрифт из разных мест
    const std::vector<std::string> fontPaths = {
        "assets/fonts/arial.ttf",
        "../assets/fonts/arial.ttf",
        "assets/fonts/Arial.ttf",
        "../assets/fonts/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/Arial.ttf"
    };
    
    for (const auto& path : fontPaths) {
        if (m_font.loadFromFile(path)) {
            std::cout << "Шрифт загружен из: " << path << std::endl;
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cerr << "Ошибка при загрузке шрифта! Используем встроенный шрифт." << std::endl;
        // Если не удалось загрузить шрифт, создаем простой шрифт
        sf::Font defaultFont;
        m_font = defaultFont;
    }
    
    // Загружаем текстуры карт
    m_deck.loadTextures("assets/cards");
} 