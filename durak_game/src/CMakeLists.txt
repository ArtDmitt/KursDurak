set(SOURCES
    main.cpp
    Game.cpp
    Card.cpp
    Deck.cpp
    Player.cpp
)

add_executable(durak_game ${SOURCES})

target_link_libraries(durak_game
    sfml-graphics
    sfml-window
    sfml-system
)

# Устанавливаем выходной каталог
set_target_properties(durak_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
) 