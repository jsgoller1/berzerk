#include "Color.hh"

Color::Color(const int combinedHexCode) {
  this->_red = (0xFF0000 & combinedHexCode) >> 16;
  this->_green = (0x00FF00 & combinedHexCode) >> 8;
  this->_blue = (0x0000FF & combinedHexCode);
}

Uint8 Color::getRed() const { return this->_red; }
Uint8 Color::getGreen() const { return this->_green; }
Uint8 Color::getBlue() const { return this->_blue; }
