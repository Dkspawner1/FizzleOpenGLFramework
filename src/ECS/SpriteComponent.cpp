#include "FizzleFramework/ECS/SpriteComponent.h"
#include <iostream>
#include <memory>

SpriteComponent::SpriteComponent(const std::string& texturePath) : m_texture(std::make_unique<Texture>(texturePath))
{
    std::cout << "SpriteComponent created with texture path: "<< texturePath << std::endl;
    if(m_texture->IsLoaded())
    {
        std::cout << "Texture loaded successfully. Size: " << m_texture->GetWidth() << "x" <<m_texture->GetHeight() << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }

}

void SpriteComponent::SetTexture(const std::string&texturePath)
{

    m_texture = std::make_unique<Texture>(texturePath);
}
