#include "PositionComponent.hh"

PositionComponent::PositionComponent(const Vect2D& position) : _position(position) {}
Vect2D PositionComponent::getPosition() const { return this->_position; }
void PositionComponent::setPosition(const Vect2D& position) { this->_position = position; }
void PositionComponent::updatePosition(const Vect2D& delta) { this->_position += delta; }
