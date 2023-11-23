#include "sudoku_command.hpp"
#include <iostream>
#include <stdexcept>

CellCommand::CellCommand(Cell* _cell, char _newDigit) {
  if (_cell == nullptr) {
    throw std::runtime_error("created cell command with nullptr as cell");
  }
  cell = _cell;
  oldDigit = cell->digit;
  newDigit = _newDigit;
}

void CellCommand::Act() {
  cell->digit = newDigit;
}

void CellCommand::Undo() {
  cell->digit = oldDigit;
}
