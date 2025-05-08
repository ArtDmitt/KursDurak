cmake_minimum_required(VERSION 3.14)
project(DurakGame VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для указания пути к SFML
set(SFML_DIR "" CACHE PATH "Путь к директории с SFML")

# Поиск SFML пакетов
if(SFML_DIR)
    # Если путь указан, используем его
    set(CMAKE_PREFIX_PATH ${SFML_DIR})
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
else()
    # Пробуем найти SFML в стандартных местах
    find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
    
    # Если не нашли, используем встроенную версию
    if(NOT SFML_FOUND)
        message(STATUS "SFML не найден. Скачайте SFML с https://www.sfml-dev.org/download.php")
        message(STATUS "После скачивания укажите путь к SFML с помощью -DSFML_DIR=путь/к/SFML/lib/cmake/SFML")
        message(FATAL_ERROR "SFML не найден.")
    endif()
endif()

# Включаем директории заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Добавляем подпроекты
add_subdirectory(src)

# Опция сборки тестов (по умолчанию отключена)
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Копирование ресурсов
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}) 