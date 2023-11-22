#pragma once

#include <memory>

class Screen {
public:
  virtual ~Screen() {}

  virtual void Update() = 0;
  virtual void Draw() = 0;

  virtual bool ToTransition() = 0;
};

extern std::shared_ptr<Screen> thisScreen;
extern std::shared_ptr<Screen> nextScreen;
