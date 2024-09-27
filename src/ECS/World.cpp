#include "World.h"

Entity World::CreateEntity() {
    return Entity(m_nextEntityID++);
}

void World::DestroyEntity(Entity entity) {
    m_entities.erase(entity.GetID());
}

// Note: Template implementations are in the header file
