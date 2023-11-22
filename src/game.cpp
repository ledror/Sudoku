#include "raylib.h"
#include "sudoku.hpp"
#include "screens.hpp"
#include "loading_screen.hpp"
#include "board_generator.hpp"
#include "sudoku_screen.hpp"
#include <memory>

static const int screenWidth = 800;
static const int screenHeight = 800;

std::shared_ptr<Screen> thisScreen;
std::shared_ptr<Screen> nextScreen;

void LoadAllTextures();
void UnloadAllTextures();

int main() {
  InitWindow(screenWidth, screenHeight, "Sudoku");

  LoadAllTextures();

  thisScreen = std::make_shared<LoadingScreen>();
  std::static_pointer_cast<LoadingScreen>(thisScreen)->GenerateBoard();

  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    if (thisScreen->ToTransition()) {
      thisScreen = nextScreen;
      nextScreen = nullptr;
    }

    thisScreen->Update();

    BeginDrawing();

    ClearBackground(GRAY);
    
    thisScreen->Draw();

    EndDrawing();
  }

  UnloadAllTextures();

  CloseWindow();
}

void LoadAllTextures() {
  LoadingScreen::LoadLoadingScreenTextures();
  SudokuScreen::LoadBoardTextures();
}

void UnloadAllTextures() {
  LoadingScreen::UnloadLoadingScreenTextures();
  SudokuScreen::UnloadBoardTextures();
}
