// World.h
#pragma once
#include "Entity.h"
#include "Component.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <stdexcept>

class World {
public:
    Entity* CreateEntity();
    void DestroyEntity(Entity* entity);

    template<typename T, typename... Args>
    T& AddComponent(Entity* entity, Args&&... args) {
        if (!entity) {
            throw std::runtime_error("Attempting to add component to null entity");
        }
        return entity->AddComponent<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void RemoveComponent(Entity* entity) {
        if (!entity) {
            throw std::runtime_error("Attempting to remove component from null entity");
        }
        entity->RemoveComponent<T>();
    }

    template<typename T>
    T& GetComponent(Entity* entity) {
        if (!entity) {
            throw std::runtime_error("Attempting to get component from null entity");
        }
        return entity->GetComponent<T>();
    }

    template<typename T>
    bool HasComponent(Entity* entity) const {
        if (!entity) {
            return false;
        }
        return entity->HasComponent<T>();
    }

    const std::vector<std::unique_ptr<Entity>>& GetEntities() const { return m_entities; }

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
};