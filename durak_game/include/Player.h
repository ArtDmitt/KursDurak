#pragma once

#include "Card.h"
#include <vector>
#include <memory>
#include <string>

class Player {
public:
    // Конструктор
    Player(const std::string& name, bool isHuman = true);
    
    // Геттеры
    const std::string& getName() const;
    bool isHuman() const;
    size_t getCardCount() const;
    
    // Добавление карты в руку
    void addCard(std::shared_ptr<Card> card);
    
    // Получение карты из руки
    std::shared_ptr<Card> getCard(size_t index);
    
    // Удаление карты из руки
    std::shared_ptr<Card> removeCard(size_t index);
    std::shared_ptr<Card> removeSelectedCard();
    
    // Работа с выбранной картой
    void selectCard(size_t index);
    void deselectAllCards();
    bool hasSelectedCard() const;
    std::shared_ptr<Card> getSelectedCard() const;
    
    // Проверка, есть ли карты для отбивания
    bool hasCardToBeat(const Card& card, Suit trumpSuit) const;
    std::shared_ptr<Card> getCardToBeat(const Card& card, Suit trumpSuit);
    
    // Отрисовка руки игрока
    void setPosition(float x, float y);
    void arrangeCards();
    void draw(sf::RenderWindow& window);
    
    // Проверка клика на карты
    bool handleCardClick(const sf::Vector2f& clickPos);
    
private:
    std::string m_name;
    bool m_isHuman;
    std::vector<std::shared_ptr<Card>> m_hand;
    size_t m_selectedCardIndex;
    
    // Позиция руки игрока на экране
    sf::Vector2f m_position;
    
    // Расстояние между картами в руке
    static constexpr float CARD_SPACING = 30.0f;
}; 