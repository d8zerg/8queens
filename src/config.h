#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <iostream>


constexpr int BOARD_SIZE = 8;
constexpr int WINDOW_SIZE = 640;
constexpr int CELL_SIZE = WINDOW_SIZE / BOARD_SIZE;

using Board = std::array<int, BOARD_SIZE>;


#endif //CONFIG_H
