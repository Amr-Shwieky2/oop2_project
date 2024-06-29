#pragma once

#include "Collidable.h"
#include "Singleton.h"

class StaticObject : public Collidable {
public:
    StaticObject(float startX, float startY,
        const GameEffects& textureKey)
    {
        setTexture(textureKey);
        m_sprite.setPosition(startX, startY);
    };
    
protected:
};
