#include "SpriteComponent.h"
#include <memory>

SpriteComponent::SpriteComponent(const std::string& texturePath) : m_texture(std::make_unique<Texture>(texturePath))
{

}

void SpriteComponent::SetTexture(const std::string&texturePath)
{

    m_texture = std::make_unique<Texture>(texturePath);
}