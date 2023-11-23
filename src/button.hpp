#pragma once

#include <raylib.h>

class Button {
public:
  virtual ~Button() {}

  virtual bool isClick() = 0;
  virtual void Draw() = 0;
};

class ToggleButton : public Button {
public:
  ToggleButton(Texture2D _textureOff, Texture2D _textureOn, Rectangle _rect);
  virtual ~ToggleButton() {}

  virtual void Toggle();
  virtual bool isClick();
  virtual void Draw();

private:
  bool toggle;
  Texture2D textureOff;
  Texture2D textureOn;
  Rectangle rect;
};

class ClickButton : public Button {
public:
  ClickButton() {}
  ClickButton(Texture2D _texture, Rectangle _rect);
  virtual ~ClickButton() {}

  virtual bool isClick();
  virtual void Draw();

private:
  Texture2D texture;
  Rectangle rect;
};
