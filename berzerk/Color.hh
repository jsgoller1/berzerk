#pragma once
#include <SDL2/SDL.h>

class Color {
 public:
  static Color Green() { return Color(0x75FB4C); }
  static Color Mustard() { return Color(0x6C6C1F); }
  static Color Red() { return Color(0xEA3323); }
  static Color Cobalt() { return Color(0x2D6A6B); }
  static Color Magenta() { return Color(0x630F68); }
  static Color Yellow() { return Color(0xFFFF54); }
  static Color Pink() { return Color(0xEA34F7); }
  static Color Gray() { return Color(0x6C6C6C); }
  static Color Teal() { return Color(0x75FBFD); }
  static Color White() { return Color(0xFFFFFF); }
  static Color Orange() { return Color(0xFFA500); }
  Color(const int combinedHexCode);

  Uint8 getRed() const;
  Uint8 getGreen() const;
  Uint8 getBlue() const;

 private:
  Uint8 _red;
  Uint8 _green;
  Uint8 _blue;
};
