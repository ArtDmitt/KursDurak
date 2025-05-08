#pragma once

#include "Card.h"
#include <vector>
#include <memory>
#include <random>

class Deck {
public:
    // Конструктор
    Deck();
    
    // Инициализация колоды
    void initialize();
    
    // Перемешивание колоды
    void shuffle();
    
    // Взять карту из колоды
    std::shared_ptr<Card> drawCard();
    
    // Получить козырную масть
    Suit getTrumpSuit() const;
    
    // Проверка, пуста ли колода
    bool isEmpty() const;
    
    // Получение количества карт в колоде
    size_t getCardCount() const;
    
    // Отрисовка колоды и козырной карты
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    
    // Загрузка текстур
    void loadTextures(const std::string& cardsDirectory);
    
private:
    std::vector<std::shared_ptr<Card>> m_cards;
    std::shared_ptr<Card> m_trumpCard;
    Suit m_trumpSuit;
    
    sf::Texture m_backTexture;
    sf::Sprite m_backSprite;
    
    std::mt19937 m_rng;  // Генератор случайных чисел
    
    // Позиция колоды на экране
    sf::Vector2f m_position;
}; 