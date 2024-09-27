#pragma once
#include "World.h"
class System
{
    public:
    virtual ~System() = default;
    virtual void Update(World & world, float deltaTime) = 0;

}
