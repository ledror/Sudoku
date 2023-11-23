#include "cell.hpp"
#include "sudoku_screen.hpp"

using namespace sudokuscreen;

Cell Cell::CreateCell(int i, int j) {
  return Cell('0', i, j, Rectangle{
    leftMargin + i*cellWidth,
    topMargin + j*cellHeight,
    cellWidth,
    cellHeight
  });
}
