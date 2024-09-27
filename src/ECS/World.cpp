#include "World.h"
Entity World::CreateEntity()
{
    return Entity(nextEntityID++);
}
void World::DestroyEntity(Entity entity)
{
    entities.erase(entity.GetID());
}
template<typename T, typename... Args>
T& World::AddComponent(Entity entity, Args&&... args) {
    auto& componentMap = entities[entity.GetID()];
    auto [it, success] = componentMap.try_emplace(
        std::type_index(typeid(T)),
        std::make_unique<T>(std::forward<Args>(args)...)
    );
    return *static_cast<T*>(it->second.get());
}
template<typename T>
void World::RemoveComponent(Entity entity) {
    auto entityIt = entities.find(entity.GetID());
    if (entityIt != entities.end()) {
        entityIt->second.erase(std::type_index(typeid(T)));
    }
}
template<typename T>
T& World::GetComponent(Entity entity) {
    auto& componentMap = entities.at(entity.GetID());
    return *static_cast<T*>(componentMap.at(std::type_index(typeid(T))).get());
}
template<typename T>
bool World::HasComponent(Entity entity) const {
    auto entityIt = entities.find(entity.GetID());
    if (entityIt != entities.end()) {
        return entityIt->second.find(std::type_index(typeid(T))) != entityIt->second.end();
    }
    return false;
}
