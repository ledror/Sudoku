#include "loading_screen.hpp"
#include "screens.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <thread>
#include "sudoku_screen.hpp"
#include "board_generator.hpp"

using sudokuscreen::SudokuScreen;

std::array<Texture2D, 3> LoadingScreen::loadingFrames;

void boardGenerate(std::atomic<bool>& finished, std::array<std::array<char, 9>, 9>& board);

LoadingScreen::LoadingScreen() {
  frameCounter = 0;
  toTransition = false;
  finishedLoading = false;
}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::LoadLoadingScreenTextures() {
  LoadingScreen::loadingFrames[0] = LoadTexture("resources/loading_1.png");
  LoadingScreen::loadingFrames[1] = LoadTexture("resources/loading_2.png");
  LoadingScreen::loadingFrames[2] = LoadTexture("resources/loading_3.png");
}

void LoadingScreen::UnloadLoadingScreenTextures() {
  for (auto& texture : LoadingScreen::loadingFrames) {
    UnloadTexture(texture);
  }
}

void LoadingScreen::LoadingScreen::Update() {
  if (finishedLoading) {
    nextScreen = std::make_shared<SudokuScreen>(loadedBoard);
    loadingThread.join();
    toTransition = true;
    finishedLoading = false;
  }
  frameCounter++;
}

void LoadingScreen::Draw() {
  DrawTexture(loadingFrames[(frameCounter/30)%3], 0, 0, Color{255, 255, 255, 255});
}

bool LoadingScreen::ToTransition() {
  return toTransition && frameCounter/60 >= 3;
}

void LoadingScreen::GenerateBoard() {
  loadingThread = std::thread(&boardGenerate, std::ref(finishedLoading), std::ref(loadedBoard));
}

void boardGenerate(std::atomic<bool>& finished, std::array<std::array<char, 9>, 9>& board) {
  SudokuGenerator gen;
  board = gen.generatePlayableBoard();
  finished = true;
  std::cout << "Loading Board Finished\n";
}
