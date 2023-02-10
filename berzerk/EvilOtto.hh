#pragma once

#include "GameObject.hh"
#include "IAnimation.hh"
#include "ICollision.hh"

class EvilOtto : public GameObject, public ICollision, public IAnimation {};
