#pragma once

#include "GameObject.h"
#include "Singleton.h"

class MovableObject :public GameObject
{
public:
	MovableObject(float startX, float startY,
		const GameEffects& textureKey);

	MovableObject(const Characters& textureKey);

	virtual ~MovableObject() = default;
	void draw(sf::RenderWindow& window);
	void resetPosition(float x, float y) override;
	sf::Vector2f getPosition() const override;
	virtual void update(float deltaTime) = 0;

protected:
	void setTexture(const GameEffects& textureKey);
	void setTexture(const Characters& textureKey);
};

