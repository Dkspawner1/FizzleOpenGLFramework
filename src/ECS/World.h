#pragma once
#include "Component.h"
#include "Entity.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

class World {
public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template <typename T, typename... Args>
    T& AddComponent(Entity entity, Args&&... args);

    template <typename T>
    void RemoveComponent(Entity entity);

    template <typename T>
    T& GetComponent(Entity entity);

    template <typename T>
    bool HasComponent(Entity entity) const;

private:
    EntityID nextEntityID = 0;
    std::unordered_map<EntityID, std::unordered_map<std::type_index, std::unique_ptr<Component>>> entities;
};
