#include "Bomb.h"

bool Bomb::isBlock()
{
	return false;
}

Bomb::Bomb(uint16_t coordX, uint16_t coordY, uint16_t id) :
	m_coordX(coordX), m_coordY(coordY), m_id(id)
{
	m_ticks = 8;
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

uint16_t Bomb::GetID() const
{
	return m_id;
}

bool Bomb::GetBlast() const {

	return IsBlast;
}

void Bomb::SetBlast(bool i) {

	IsBlast = i;
}

Bomb& Bomb::operator=(const Bomb& other)
{
	m_coordX=other.m_coordX;
    m_coordY=other.m_coordY;
	m_ticks=other.m_ticks;
	m_flame= other.m_flame;
	m_id= other.m_id;
	return *this;
}

Bomb& Bomb::operator=(Bomb&& other)
{
	m_coordX =other.m_coordX;
	m_coordY =other.m_coordY;
	m_ticks = other.m_ticks;
	m_flame = other.m_flame;
	m_id =    other.m_id;

	other.m_coordX = 0;
	other.m_coordY = 0;
	other.m_ticks = 0;
	other.m_flame = 0;
	other.m_id = 0;

	return *this;
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
