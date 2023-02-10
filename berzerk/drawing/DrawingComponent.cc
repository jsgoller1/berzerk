#include "DrawingComponent.hh"

#include "Vect2D.hh"

DrawingComponent::DrawingComponent(PositionComponent& positionComponent, const int height, const int width,
                                   DrawingProxy& drawingProxy)
    : _positionComponent(positionComponent), _height(height), _width(width), _drawingProxy(drawingProxy) {
  // SDL_SetColorKey(this->_pixelData.get(), SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
DrawingComponent::~DrawingComponent() = default;

int DrawingComponent::getHeight() const { return this->_height; }
void DrawingComponent::setHeight(const int height) { this->_height = height; }

int DrawingComponent::getWidth() const { return this->_width; }
void DrawingComponent::setWidth(const int width) { this->_width = width; }

Vect2D DrawingComponent::getTopLeft() const {
  Vect2D topLeft = this->_positionComponent.getPosition();
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}

DrawingProxy& DrawingComponent::getDrawingProxy() const { return this->_drawingProxy; }

void DrawingComponent::draw() {
  this->_drawingProxy.draw(this->_positionComponent.getPosition(), this->_width, this->_height,
                           this->getCurrentSprite());
}
