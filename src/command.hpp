#pragma once

class Command {
public:
  virtual ~Command() {}

  virtual void Act() = 0;
  virtual void Undo() = 0;
};

class NoCommand : public Command {
public:
  virtual ~NoCommand() {}

  void Act() {}
  void Undo() {}
};
