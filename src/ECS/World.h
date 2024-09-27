#pragma once
#include "Entity.h"
#include "Component.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <vector>

class World {
public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template<typename T, typename... Args>
    T& AddComponent(Entity entity, Args&&... args);

    template<typename T>
    void RemoveComponent(Entity entity);

    template<typename T>
    T& GetComponent(Entity entity);

    template<typename T>
    bool HasComponent(Entity entity) const;

    const std::unordered_map<unsigned int, std::unordered_map<std::type_index, std::unique_ptr<Component>>>& GetEntities() const { return m_entities; }

private:
    unsigned int m_nextEntityID = 0;
    std::unordered_map<unsigned int, std::unordered_map<std::type_index, std::unique_ptr<Component>>> m_entities;
};

// Template implementations
template<typename T, typename... Args>
T& World::AddComponent(Entity entity, Args&&... args) {
    auto& componentMap = m_entities[entity.GetID()];
    auto [it, success] = componentMap.try_emplace(
        std::type_index(typeid(T)),
        std::make_unique<T>(std::forward<Args>(args)...)
    );
    return *static_cast<T*>(it->second.get());
}

template<typename T>
void World::RemoveComponent(Entity entity) {
    auto entityIt = m_entities.find(entity.GetID());
    if (entityIt != m_entities.end()) {
        entityIt->second.erase(std::type_index(typeid(T)));
    }
}

template<typename T>
T& World::GetComponent(Entity entity) {
    auto& componentMap = m_entities.at(entity.GetID());
    return *static_cast<T*>(componentMap.at(std::type_index(typeid(T))).get());
}

template<typename T>
bool World::HasComponent(Entity entity) const {
    auto entityIt = m_entities.find(entity.GetID());
    if (entityIt != m_entities.end()) {
        return entityIt->second.find(std::type_index(typeid(T))) != entityIt->second.end();
    }
    return false;
}
