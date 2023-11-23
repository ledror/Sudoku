#include "board_generator.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <random>
#include <stdexcept>
#include <iostream>

using namespace std;

std::array<std::array<char, 9>, 9> SudokuGenerator::generateFullBoard() {
  std::array<std::array<char, 9>, 9> board;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board[i][j] = '0';
    }
  }

  vector<int> indecies;
  for (int i = 0; i < 81; i++) {
    indecies.push_back(i);
  }

  auto rd = random_device {};
  auto rng = default_random_engine { rd() };

  shuffle(indecies.begin(), indecies.end(), rng);

  for (auto index : indecies) {
    int row = index/9;
    int col = index%9;
    auto validChars = getValidChars(board, row, col);
    shuffle(validChars.begin(), validChars.end(), rng);
    bool found = false;
    for (auto digit : validChars) {
      board[row][col] = digit;
      if (isSolvable(board)) {
        found = true;
        break;
      }
    }
    if (!found) {
      throw runtime_error("generating failed! no suitable digit found");
    }
  }

  return board;
}

std::array<std::array<char, 9>, 9> SudokuGenerator::generatePlayableBoard() {
  stopwatch = std::chrono::high_resolution_clock::now();
  callCounter = 0;
  
  std::array<std::array<char, 9>, 9> fullBoard;

  bool generated = false;

  while(!generated) {
    try {
      fullBoard = generateFullBoard();

      vector<int> indecies;
      for (int i = 0; i < 81; i++) {
        indecies.push_back(i);
      }

      auto rd = random_device {};
      auto rng = default_random_engine { rd() };
      shuffle(indecies.begin(), indecies.end(), rng);
      
      for (auto index : indecies) {
        int row = index/9;
        int col = index%9;
        char oldDigit = fullBoard[row][col];
        fullBoard[row][col] = '0';
        SolutionOptions state = boardSolutionState(fullBoard);
        if (state == SolutionOptions::UNIQUE_SOLUTION) {
          continue;
        } else if (state == SolutionOptions::MULTIPLE_SOLUTIONS) {
          fullBoard[row][col] = oldDigit;
          continue;
        } else {
          throw runtime_error("removing digit made the board unsolvable??");
        }
      }
      
      generated = true;
    } catch(const runtime_error& e) {
      throw e;
    } catch(const std::chrono::milliseconds& e) {
      std::cout << "generation took too long (" << e.count() << "ms), trying again" << std::endl;
      stopwatch = std::chrono::high_resolution_clock::now();
      callCounter = 0;
    }
  }

  return fullBoard;
}

bool SudokuGenerator::solveRecForward(std::array<std::array<char, 9>, 9>& board, int oldCell) {
  callCounter++;
  if (callCounter > MaxCallCounter) {
    callCounter = 0;
    auto timeNow = std::chrono::high_resolution_clock::now();
    auto passedMicroseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - stopwatch);
    if (passedMicroseconds > std::chrono::milliseconds(MaxCallTimeout)) {
      throw passedMicroseconds;
    }
  }
 
  int cell = nextFreeCell(board, oldCell);
  if (cell == -1) {
      return true;
  }
  int i = cell/9;
  int j = cell%9;
  for (char c = '1'; c <= '9'; c++) {
      if (isValidChar(board, i, j, c)) {
          board[i][j] = c;
          if (solveRecForward(board, cell)) {
              return true;
          } else {
              continue;
          }
      }
  }
  board[i][j] = '0';
  return false;
}

bool SudokuGenerator::solveRecBackward(std::array<std::array<char, 9>, 9>& board, int oldCell) {
  callCounter++;
  if (callCounter > MaxCallCounter) {
    callCounter = 0;
    auto timeNow = std::chrono::high_resolution_clock::now();
    auto passedMicroseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - stopwatch);
    if (passedMicroseconds > std::chrono::milliseconds(MaxCallTimeout)) {
      throw passedMicroseconds;
    }
  }

  int cell = nextFreeCell(board, oldCell);
  if (cell == -1) {
      return true;
  }
  int i = cell/9;
  int j = cell%9;
  for (char c = '9'; c >= '1'; c--) {
      if (isValidChar(board, i, j, c)) {
          board[i][j] = c;
          if (solveRecBackward(board, cell)) {
              return true;
          } else {
              continue;
          }
      }
  }
  board[i][j] = '0';
  return false;
}

vector<char> SudokuGenerator::getValidChars(std::array<std::array<char, 9>, 9>& board, int row, int col) {
  vector<char> chars;
  for (char c = '1'; c <= '9'; c++) {
    if (isValidChar(board, row, col, c)) {
      chars.push_back(c);
    }
  }
  return chars;
}

bool SudokuGenerator::isValidChar(std::array<std::array<char, 9>, 9>& board, int row, int col, char ch) {
  for(int i=0; i<9; i++){
      if(board[row][i] == ch) return false;
      if(board[i][col] == ch) return false;
      if(board[3*(row/3) + i/3][3*(col/3) + i%3] == ch) return false;
  }
  return true;
}

int SudokuGenerator::nextFreeCell(std::array<std::array<char, 9>, 9>& board, int cell) {
  for (; cell < 81; cell++) {
      if (board[cell/9][cell%9] == '0') {
          return cell;
      }
  }
  return -1;
}

bool SudokuGenerator::isSolvable(const array<array<char, 9>, 9>& board) {
  auto boardCopy = board;
  return solveRecForward(boardCopy, 0);
}

SolutionOptions SudokuGenerator::boardSolutionState(const std::array<std::array<char, 9>, 9>& board) {
  auto boardFoward = board;
  auto boardBackward = board;
  int count = 0;
  if (solveRecForward(boardFoward, 0)) {
    count++;
  }
  if (solveRecBackward(boardBackward, 0)) {
    count++;
  }
  if (count == 0) {
    return SolutionOptions::NO_SOLUTION;
  } else if (count == 1) {
    throw std::runtime_error("one of the solving algorithms failed");
  } else {
    if (boardFoward == boardBackward) {
      return SolutionOptions::UNIQUE_SOLUTION;
    } else {
      return SolutionOptions::MULTIPLE_SOLUTIONS;
    }
  }

}

void boardGenerate(std::atomic<bool>& finished, std::array<std::array<char, 9>, 9>& board) {
  SudokuGenerator gen;
  board = gen.generatePlayableBoard();
  finished = true;
  std::cout << "Loading Board Finished\n";
}
