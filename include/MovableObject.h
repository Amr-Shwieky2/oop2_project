#pragma once
#include "Collidable.h"
#include "Singleton.h"

class MovableObject : public Collidable
{
public:
	MovableObject(const GameEffects& textureKey) { setTexture(textureKey); };


	MovableObject(float startX, float startY,
		const GameEffects& textureKey)
	{
		setTexture(textureKey);
		m_sprite.setPosition(startX, startY);
	};

	MovableObject() {};


private:

};

