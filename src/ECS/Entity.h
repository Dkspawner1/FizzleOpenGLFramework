#pragma once
#include <atomic>
#include <cstdint>

using EntityID = std::atomic<std::uint32_t>;

class Entity
{
public:
    explicit Entity(std::uint32_t id) : id(id) {}
    std::uint32_t GetID() const { return id.load(); }

private:
    EntityID id;
};
