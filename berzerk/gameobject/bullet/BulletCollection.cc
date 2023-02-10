#include "BulletCollection.hh"

#include "LevelHelpers.hh"

BulletCollection::BulletCollection(const int levelNo, BulletSpriteManager& bulletSpriteManager,
                                   DrawingProxy& drawingProxy)
    : _bullets(std::vector<std::unique_ptr<Bullet>>()),
      _drawingProxy(drawingProxy),
      _bulletSpriteManager(bulletSpriteManager) {
  this->_bulletSpriteManager.setColorMask(getLevelColor(levelNo));
}

Bullet* BulletCollection::get(const size_t index) const {
  // NOTE: We intentionally do not do bounds checking here; rather than returning a nullptr when an invalid
  // index is passed to this function (then having to trace that nullptr back to this function), I'd rather
  // just loudly get a std::out_of_range here.
  return this->_bullets.at(index).get();
}
size_t BulletCollection::size() const { return this->_bullets.size(); }

void BulletCollection::createAt(const Direction& direction, const Vect2D& origin) {
  this->_bullets.push_back(
      std::unique_ptr<Bullet>(new Bullet(origin, direction, this->_drawingProxy, this->_bulletSpriteManager)));
}

void BulletCollection::removeMarked() {
  for (size_t i = 0; i < this->size(); i++) {
    if (this->_bullets[i]->getShouldRemove()) {
      this->erase(i);
    }
  }
}

void BulletCollection::update(const TimerProxy& deltaT) {
  // NOTE: A little smelly, but bullets don't need the time
  // since it's a static animation
  (void)deltaT;
  for (size_t i = 0; i < this->size(); i++) {
    this->_bullets[i]->update();
  }
}

void BulletCollection::erase(const size_t index) { this->_bullets.erase(this->_bullets.begin() + (long)index); }
