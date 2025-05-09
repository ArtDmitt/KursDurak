cmake_minimum_required(VERSION 3.14)
project(DurakGame VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Явно указываем пути к заголовочным файлам
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include)

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

# Копирование DLL-файлов SFML
if(WIN32)
    # Путь к dll-файлам SFML
    file(GLOB SFML_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/bin/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/bin)
    message(STATUS "Скопированы DLL-файлы SFML в ${CMAKE_BINARY_DIR}/bin")
endif() 