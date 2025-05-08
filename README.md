# Карточная игра "Дурак" 🃏

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++: 17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/std/the-standard)
[![SFML: 2.5](https://img.shields.io/badge/SFML-2.5-green.svg)](https://www.sfml-dev.org/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()

Курсовая работа по разработке карточной игры "Дурак" на C++ с использованием SFML.

![Превью игры](https://i.imgur.com/example.png)

## 📋 Описание

Данный проект представляет собой реализацию классической карточной игры "Дурак" с графическим интерфейсом. Игра поддерживает режим игры против компьютера с интуитивно понятным интерфейсом и полной реализацией правил игры.

### 🌟 Основные функции

- Полная реализация правил игры "Дурак"
- Современный графический интерфейс на основе SFML
- Игра против компьютерного оппонента с базовым ИИ
- Визуальное отображение карт, колоды и игрового процесса
- Анимации перемещения карт и игровых действий
- Настраиваемые параметры игры

## 🔧 Требования

- C++17 или выше
- CMake 3.14 или выше
- SFML 2.5 или выше
- Windows, Linux или macOS

## 📁 Структура проекта

```
durak_game/
├── assets/
│   ├── cards/        # Изображения карт
│   └── fonts/        # Шрифты
├── include/          # Заголовочные файлы
├── src/              # Исходный код
├── tests/            # Тесты
├── external/         # Внешние зависимости (SFML)
├── build.ps1         # Скрипт сборки проекта
├── download_sfml.ps1 # Скрипт для скачивания SFML
├── generate_test_cards.ps1 # Скрипт для генерации тестовых карт
└── CMakeLists.txt    # Файл сборки CMake
```

## 🚀 Быстрый старт

### Windows

1. Клонируйте репозиторий:
```bash
git clone https://github.com/ArtDmitt/durak-card-game.git
cd durak-card-game
```

2. Запустите скрипт сборки, который автоматически скачает SFML и соберет проект:
```powershell
.\build.ps1
```

3. Для генерации тестовых изображений карт (требуется ImageMagick):
```powershell
.\generate_test_cards.ps1
```

4. После успешной сборки запустите игру:
```powershell
.\build\bin\Release\durak_game.exe
```

### Linux/macOS

1. Установите зависимости:
```bash
# Ubuntu
sudo apt-get install libsfml-dev cmake g++

# macOS
brew install sfml cmake
```

2. Клонируйте репозиторий и соберите проект:
```bash
git clone https://github.com/ArtDmitt/durak-card-game.git
cd durak-card-game
mkdir build && cd build
cmake ..
make
```

3. Запустите игру:
```bash
./bin/durak_game
```

## 🔄 Ручная сборка (Windows)

1. Установите SFML:
   - Скачайте библиотеку SFML с официального сайта: https://www.sfml-dev.org/download.php
   - Распакуйте архив в удобное место
   - Добавьте путь к библиотеке в переменную окружения PATH или используйте скрипт `download_sfml.ps1`

2. Сборка с использованием CMake:
```bash
mkdir build
cd build
cmake .. -DSFML_DIR=путь/к/SFML/lib/cmake/SFML
cmake --build . --config Release
```

## 🎨 Подготовка изображений карт

Для работы игры необходимы изображения карт. Вы можете:
1. Использовать готовые изображения карт, поместив их в директорию `assets/cards`
2. Создать свои изображения карт согласно требованиям в `assets/cards/README.md`
3. Сгенерировать тестовые изображения с помощью скрипта `generate_test_cards.ps1` (требуется ImageMagick)

Имена файлов должны соответствовать формату: `[масть]_[ранг].png`, например:
- `hearts_6.png`
- `diamonds_ace.png`
- `clubs_king.png`

Также необходимо создать изображение рубашки карты: `back.png`

## 📖 Правила игры

1. В начале игры каждому игроку раздается по 6 карт.
2. Последняя карта колоды определяет козырную масть.
3. Игрок с наименьшим козырем начинает игру.
4. Игрок может атаковать, а оппонент должен отбиваться.
5. Карты отбиваются старшими картами той же масти или козырями.
6. Если игрок не может отбиться, он берет все карты со стола.
7. После каждого хода игроки добирают карты из колоды до 6 штук.
8. Игра продолжается, пока один из игроков не избавится от всех карт.
9. Последний игрок, оставшийся с картами, считается проигравшим.

## 📸 Скриншоты

<div align="center">
  <img src="https://i.imgur.com/example1.png" width="400" alt="Игровой процесс">
  <img src="https://i.imgur.com/example2.png" width="400" alt="Меню игры">
</div>

## 📚 Документация

- [ARCHITECTURE.md](ARCHITECTURE.md) - Описание архитектуры проекта
- [DEVELOPMENT.md](DEVELOPMENT.md) - Описание процесса разработки
- [CHANGELOG.md](CHANGELOG.md) - История изменений проекта
- [assets/cards/README.md](assets/cards/README.md) - Требования к изображениям карт

## 🛠️ Планы развития

- Добавление сетевой игры
- Улучшение ИИ противника
- Добавление различных уровней сложности
- Реализация анимаций и звуковых эффектов
- Создание мобильной версии

## 🤝 Вклад в проект

Вклады в проект приветствуются! Если вы хотите внести свой вклад:

1. Форкните репозиторий
2. Создайте ветку для своей функции (`git checkout -b feature/amazing-feature`)
3. Зафиксируйте свои изменения (`git commit -m 'Добавлена удивительная функция'`)
4. Отправьте ветку (`git push origin feature/amazing-feature`)
5. Откройте Pull Request

## 👨‍💻 Автор

Артём - [GitHub](https://github.com/ваш-логин)

## 📄 Лицензия

Этот проект распространяется под лицензией MIT. См. файл [LICENSE](LICENSE) для получения дополнительной информации.

## 📊 Статистика проекта

![GitHub stars](https://img.shields.io/github/stars/ваш-логин/durak-card-game?style=social)
![GitHub forks](https://img.shields.io/github/forks/ваш-логин/durak-card-game?style=social)
![GitHub issues](https://img.shields.io/github/issues/ваш-логин/durak-card-game) 
