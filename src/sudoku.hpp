#pragma once

#include "raylib.h"
#include <array>
#include <set>

const float cellWidth = 70.0f;
const float cellHeight = 70.0f;

const float leftMargin = 100.0f;
const float topMargin = 100.0f;

const Color adjacentsColor{140, 180, 180, 255};
const Color brothersColor{70, 140, 140, 255};
const Color backgroundColor = RAYWHITE;
const Color clickedColor = {100, 190, 255, 255};
const Color faultyColor = {230, 41, 55, 255};

struct Cell {
  Cell(char _digit = '0', bool _clicked = false, int _row = 0, int _col = 0, Rectangle _bounds = { 0, 0, 0, 0 }) : digit(_digit), clicked(_clicked), row(_row), col(_col), bounds(_bounds) {}

  char digit;
  bool clicked;
  int row;
  int col;
  Rectangle bounds;
};

struct Board {
  Board();
  Board(std::array<std::array<char, 9>, 9> _board);
  
  void Update();
  void Draw();

  Cell* clickedCell;
  Cell* faultyCell;
  std::array<std::array<Cell, 9>, 9> board;

private:
  std::set<Cell*> adjacentTo(Cell* cell);
  std::set<Cell*> sameDigit(Cell* cell);
  bool canPlace(Cell* cell);
};
