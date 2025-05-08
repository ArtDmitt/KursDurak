#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// Перечисления для мастей и рангов карт
enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Rank {
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

class Card {
public:
    // Конструкторы
    Card(Suit suit, Rank rank);
    Card(const Card& other);
    
    // Геттеры
    Suit getSuit() const;
    Rank getRank() const;
    bool isFaceUp() const;
    bool isSelected() const;
    
    // Сеттеры
    void setFaceUp(bool faceUp);
    void setSelected(bool selected);
    
    // Отрисовка
    void loadTexture(const std::string& filepath);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    
    // Проверка клика на карту
    bool contains(const sf::Vector2f& point) const;
    
    // Сравнение карт
    bool canBeat(const Card& other, Suit trumpSuit) const;
    
    // Получение имени файла для карты
    static std::string getCardFileName(Suit suit, Rank rank);
    
    // Преобразование enum в строку
    static std::string suitToString(Suit suit);
    static std::string rankToString(Rank rank);
    
private:
    Suit m_suit;
    Rank m_rank;
    bool m_faceUp;
    bool m_selected;
    
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    
    // Размер карты
    static constexpr float CARD_WIDTH = 100.0f;
    static constexpr float CARD_HEIGHT = 150.0f;
}; 