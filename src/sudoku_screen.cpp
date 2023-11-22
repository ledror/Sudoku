#include "sudoku_screen.hpp"
#include <array>
#include <raylib.h>

Texture2D SudokuScreen::boardBackground;
std::array<Texture2D, 10> SudokuScreen::cellTextures;

SudokuScreen::SudokuScreen(std::array<std::array<char, 9>, 9> _board) {
  board = _board;
}

void SudokuScreen::Update() {
  board.Update();
}

void SudokuScreen::Draw() {
  board.Draw();
}

void SudokuScreen::LoadBoardTextures() {
  SudokuScreen::boardBackground = LoadTexture("resources/board_background.png");
  SudokuScreen::cellTextures[0] = LoadTexture("resources/number_blank.png");
  SudokuScreen::cellTextures[1] = LoadTexture("resources/number_one.png");
  SudokuScreen::cellTextures[2] = LoadTexture("resources/number_two.png");
  SudokuScreen::cellTextures[3] = LoadTexture("resources/number_three.png");
  SudokuScreen::cellTextures[4] = LoadTexture("resources/number_four.png");
  SudokuScreen::cellTextures[5] = LoadTexture("resources/number_five.png");
  SudokuScreen::cellTextures[6] = LoadTexture("resources/number_six.png");
  SudokuScreen::cellTextures[7] = LoadTexture("resources/number_seven.png");
  SudokuScreen::cellTextures[8] = LoadTexture("resources/number_eight.png");
  SudokuScreen::cellTextures[9] = LoadTexture("resources/number_nine.png");
}

void SudokuScreen::UnloadBoardTextures() {
  UnloadTexture(SudokuScreen::boardBackground);
  for (auto& texture : SudokuScreen::cellTextures) {
    UnloadTexture(texture);
  }
}
