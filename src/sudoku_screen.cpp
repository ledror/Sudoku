#include "sudoku_screen.hpp"
#include "sudoku_command.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>

Texture2D sudokuscreen::boardBackground;
std::array<Texture2D, 10> sudokuscreen::cellTextures;

using namespace sudokuscreen;

SudokuScreen::SudokuScreen(std::array<std::array<char, 9>, 9> _board) {
  board = _board;
}

void SudokuScreen::Update() {
  if (IsKeyPressed(KEY_BACKSPACE)) {
    if (!cmdHistory.empty()) {
      auto cmd = cmdHistory.top();
      cmd->Undo();
      cmdHistory.pop();
      return;
    }
  }
  board.Update();
  auto cmd = board.getCommand();
  if (cmd != nullptr) {
    cmd->Act();
    cmdHistory.push(cmd);
  }
}

void SudokuScreen::Draw() {
  DrawBoardBackground();
  board.Draw();
  DrawBoardSkeleton();
}

void sudokuscreen::LoadBoardTextures() {
  boardBackground = LoadTexture("resources/board_background.png");
  cellTextures[0] = LoadTexture("resources/number_blank.png");
  cellTextures[1] = LoadTexture("resources/number_one.png");
  cellTextures[2] = LoadTexture("resources/number_two.png");
  cellTextures[3] = LoadTexture("resources/number_three.png");
  cellTextures[4] = LoadTexture("resources/number_four.png");
  cellTextures[5] = LoadTexture("resources/number_five.png");
  cellTextures[6] = LoadTexture("resources/number_six.png");
  cellTextures[7] = LoadTexture("resources/number_seven.png");
  cellTextures[8] = LoadTexture("resources/number_eight.png");
  cellTextures[9] = LoadTexture("resources/number_nine.png");
}

void sudokuscreen::UnloadBoardTextures() {
  UnloadTexture(sudokuscreen::boardBackground);
  for (auto& texture : cellTextures) {
    UnloadTexture(texture);
  }
}

void sudokuscreen::DrawBoardBackground() {
  DrawRectangleV(boardBackgroundPos, boardBackgroundSize, backgroundColor);
  DrawRectangle(leftMargin-1, topMargin-1, boardBackground.width, boardBackground.height, backgroundColor);
}

void sudokuscreen::DrawBoardSkeleton() {
  DrawTextureV(boardBackground, boardBackgroundPos, WHITE);
}
