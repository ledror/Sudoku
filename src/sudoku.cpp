#include "sudoku.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <raylib.h>
#include <set>
#include <stdexcept>
#include "command.hpp"
#include "sudoku_command.hpp"
#include "sudoku_screen.hpp"

using namespace std;
using namespace sudokuscreen;

Board::Board() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
       board[i][j] = Cell::CreateCell(i, j);
    }
  }
  clickedCell = nullptr;
  faultyCell = nullptr;
}

Board::Board(array<array<char, 9>, 9> _board) : Board() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board[i][j].digit = _board[i][j];
    }
  }
}

Cell* Board::cellOnMouse() {
  Vector2 mousePos = GetMousePosition();
  int i = std::floor((mousePos.x - leftMargin) / cellWidth);
  int j = std::floor((mousePos.y - topMargin) / cellHeight);
  if (i < 0 || i > 8 || j < 0 || j > 8) {
    return nullptr;
  }
  return &board[i][j];
}

void Board::updateClickedCell() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Cell* cell = cellOnMouse();
    if (cell == nullptr) {
      clickedCell = nullptr;
    } else {
      if (cell == clickedCell) {
        clickedCell = nullptr;
      } else {
        clickedCell = cell;
      }
    }
  }
}

shared_ptr<CellCommand> Board::getCommand() {
  if (clickedCell != nullptr) { // there's a selected cell
    if (clickedCell == faultyCell || faultyCell == nullptr) {
      int keyPressed = GetKeyPressed();
      if (keyPressed >= KEY_ONE && keyPressed <= KEY_NINE && keyPressed != clickedCell->digit) {
        if (!canPlace(clickedCell, keyPressed)) {
          faultyCell = clickedCell;
        } else {
          faultyCell = nullptr;
        }
        return make_shared<CellCommand>(clickedCell, keyPressed - KEY_ONE + '1');
      }
    }
  }
  return nullptr;
}

void Board::Update() {
  updateClickedCell();
  resolveFaulty();
}

void Board::resolveFaulty() {
  if (faultyCell == nullptr) {
    return;
  }
  if (canPlace(faultyCell, faultyCell->digit)) {
    faultyCell = nullptr;
  }
}


void Board::Draw() {
  auto adjacents = adjacentTo(clickedCell);
  auto brothers = sameDigit(clickedCell);
  for (auto cell : adjacents) {
    DrawRectangleRec(cell->bounds, adjacentsColor);
  }
  for (auto cell : brothers) {
    DrawRectangleRec(cell->bounds, brothersColor);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      Cell cell = board[i][j];
      DrawTexture(cellTextures[cell.digit - '0'], cell.bounds.x, cell.bounds.y, WHITE);
    }
  }
  if (clickedCell != nullptr) {
    DrawRectangleRec(clickedCell->bounds, clickedColor);
    DrawTexture(cellTextures[clickedCell->digit - '0'], clickedCell->bounds.x, clickedCell->bounds.y, WHITE);
  } 
  if (faultyCell != nullptr) {
    DrawRectangleRec(faultyCell->bounds, faultyColor);
    DrawTexture(cellTextures[faultyCell->digit - '0'], faultyCell->bounds.x, faultyCell->bounds.y, WHITE);
  }
}


std::set<Cell*> Board::adjacentTo(Cell* cell) {
  std::set<Cell*> cells;
  if (cell == nullptr) {
    return cells;
  }
  int row = cell->row;
  int col = cell->col;
  for (int i = 0; i < 9; i++) {
    cells.insert(&board[i][col]);
  }
  for (int j = 0; j < 9; j++) {
    cells.insert(&board[row][j]);
  }
  int baseRow = 3 * (row/3);
  int baseCol = 3 * (col/3);
  for (int i = baseRow; i <baseRow + 3; i++) {
    for (int j = baseCol; j < baseCol + 3; j++) {
      cells.insert(&board[i][j]);
    }
  }
  cells.erase(&board[row][col]);
  return cells;
}


std::set<Cell*> Board::sameDigit(Cell* cell) {
  std::set<Cell*> cells;
  if (cell == nullptr || cell->digit == '0') {
    return cells;
  }
  int row = cell->row;
  int col = cell->col;
  int digit = board[row][col].digit;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (digit == board[i][j].digit) {
        cells.insert(&board[i][j]);
      }
    }
  }
  cells.erase(&board[row][col]);
  return cells;
}


bool Board::canPlace(Cell* cell, char digit) {
  if (cell == nullptr) {
    throw runtime_error("canPlace got nullptr as cell");
  }
  char oldDigit = cell->digit;
  cell->digit = digit;
  std::set<Cell*> adjacents = adjacentTo(cell);
  std::set<Cell*> brothers = sameDigit(cell);
  std::vector<Cell*> intersection;
  std::set_intersection(adjacents.begin(), adjacents.end(), brothers.begin(), brothers.end(), std::back_inserter(intersection));
  cell->digit = oldDigit;
  return intersection.size() == 0;
}
