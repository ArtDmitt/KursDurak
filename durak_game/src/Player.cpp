#include "../include/Player.h"
#include <algorithm>

Player::Player(const std::string& name, bool isHuman)
    : m_name(name), m_isHuman(isHuman), m_selectedCardIndex(static_cast<size_t>(-1)) {
    // Устанавливаем начальную позицию руки игрока
    m_position = sf::Vector2f(0.0f, 0.0f);
}

const std::string& Player::getName() const {
    return m_name;
}

bool Player::isHuman() const {
    return m_isHuman;
}

size_t Player::getCardCount() const {
    return m_hand.size();
}

void Player::addCard(std::shared_ptr<Card> card) {
    if (card) {
        card->setFaceUp(m_isHuman); // Показываем карты только для человека
        m_hand.push_back(card);
        arrangeCards(); // Перераспределяем карты в руке
    }
}

std::shared_ptr<Card> Player::getCard(size_t index) {
    if (index < m_hand.size()) {
        return m_hand[index];
    }
    return nullptr;
}

std::shared_ptr<Card> Player::removeCard(size_t index) {
    if (index < m_hand.size()) {
        auto card = m_hand[index];
        m_hand.erase(m_hand.begin() + index);
        
        // Если удаляемая карта была выбранной, сбрасываем выбор
        if (m_selectedCardIndex == index) {
            m_selectedCardIndex = static_cast<size_t>(-1);
        } else if (m_selectedCardIndex > index) {
            // Обновляем индекс, если удаляем карту перед выбранной
            m_selectedCardIndex--;
        }
        
        arrangeCards(); // Перераспределяем карты в руке
        return card;
    }
    return nullptr;
}

std::shared_ptr<Card> Player::removeSelectedCard() {
    if (m_selectedCardIndex != static_cast<size_t>(-1)) {
        return removeCard(m_selectedCardIndex);
    }
    return nullptr;
}

void Player::selectCard(size_t index) {
    // Снимаем выделение с предыдущей выбранной карты
    if (m_selectedCardIndex != static_cast<size_t>(-1) && m_selectedCardIndex < m_hand.size()) {
        m_hand[m_selectedCardIndex]->setSelected(false);
    }
    
    // Выделяем новую карту
    if (index < m_hand.size()) {
        m_selectedCardIndex = index;
        m_hand[index]->setSelected(true);
    } else {
        m_selectedCardIndex = static_cast<size_t>(-1);
    }
}

void Player::deselectAllCards() {
    // Снимаем выделение со всех карт
    for (auto& card : m_hand) {
        card->setSelected(false);
    }
    m_selectedCardIndex = static_cast<size_t>(-1);
}

bool Player::hasSelectedCard() const {
    return m_selectedCardIndex != static_cast<size_t>(-1);
}

std::shared_ptr<Card> Player::getSelectedCard() const {
    if (m_selectedCardIndex != static_cast<size_t>(-1) && m_selectedCardIndex < m_hand.size()) {
        return m_hand[m_selectedCardIndex];
    }
    return nullptr;
}

bool Player::hasCardToBeat(const Card& card, Suit trumpSuit) const {
    // Проверяем, есть ли в руке карта, которой можно отбиться
    for (const auto& myCard : m_hand) {
        if (myCard->canBeat(card, trumpSuit)) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Card> Player::getCardToBeat(const Card& card, Suit trumpSuit) {
    // Для компьютерного игрока - выбираем наименьшую подходящую карту
    
    std::shared_ptr<Card> bestCard = nullptr;
    size_t bestCardIndex = static_cast<size_t>(-1);
    
    for (size_t i = 0; i < m_hand.size(); ++i) {
        auto myCard = m_hand[i];
        if (myCard->canBeat(card, trumpSuit)) {
            // Если это первая подходящая карта или она меньше текущей лучшей
            if (!bestCard || 
                (myCard->getSuit() == bestCard->getSuit() && 
                 static_cast<int>(myCard->getRank()) < static_cast<int>(bestCard->getRank())) ||
                (myCard->getSuit() != trumpSuit && bestCard->getSuit() == trumpSuit)) {
                bestCard = myCard;
                bestCardIndex = i;
            }
        }
    }
    
    // Если нашли подходящую карту, выбираем её
    if (bestCard && !m_isHuman) {
        selectCard(bestCardIndex);
    }
    
    return bestCard;
}

void Player::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    arrangeCards(); // Обновляем позиции карт
}

void Player::arrangeCards() {
    if (m_hand.empty()) {
        return;
    }
    
    // Рассчитываем позиции для каждой карты
    float totalWidth = (m_hand.size() - 1) * CARD_SPACING;
    float startX = m_position.x - totalWidth / 2;
    
    for (size_t i = 0; i < m_hand.size(); ++i) {
        float x = startX + i * CARD_SPACING;
        m_hand[i]->setPosition(x, m_position.y);
    }
}

void Player::draw(sf::RenderWindow& window) {
    // Рисуем все карты в руке
    for (auto& card : m_hand) {
        card->draw(window);
    }
}

bool Player::handleCardClick(const sf::Vector2f& clickPos) {
    if (!m_isHuman) {
        return false; // Компьютерный игрок не обрабатывает клики
    }
    
    // Проверяем все карты в обратном порядке (сверху вниз)
    for (int i = static_cast<int>(m_hand.size()) - 1; i >= 0; --i) {
        if (m_hand[i]->contains(clickPos)) {
            // Если карта уже выбрана, снимаем выделение
            if (m_selectedCardIndex == static_cast<size_t>(i)) {
                deselectAllCards();
            } else {
                // Иначе выбираем карту
                selectCard(i);
            }
            return true;
        }
    }
    
    return false;
} 