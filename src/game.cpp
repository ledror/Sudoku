#include "raylib.h"
#include "sudoku.hpp"

static const int screenWidth = 800;
static const int screenHeight = 800;

Texture2D boardBackground;
Texture2D cellTextures[10] = {0};

void LoadBoardTextures();

int main() {
  InitWindow(screenWidth, screenHeight, "Sudoku");

  LoadBoardTextures();
  Board board;

  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    board.Update();
    BeginDrawing();

    ClearBackground(GRAY);
    
    board.Draw();

    EndDrawing();
  }

  CloseWindow();
}

void LoadBoardTextures() {
  boardBackground = LoadTexture("resources/board_background.png");
  cellTextures[0] = LoadTexture("resources/number_blank.png");
  cellTextures[1] = LoadTexture("resources/number_one.png");
  cellTextures[2] = LoadTexture("resources/number_two.png");
  cellTextures[3] = LoadTexture("resources/number_three.png");
  cellTextures[4] = LoadTexture("resources/number_four.png");
  cellTextures[5] = LoadTexture("resources/number_five.png");
  cellTextures[6] = LoadTexture("resources/number_six.png");
  cellTextures[7] = LoadTexture("resources/number_seven.png");
  cellTextures[8] = LoadTexture("resources/number_eight.png");
  cellTextures[9] = LoadTexture("resources/number_nine.png");
}
