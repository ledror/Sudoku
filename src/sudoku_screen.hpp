#pragma once

#include "screens.hpp"
#include "sudoku.hpp"
#include <array>

class SudokuScreen : public Screen {
public:
  static Texture2D boardBackground;
  static std::array<Texture2D, 10> cellTextures;

  SudokuScreen(std::array<std::array<char, 9>, 9> _board);

  virtual ~SudokuScreen() {}

  static void LoadBoardTextures();
  static void UnloadBoardTextures();

  virtual void Update();
  virtual void Draw();

  virtual bool ToTransition() {
    return false;
  }

public:
  Board board;
};

void LoadBoardTextures();
void UnloadBoardTextures();
