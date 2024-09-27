#pragma once
#include "Component.h"
#include "../Core/Texture.h"
#include <memory>

class SpriteComponent : public Component 
{
    public:
 SpriteComponent(const std::string& texturePath);
void SetTexture(const std::string& texturePath);
 const Texture* GetTexture() const { return m_texture.get(); }    private:

    std::unique_ptr<Texture> m_texture;
};