#include "StaticDrawingComponent.hh"

StaticDrawingComponent::StaticDrawingComponent(PositionComponent& positionComponent, const int height, const int width,
                               DrawingProxy& drawingProxy, const std::shared_ptr<Sprite> sprite)
    : DrawingComponent(positionComponent, height, width, drawingProxy), _sprite(sprite) {}

std::shared_ptr<Sprite> StaticDrawingComponent::getCurrentSprite() const { return this->_sprite; }
