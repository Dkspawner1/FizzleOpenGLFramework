#include "World.h"
#include <algorithm>

Entity* World::CreateEntity() {
    m_entities.push_back(std::make_unique<Entity>());
    return m_entities.back().get();
}

void World::DestroyEntity(Entity* entity) {
    auto it = std::find_if(m_entities.begin(), m_entities.end(),
        [entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; });

    if (it != m_entities.end()) {
        m_entities.erase(it);
    }
}