#pragma once
#include "../ECS/World.h"
class Scene
{
    public:
    virtual ~Scene() = default;
    virtual void Initialize() = 0;
    virtual void Update(float deltaTime)= 0;
    virtual void Render() = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;

    protected:
    World world;

};
