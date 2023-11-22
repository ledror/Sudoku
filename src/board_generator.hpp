#include <vector>
#include <array>

enum class SolutionOptions {NO_SOLUTION, UNIQUE_SOLUTION, MULTIPLE_SOLUTIONS};

class SudokuGenerator {
public:
  std::array<std::array<char, 9>, 9> generateFullBoard();
  std::array<std::array<char, 9>, 9> generatePlayableBoard();

private:
  SolutionOptions boardSolutionState(const std::array<std::array<char, 9>, 9>& board);
  std::vector<char> getValidChars(std::array<std::array<char, 9>, 9>& board, int row, int col);

  bool isSolvable(const std::array<std::array<char, 9>, 9>& board);
  void solveSudoku(std::array<std::array<char, 9>, 9>& board);
  bool solveRecForward(std::array<std::array<char, 9>, 9>& board, int oldCell);
  bool solveRecBackward(std::array<std::array<char, 9>, 9>& board, int oldCell);
  bool isValidChar(std::array<std::array<char, 9>, 9>& board, int row, int col, char ch);
  int nextFreeCell(std::array<std::array<char, 9>, 9>& board, int cell);
};
