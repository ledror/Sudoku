#include "button.hpp"
#include <raylib.h>

ToggleButton::ToggleButton(Texture2D _textureOff, Texture2D _textureOn, Rectangle _rect) :
  toggle(false),
  textureOff(_textureOff),
  textureOn(_textureOn),
  rect(_rect)
{}

void ToggleButton::Toggle() {
  toggle = !toggle;
}

bool ToggleButton::isClick() {
  Vector2 mousePos = GetMousePosition();
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, rect);
}

void ToggleButton::Draw() {
  if (toggle) {
    DrawTextureRec(textureOn, rect, Vector2{rect.x, rect.y}, WHITE);
  } else {
    DrawTextureRec(textureOff, rect, Vector2{rect.x, rect.y}, WHITE);
  }
}

ClickButton::ClickButton(Texture2D _texture, Rectangle _rect) :
  texture(_texture),
  rect(_rect)
{}

bool ClickButton::isClick() {
  Vector2 mousePos = GetMousePosition();
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, rect);
}

void ClickButton::Draw() {
  DrawTexture(texture, rect.x, rect.y, WHITE);
}
