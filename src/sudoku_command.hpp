#pragma once

#include "command.hpp"
#include "cell.hpp"

// class Command {
// public:
//   virtual ~Command() {}
//
//   virtual void Act() = 0;
//   virtual void Undo() = 0;
// };
//

class CellCommand : public Command {
public:
  CellCommand(Cell* cell, char _newDigit);
  virtual ~CellCommand() {}

  virtual void Act();
  virtual void Undo();

protected:
  Cell* cell;
  char newDigit;
  char oldDigit;
};
