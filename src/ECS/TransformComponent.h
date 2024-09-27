#pragma once
#include "Component.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>

struct TransformComponent : public Component
{
glm::vec2 position;
glm::vec2 size;

TransformComponent(const glm::vec2& pos, const glm::vec2&sz) : position(pos), size(sz){}


};