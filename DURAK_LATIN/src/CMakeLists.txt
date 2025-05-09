set(SOURCES
    main.cpp
    Game.cpp
    Card.cpp
    Deck.cpp
    Player.cpp
)

add_executable(durak_game ${SOURCES})

# Явно указываем библиотеки SFML без использования переменных пути
if(WIN32)
    # Получаем короткий путь к директории SFML для обхода проблем с кириллицей
    target_link_libraries(durak_game 
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/SFML/lib/sfml-graphics.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/SFML/lib/sfml-window.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/SFML/lib/sfml-system.lib"
    )
    
    # Явно указываем путь к заголовочным файлам
    target_include_directories(durak_game PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/SFML/include"
    )
else()
    # Для других платформ используем обычный поиск SFML
    target_link_libraries(durak_game
        sfml-graphics
        sfml-window
        sfml-system
    )
endif()

# Устанавливаем выходной каталог
set_target_properties(durak_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
) 