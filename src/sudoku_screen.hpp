#pragma once

#include "command.hpp"
#include "screens.hpp"
#include "sudoku.hpp"
#include "sudoku_command.hpp"
#include <array>
#include <memory>
#include <raylib.h>
#include <stack>

namespace sudokuscreen {

constexpr static const float cellWidth = 70.0f;
constexpr static const float cellHeight = 70.0f;

constexpr static const float leftMargin = 100.0f;
constexpr static const float topMargin = 100.0f;

constexpr static const Color backgroundColor = RAYWHITE;
constexpr static const Vector2 boardBackgroundPos{leftMargin-1, topMargin-1};
constexpr static const Vector2 boardBackgroundSize{2+cellWidth*9, 2+cellHeight*9};

extern Texture2D boardBackground;
extern std::array<Texture2D, 10> cellTextures;

class SudokuScreen : public Screen {
public:
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
  std::stack<std::shared_ptr<Command>> cmdHistory;
};

void LoadBoardTextures();
void UnloadBoardTextures();

void DrawBoardBackground();
void DrawBoardSkeleton();
};
