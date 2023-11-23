#pragma once

#include <chrono>
#include <vector>
#include <array>
#include <atomic>

enum class SolutionOptions {NO_SOLUTION, UNIQUE_SOLUTION, MULTIPLE_SOLUTIONS};

class SudokuGenerator {
public:
  std::array<std::array<char, 9>, 9> generateFullBoard();
  std::array<std::array<char, 9>, 9> generatePlayableBoard();

private:
  std::chrono::time_point<std::chrono::system_clock> stopwatch;
  int callCounter;

  constexpr static const int MaxCallCounter = 10000;
  constexpr static const auto MaxCallTimeout = std::chrono::milliseconds(250);

  SolutionOptions boardSolutionState(const std::array<std::array<char, 9>, 9>& board);
  std::vector<char> getValidChars(std::array<std::array<char, 9>, 9>& board, int row, int col);

  bool isSolvable(const std::array<std::array<char, 9>, 9>& board);
  void solveSudoku(std::array<std::array<char, 9>, 9>& board);
  bool solveRecForward(std::array<std::array<char, 9>, 9>& board, int oldCell);
  bool solveRecBackward(std::array<std::array<char, 9>, 9>& board, int oldCell);
  bool isValidChar(std::array<std::array<char, 9>, 9>& board, int row, int col, char ch);
  int nextFreeCell(std::array<std::array<char, 9>, 9>& board, int cell);
};

void boardGenerate(std::atomic<bool>& finished, std::array<std::array<char, 9>, 9>& board);
