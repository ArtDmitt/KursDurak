#include "../include/Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck() : m_trumpSuit(Suit::HEARTS) {
    // Инициализируем генератор случайных чисел
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_rng.seed(seed);
    
    // Устанавливаем начальную позицию колоды
    m_position = sf::Vector2f(0.0f, 0.0f);
}

void Deck::initialize() {
    // Очищаем старую колоду
    m_cards.clear();
    
    // Создаем новую колоду из 36 карт (от 6 до туза в каждой масти)
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 6; rank <= 14; ++rank) {
            auto card = std::make_shared<Card>(
                static_cast<Suit>(suit),
                static_cast<Rank>(rank)
            );
            m_cards.push_back(card);
        }
    }
    
    // Перемешиваем колоду
    shuffle();
    
    // Устанавливаем козырную карту
    if (!m_cards.empty()) {
        m_trumpCard = m_cards.back();
        m_trumpSuit = m_trumpCard->getSuit();
        m_trumpCard->setFaceUp(true);
    }
}

void Deck::shuffle() {
    std::shuffle(m_cards.begin(), m_cards.end(), m_rng);
}

std::shared_ptr<Card> Deck::drawCard() {
    if (m_cards.empty()) {
        return nullptr;
    }
    
    // Берем карту с верха колоды
    auto card = m_cards.front();
    m_cards.erase(m_cards.begin());
    
    return card;
}

Suit Deck::getTrumpSuit() const {
    return m_trumpSuit;
}

bool Deck::isEmpty() const {
    return m_cards.empty();
}

size_t Deck::getCardCount() const {
    return m_cards.size();
}

void Deck::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    
    // Обновляем позицию отображения колоды
    m_backSprite.setPosition(x, y);
    
    // Обновляем позицию козырной карты
    if (m_trumpCard) {
        m_trumpCard->setPosition(x + 20.0f, y + 30.0f);  // Смещаем козырную карту немного вправо и вниз
    }
}

void Deck::draw(sf::RenderWindow& window) {
    // Рисуем рубашку колоды, если есть карты
    if (!m_cards.empty()) {
        window.draw(m_backSprite);
    }
    
    // Рисуем козырную карту, если она есть
    if (m_trumpCard && !m_cards.empty()) {
        m_trumpCard->draw(window);
    }
}

void Deck::loadTextures(const std::string& cardsDirectory) {
    // Загружаем текстуру рубашки карты
    std::string backTexturePath = cardsDirectory + "/back.png";
    if (!m_backTexture.loadFromFile(backTexturePath)) {
        std::cerr << "Ошибка при загрузке текстуры рубашки карты: " << backTexturePath << std::endl;
        return;
    }
    
    m_backSprite.setTexture(m_backTexture);
    m_backSprite.setPosition(m_position);
    
    // Загружаем текстуры для всех карт в колоде
    for (auto& card : m_cards) {
        std::string cardTexturePath = cardsDirectory + "/" + 
            Card::getCardFileName(card->getSuit(), card->getRank());
        card->loadTexture(cardTexturePath);
    }
    
    // Загружаем текстуру для козырной карты, если она есть
    if (m_trumpCard) {
        std::string trumpTexturePath = cardsDirectory + "/" + 
            Card::getCardFileName(m_trumpCard->getSuit(), m_trumpCard->getRank());
        m_trumpCard->loadTexture(trumpTexturePath);
    }
} 