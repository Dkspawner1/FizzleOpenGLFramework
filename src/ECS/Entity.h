// Entity.h
#pragma once
#include "Component.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

class Entity {
public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& componentRef = *component;
        m_components[typeid(T)] = std::move(component);
        return componentRef;
    }

    template<typename T>
    void RemoveComponent() {
        m_components.erase(typeid(T));
    }

    template<typename T>
    T& GetComponent() {
        auto it = m_components.find(typeid(T));
        if (it == m_components.end()) {
            throw std::runtime_error("Component not found");
        }
        return *static_cast<T*>(it->second.get());
    }

    template<typename T>
    bool HasComponent() const {
        return m_components.find(typeid(T)) != m_components.end();
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
};