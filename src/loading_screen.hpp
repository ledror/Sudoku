#pragma once

#include "screens.hpp"
#include "raylib.h"
#include <array>
#include <atomic>
#include <vector>
#include <thread>

class LoadingScreen : public Screen {
public:
  static std::array<Texture2D, 3> loadingFrames;

  LoadingScreen();
  virtual ~LoadingScreen();

  virtual void Update();
  virtual void Draw();

  void GenerateBoard();
  virtual bool ToTransition();

  static void LoadLoadingScreenTextures();
  static void UnloadLoadingScreenTextures();

private:
  int frameCounter;
  std::atomic<bool> finishedLoading;
  std::array<std::array<char, 9>, 9> loadedBoard;
  std::thread loadingThread;
  bool toTransition;
  // std::array<Texture2D, 3> loadingFrames;
};
