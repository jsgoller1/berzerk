#include "GameObjectCollection.hh"

#include "DrawingComponent.hh"

GameObjectCollection::~GameObjectCollection() = default;

void GameObjectCollection::draw() {
  for (size_t i = 0; i < this->size(); i++) {
    this->get(i)->getDrawingComponent().draw();
  }
}

void GameObjectCollection::collisionTestAndResolve(GameObject* source) {
  for (size_t i = 0; i < this->size(); i++) {
    GameObject* object = this->get(i);
    if (object == source) {
      continue;
    }
    if (!source->getShouldRemove() && !object->getShouldRemove() && source->collisionTest(*object)) {
      source->resolveCollision(*object);
      object->resolveCollision(*source);
    }
  }
}

void GameObjectCollection::collisionTestAndResolve(GameObjectCollection* sources) {
  for (size_t i = 0; i < sources->size(); i++) {
    GameObject* object = sources->get(i);
    this->collisionTestAndResolve(object);
  }
}
