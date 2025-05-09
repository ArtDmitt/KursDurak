#include "../include/Game.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // Создаем игру с размером окна 800x600
        Game game(800, 600);
        
        // Запускаем игру
        game.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
        return 1;
    }
} 