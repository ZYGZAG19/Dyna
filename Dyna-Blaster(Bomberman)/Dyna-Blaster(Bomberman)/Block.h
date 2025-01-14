#pragma once
#include"Entity.h"
#include<iostream>

class Block: public Entity
{
public:
	enum class Type
	{
		HardBlock=0,
		SoftBlock,
		NoneBlock,
		ExplodedBlock,
		HorizontalFire,
		VerticalFire,
		ExplodedBomb,
		Exit,
		HiddenExit
	};
	
public:
	Block(Type type, const float x, const float y,sf::Texture& textureSheet);
	Type GetType() const;
	sf::FloatRect GetGlobalBounds() const;

	void Render(sf::RenderTarget& target);

	friend std::ostream& operator<<(std::ostream& out, const Block& block);
	Block& operator=(const Block& other);
	Block& operator=(Block&& other);

private:
	Type m_type;
	sf::RectangleShape m_sprite;
};

