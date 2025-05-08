#include "../include/Card.h"
#include <iostream>

Card::Card(Suit suit, Rank rank)
    : m_suit(suit), m_rank(rank), m_faceUp(false), m_selected(false) {
    // По умолчанию карта рубашкой вверх и не выбрана
}

Card::Card(const Card& other)
    : m_suit(other.m_suit), m_rank(other.m_rank), m_faceUp(other.m_faceUp), m_selected(other.m_selected) {
    // Копируем текстуру и спрайт
    if (other.m_texture.getSize().x > 0) {
        m_texture = other.m_texture;
        m_sprite = other.m_sprite;
        m_sprite.setTexture(m_texture);
    }
}

Suit Card::getSuit() const {
    return m_suit;
}

Rank Card::getRank() const {
    return m_rank;
}

bool Card::isFaceUp() const {
    return m_faceUp;
}

bool Card::isSelected() const {
    return m_selected;
}

void Card::setFaceUp(bool faceUp) {
    m_faceUp = faceUp;
}

void Card::setSelected(bool selected) {
    m_selected = selected;
    
    // Визуальное выделение карты
    if (selected) {
        m_sprite.setColor(sf::Color(255, 255, 255, 255)); // Полная непрозрачность
        m_sprite.setScale(1.1f, 1.1f); // Увеличение размера
    } else {
        m_sprite.setColor(sf::Color(255, 255, 255, 220)); // Легкая прозрачность
        m_sprite.setScale(1.0f, 1.0f); // Нормальный размер
    }
}

void Card::loadTexture(const std::string& filepath) {
    if (!m_texture.loadFromFile(filepath)) {
        std::cerr << "Ошибка загрузки текстуры карты: " << filepath << std::endl;
        return;
    }
    
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(CARD_WIDTH / 2, CARD_HEIGHT / 2);
    m_sprite.setScale(1.0f, 1.0f);
}

void Card::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void Card::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

bool Card::contains(const sf::Vector2f& point) const {
    return m_sprite.getGlobalBounds().contains(point);
}

bool Card::canBeat(const Card& other, Suit trumpSuit) const {
    // Если масти совпадают, то старшая карта бьет младшую
    if (m_suit == other.m_suit) {
        return static_cast<int>(m_rank) > static_cast<int>(other.m_rank);
    }
    
    // Если это козырь, а атакующая карта не козырь, то можно бить
    if (m_suit == trumpSuit && other.m_suit != trumpSuit) {
        return true;
    }
    
    // В других случаях бить нельзя
    return false;
}

std::string Card::getCardFileName(Suit suit, Rank rank) {
    return suitToString(suit) + "_" + rankToString(rank) + ".png";
}

std::string Card::suitToString(Suit suit) {
    switch (suit) {
        case Suit::HEARTS: return "hearts";
        case Suit::DIAMONDS: return "diamonds";
        case Suit::CLUBS: return "clubs";
        case Suit::SPADES: return "spades";
        default: return "unknown";
    }
}

std::string Card::rankToString(Rank rank) {
    switch (rank) {
        case Rank::SIX: return "6";
        case Rank::SEVEN: return "7";
        case Rank::EIGHT: return "8";
        case Rank::NINE: return "9";
        case Rank::TEN: return "10";
        case Rank::JACK: return "jack";
        case Rank::QUEEN: return "queen";
        case Rank::KING: return "king";
        case Rank::ACE: return "ace";
        default: return "unknown";
    }
} 