#include "sudoku.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <raylib.h>
#include <set>

Board::Board() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board[i][j] = Cell('0', false, i, j, { leftMargin + i*cellWidth, topMargin + j*cellHeight, cellWidth, cellHeight });
    }
  }
  clickedCell = nullptr;
  faultyCell = nullptr;
}

void Board::Update() {
  Vector2 mousePos = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Cell* newClicked = nullptr;
    bool found = false;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (CheckCollisionPointRec(mousePos, board[i][j].bounds)) {
          found = true;
          newClicked = &board[i][j];
          if (newClicked == clickedCell) {
            newClicked->clicked = !newClicked->clicked;
            clickedCell = nullptr;
          } else {
            newClicked->clicked = true;
            if (clickedCell != nullptr) {
              clickedCell->clicked = false;
            }
            clickedCell = newClicked;
          }
        }
      }
    }
    if (!found) {
      if (clickedCell != nullptr) {
        clickedCell->clicked = false;
        clickedCell = nullptr;
      }
    }
  }
  if (clickedCell != nullptr) { // there's a selected cell
    if (clickedCell == faultyCell || faultyCell == nullptr) {
      int keyPressed = GetKeyPressed();
      if (keyPressed >= KEY_ONE && keyPressed <= KEY_NINE) {
        int oldDigit = clickedCell->digit;
        clickedCell->digit = keyPressed - KEY_ONE + '1';
        if (!canPlace(clickedCell)) {
          faultyCell = clickedCell;
        } else {
          faultyCell = nullptr;
        }
      }
    }
  }
  return;
}

void Board::Draw() {
  DrawRectangle(leftMargin-1, topMargin-1, boardBackground.width, boardBackground.height, backgroundColor);
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
      DrawTexture(cellTextures[cell.digit - '0'], cell.bounds.x, cell.bounds.y, Color{255, 255, 255 ,255});
    }
  }
  if (clickedCell != nullptr) {
    DrawRectangleRec(clickedCell->bounds, clickedColor);
    DrawTexture(cellTextures[clickedCell->digit - '0'], clickedCell->bounds.x, clickedCell->bounds.y, Color{255, 255, 255 ,255});
  } 
  if (faultyCell != nullptr) {
    DrawRectangleRec(faultyCell->bounds, faultyColor);
    DrawTexture(cellTextures[faultyCell->digit - '0'], faultyCell->bounds.x, faultyCell->bounds.y, Color{255, 255, 255 ,255});
  }
  DrawTexture(boardBackground, leftMargin-1, topMargin-1, Color{255, 255, 255, 255}); // -1 because background is (width*9+2)x(height*9+2)
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


bool Board::canPlace(Cell* cell) {
  std::set<Cell*> adjacents = adjacentTo(cell);
  std::set<Cell*> brothers = sameDigit(cell);
  std::vector<Cell*> intersection;
  std::set_intersection(adjacents.begin(), adjacents.end(), brothers.begin(), brothers.end(), std::back_inserter(intersection));
  return intersection.size() == 0;
}
