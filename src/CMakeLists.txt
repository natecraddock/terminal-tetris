add_executable(tetris main.c screen.c game.c events.c queue.c piece.c)

target_include_directories(tetris PUBLIC "include")
target_link_libraries(tetris m ncurses)
