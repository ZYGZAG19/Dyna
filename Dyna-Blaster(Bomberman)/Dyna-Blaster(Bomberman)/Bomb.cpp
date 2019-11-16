#include "Bomb.h"


bool Bomb::isBlock()
{
	return false;
}

Bomb::Bomb(uint16_t coordX, uint16_t coordY, uint16_t id) :
	m_coordX(coordX), m_coordY(coordY), m_id(id)
{
	m_ticks = 6;
}

//destructor is important for destroying old bomb objects after they have detonated!
//Bomb::~Bomb() {
//
//	delete this;
//}

uint16_t Bomb::GetCoordX() const
{
	return m_coordX;
}

uint16_t Bomb::GetCoordY() const
{
	return m_coordY;
}

bool Bomb::GetBlast() const {

	return IsBlast;
}

void Bomb::SetBlast(bool i) {

	IsBlast = i;
}

void Bomb::Explode(Map& map, uint16_t fire)
{
	map.SetBlock(Block::Type::ExplodedBomb, m_coordX, m_coordY);
	int index1 = m_coordX;
	int index2 = m_coordY;
	uint16_t flame = fire;
	while (dynamic_cast<Block*>(map[{index1 - 1, index2}])->GetType() == Block::Type::NoneBlock && flame != 0)
	{
		map.SetBlock(Block::Type::VerticalFire, --index1, index2);
		flame--;
	}
	if(dynamic_cast<Block*>(map[{index1 - 1, index2}])->GetType() == Block::Type::SoftBlock && flame != 0)
		map.SetBlock(Block::Type::ExplodedBlock, --index1, index2);
	index1 = m_coordX;
	index2 = m_coordY;
	flame = fire;
	while (dynamic_cast<Block*>(map[{index1 + 1, index2}])->GetType() == Block::Type::NoneBlock && flame != 0)
	{
		map.SetBlock(Block::Type::VerticalFire, ++index1, index2);
		flame--;
	}
	if (dynamic_cast<Block*>(map[{index1 + 1, index2}])->GetType() == Block::Type::SoftBlock && flame != 0)
		map.SetBlock(Block::Type::ExplodedBlock, ++index1, index2);
	index1 = m_coordX;
	index2 = m_coordY;
	flame = fire;
	while (dynamic_cast<Block*>(map[{index1, index2 - 1}])->GetType() == Block::Type::NoneBlock && flame != 0)
	{
		map.SetBlock(Block::Type::HorizontalFire, index1, --index2);
		flame--;
	}
	if (dynamic_cast<Block*>(map[{index1, index2 - 1}])->GetType() == Block::Type::SoftBlock && flame != 0)
		map.SetBlock(Block::Type::ExplodedBlock, index1, --index2);
	index1 = m_coordX;
	index2 = m_coordY;
	flame = fire;
	while (dynamic_cast<Block*>(map[{index1, index2 + 1}])->GetType() == Block::Type::NoneBlock && flame != 0)
	{
		map.SetBlock(Block::Type::HorizontalFire, index1, ++index2);
		flame--;
	}
	if (dynamic_cast<Block*>(map[{index1, index2 + 1}])->GetType() == Block::Type::SoftBlock && flame != 0)
		map.SetBlock(Block::Type::ExplodedBlock, index1, ++index2);
}

bool Bomb::GetIgnite() const {

	return Ignition;
}

void Bomb::SetIgnite(bool i) {

	Ignition = i;
}

uint16_t Bomb::GetTicks() const
{

	return m_ticks;
}

void Bomb::SetTicks(uint16_t ticks)
{
	m_ticks = ticks;
}

//returns length of blast
uint16_t Bomb::GetFlame() const
{

	return m_flame;
}


//sets flame size on new bombs
void Bomb::SetFlame(uint16_t F) 
{

	m_flame = F;
}

std::ostream& operator<<(std::ostream& out, const Bomb& bomb)
{
	return out << "* ";
}
