#pragma once

#include "raylib.h"
#include <array>
#include <memory>
#include <set>
#include "cell.hpp"

const Color adjacentsColor{140, 180, 180, 255};
const Color brothersColor{70, 140, 140, 255};
const Color clickedColor = {100, 190, 255, 255};
const Color faultyColor = {230, 41, 55, 255};

// struct Cell {
//   Cell(char _digit = '0', int _row = 0, int _col = 0, Rectangle _bounds = { 0, 0, 0, 0 }) : digit(_digit), row(_row), col(_col), bounds(_bounds) {}
//   static Cell CreateCell(int _row, int _col);
//
//   char digit;
//   int row;
//   int col;
//   Rectangle bounds;
// };

class CellCommand;

struct Board {
  Board();
  Board(std::array<std::array<char, 9>, 9> _board);
  
  void Update();
  void Draw();

  Cell* cellOnMouse();
  void updateClickedCell();
  std::shared_ptr<CellCommand> getCommand();
  void resolveFaulty();

  Cell* clickedCell;
  Cell* faultyCell;
  std::array<std::array<Cell, 9>, 9> board;

private:
  std::set<Cell*> adjacentTo(Cell* cell);
  std::set<Cell*> sameDigit(Cell* cell);
  bool canPlace(Cell* cell, char digit);
};
