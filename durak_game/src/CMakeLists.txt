set(SOURCES
    main.cpp
    Game.cpp
    Card.cpp
    Deck.cpp
    Player.cpp
)

add_executable(durak_game ${SOURCES})

# Настройка линковки SFML
if(WIN32)
    # Для MinGW используем обычную линковку
    target_link_libraries(durak_game
        sfml-graphics
        sfml-window
        sfml-system
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