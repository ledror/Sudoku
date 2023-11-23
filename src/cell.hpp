#pragma once

#include "raylib.h"

struct Cell {
  Cell(char _digit = '0', int _row = 0, int _col = 0, Rectangle _bounds = { 0, 0, 0, 0 }) : digit(_digit), row(_row), col(_col), bounds(_bounds) {}
  static Cell CreateCell(int _row, int _col);

  char digit;
  int row;
  int col;
  Rectangle bounds;
};
