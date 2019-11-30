#include "Player.h"

Player::Player(uint16_t fire, uint16_t numberBombs, uint16_t health, uint32_t score, uint16_t speed) :
	m_fire(fire), m_noOfBombs(numberBombs), m_health(health), m_score(score), m_speed(speed)
{
	m_coordX = 1;
	m_coordY = 1;
	m_lastX = 1;
	m_lastY = 1;
	m_softBlockPass = true;
	m_bombPass = true;
	m_vest = true;
	m_remoteControl = true;
}

Player::Player()
{
}

void Player::SetFire(uint16_t up)
{
	m_fire = up;
}

uint16_t Player::GetFire() const
{
	return m_fire;
}

void Player::SetNoOfBombs(uint16_t up)
{
	m_noOfBombs = up;
}

uint16_t Player::GetNoOfBombs() const
{
	return m_noOfBombs;
}

uint16_t Player::GetSpeed() const
{
	return m_speed;
}

void Player::SetSpeed(uint16_t up)
{
	m_speed = up;
}

void Player::SetSoftBlockPass(bool up)
{
	m_softBlockPass = up;
}

void Player::SetBombPass(bool up)
{
	m_bombPass = up;
}

void Player::SetHealth(uint16_t up)
{
	m_health = up;
}

uint16_t Player::GetHealth() const
{
	return m_health;
}

uint16_t Player::GetCoordX() const
{
	return m_coordX;
}

uint16_t Player::GetCoordY() const
{
	return m_coordY;
}

uint16_t Player::GetNoOfPlacedBombs() const
{
	return m_placedBombs.size();
}

uint16_t Player::GetLastX() const
{
	return m_lastX;
}

uint16_t Player::GetLastY() const
{
	return m_lastY;
}

uint16_t Player::GetScore() const
{
	return m_score;
}

bool Player::GetHasVest() const
{
	return m_vest;
}

bool Player::GetRemoteControl() const
{
	return m_remoteControl;
}

void Player::SetVest(bool up)
{
	m_vest = up;
}

void Player::SetRemoteControl(bool up)
{
	m_remoteControl = up;
}

void Player::Place(Map& map, uint16_t coordX, uint16_t coordY)
{
	m_coordX = coordX;
	m_coordY = coordY;
	map.SetBlock(Block::Type::NoneBlock, m_coordX, m_coordY);
	if (dynamic_cast<Block*>(map[{m_coordX - 1, m_coordY}])->GetType() == Block::Type::SoftBlock)
		map.SetBlock(Block::Type::NoneBlock, m_coordX - 1, m_coordY);
	if (dynamic_cast<Block*>(map[{m_coordX + 1, m_coordY}])->GetType() == Block::Type::SoftBlock)
		map.SetBlock(Block::Type::NoneBlock, m_coordX + 1, m_coordY);
	if (dynamic_cast<Block*>(map[{m_coordX, m_coordY - 1}])->GetType() == Block::Type::SoftBlock)
		map.SetBlock(Block::Type::NoneBlock, m_coordX, m_coordY - 1);
	if (dynamic_cast<Block*>(map[{m_coordX, m_coordY + 1}])->GetType() == Block::Type::SoftBlock)
		map.SetBlock(Block::Type::NoneBlock, m_coordX, m_coordY + 1);
}

void Player::Move(Map& map, char ch)
{
	switch (ch)
	{
	case 'W':
	case 'w':
	{
		if (dynamic_cast<Powers*>(map[{m_coordX - 1, m_coordY}]))
		{
			if (dynamic_cast<Powers*>(map[{m_coordX - 1, m_coordY}])->GetPowerStatus() == 0 || m_softBlockPass)
			{
				if (dynamic_cast<Powers*>(map[{m_coordX - 1, m_coordY}])->GetPowerStatus() == 0)
				{
					UpdatePlayerPower(dynamic_cast<Powers*>(map[{m_coordX - 1, m_coordY}])->GetPowerType());
					map.SetBlock(Block::Type::NoneBlock, m_coordX - 1, m_coordY);
				}
				m_lastX = m_coordX;
				m_lastY = m_coordY;
				--m_coordX;
			}
		}
		else
		if (dynamic_cast<Block*>(map[{m_coordX - 1, m_coordY}])->GetType() == Block::Type::NoneBlock || 
			dynamic_cast<Block*>(map[{m_coordX - 1, m_coordY}])->GetType() == Block::Type::SoftBlock && m_softBlockPass || 
			dynamic_cast<Block*>(map[{m_coordX - 1, m_coordY}])->GetType() == Block::Type::Exit &&
			(dynamic_cast<Block*>(map[{m_coordX - 1, m_coordY}])->GetExitStatus() == 0 || m_softBlockPass))
		{
			bool ok = 1;
			if (!m_bombPass)
				for (int index = 0; index < m_placedBombs.size(); ++index)
					if (m_placedBombs[index]->GetCoordX() == m_coordX - 1 && m_placedBombs[index]->GetCoordY() == m_coordY)
						ok = 0;
			if (ok)
			{
				m_lastX = m_coordX;
				m_lastY = m_coordY;
				--m_coordX;
			}
		}
	}
	break;
	case 'A':
	case 'a':
	{
		if (dynamic_cast<Powers*>(map[{m_coordX , m_coordY-1}]))
		{
			if (dynamic_cast<Powers*>(map[{m_coordX, m_coordY-1}])->GetPowerStatus() == 0 || m_softBlockPass)
			{
				if (dynamic_cast<Powers*>(map[{m_coordX, m_coordY - 1}])->GetPowerStatus() == 0)
				{
					UpdatePlayerPower(dynamic_cast<Powers*>(map[{m_coordX, m_coordY - 1}])->GetPowerType());
					map.SetBlock(Block::Type::NoneBlock, m_coordX, m_coordY - 1);
				}
				m_lastX = m_coordX;
				m_lastY = m_coordY;
				--m_coordY;
			}
		}
		else
		if (dynamic_cast<Block*>(map[{m_coordX, m_coordY - 1}])->GetType() == Block::Type::NoneBlock ||
			dynamic_cast<Block*>(map[{m_coordX, m_coordY - 1}])->GetType() == Block::Type::SoftBlock && m_softBlockPass ||
			dynamic_cast<Block*>(map[{m_coordX, m_coordY - 1}])->GetType() == Block::Type::Exit &&
			(dynamic_cast<Block*>(map[{m_coordX, m_coordY - 1}])->GetExitStatus() == 0 || m_softBlockPass))

		{
			bool ok = 1;
			if (!m_bombPass)
				for (int index = 0; index < m_placedBombs.size(); ++index)
					if (m_placedBombs[index]->GetCoordX() == m_coordX && m_placedBombs[index]->GetCoordY() == m_coordY - 1)
						ok = 0;
			if (ok)
			{
				m_lastY = m_coordY;
				m_lastX = m_coordX;
				--m_coordY;
			}
		}
	}
	break;
	case 's':
	case 'S':
	{
		if (dynamic_cast<Powers*>(map[{m_coordX + 1, m_coordY}]))
		{
			if (dynamic_cast<Powers*>(map[{m_coordX + 1, m_coordY}])->GetPowerStatus() == 0 || m_softBlockPass)
			{
				if (dynamic_cast<Powers*>(map[{m_coordX + 1, m_coordY}])->GetPowerStatus() == 0)
				{
					UpdatePlayerPower(dynamic_cast<Powers*>(map[{m_coordX + 1, m_coordY}])->GetPowerType());
					map.SetBlock(Block::Type::NoneBlock, m_coordX + 1, m_coordY);
				}
				m_lastX = m_coordX;
				m_lastY = m_coordY;
				++m_coordX;
			}
		}
		else
		if (dynamic_cast<Block*>(map[{m_coordX + 1, m_coordY}])->GetType() == Block::Type::NoneBlock ||
			dynamic_cast<Block*>(map[{m_coordX + 1, m_coordY}])->GetType() == Block::Type::SoftBlock && m_softBlockPass ||
			dynamic_cast<Block*>(map[{m_coordX + 1, m_coordY}])->GetType() == Block::Type::Exit &&
			(dynamic_cast<Block*>(map[{m_coordX + 1, m_coordY}])->GetExitStatus() == 0 || m_softBlockPass))

		{
			bool ok = 1;
			if (!m_bombPass)
				for (int index = 0; index < m_placedBombs.size(); ++index)
					if (m_placedBombs[index]->GetCoordX() == m_coordX + 1 && m_placedBombs[index]->GetCoordY() == m_coordY)
						ok = 0;
			if (ok)
			{
				m_lastX = m_coordX;
				m_lastY = m_coordY;

				++m_coordX;
			}
		}
	}
	break;
	case 'D':
	case 'd':
	{
		if (dynamic_cast<Powers*>(map[{m_coordX, m_coordY + 1}]))
		{
			if (dynamic_cast<Powers*>(map[{m_coordX, m_coordY + 1}])->GetPowerStatus() == 0 || m_softBlockPass)
			{
				if (dynamic_cast<Powers*>(map[{m_coordX, m_coordY + 1}])->GetPowerStatus() == 0)
				{
					UpdatePlayerPower(dynamic_cast<Powers*>(map[{m_coordX, m_coordY + 1}])->GetPowerType());
					map.SetBlock(Block::Type::NoneBlock, m_coordX, m_coordY + 1);
				}
				m_lastX = m_coordX;
				m_lastY = m_coordY;
				++m_coordY;
			}
		}
		else
		if (dynamic_cast<Block*>(map[{m_coordX, m_coordY + 1}])->GetType() == Block::Type::NoneBlock ||
			dynamic_cast<Block*>(map[{m_coordX, m_coordY + 1}])->GetType() == Block::Type::SoftBlock && m_softBlockPass ||
			dynamic_cast<Block*>(map[{m_coordX, m_coordY + 1}])->GetType() == Block::Type::Exit &&
			(dynamic_cast<Block*>(map[{m_coordX, m_coordY + 1}])->GetExitStatus() == 0 || m_softBlockPass))
		{
			bool ok = 1;
			if (!m_bombPass)
				for (int index = 0; index < m_placedBombs.size(); ++index)
					if (m_placedBombs[index]->GetCoordX() == m_coordX && m_placedBombs[index]->GetCoordY() == m_coordY + 1)
						ok = 0;
			if (ok)
			{
				m_lastY = m_coordY;
				m_lastX = m_coordX;

				++m_coordY;
			}
		}
	}
	break;
	case 'E':
	case 'e':
	{
		// no movement
	}
	break;

	}
}

void Player::PlaceBomb(Map& map)
{
	bool ok = 1;
	for (int index = 0; index < m_placedBombs.size(); ++index)
		if (m_placedBombs[index]->GetCoordX() == m_coordX && m_placedBombs[index]->GetCoordY() == m_coordY)
			ok = 0;
	if (dynamic_cast<Block*>(map[{m_coordX, m_coordY}])->GetType() == Block::Type::Exit)
		ok = 0;
	if (ok) 
	{
		Bomb* bomb= new Bomb(m_coordX, m_coordY, m_placedBombs.size());
		m_placedBombs.push_back(bomb);
		m_noOfBombs--;
	}
}

void Player::DeleteBomb(int bombId)
{
	m_placedBombs.erase(m_placedBombs.begin() + bombId);
	/*delete m_placedBombs[bombId];
	for (int index = bombId; index < m_placedBombs.size() - 1; ++index)
		m_placedBombs[index] = m_placedBombs[index + 1];
	m_placedBombs.resize(m_placedBombs.size() - 1);*/
	m_noOfBombs++;
}

void Player::UpdatePlayerPower( Powers::Power power)
{
	switch (power)
	{
	case Powers::Power::FireUp:
	{
		m_fire++;
	}
	break;
	case Powers::Power::FireDown:
	{
		if (m_fire > 1)
			m_fire--;
	}
	break;
	case Powers::Power::BombUp:
		m_noOfBombs++;
		break;
	case Powers::Power::BombDown:
		if (m_noOfBombs > 0)
			m_noOfBombs--;
		break;
	case Powers::Power::SkateUp:
		if (m_speed < 4)
			m_speed++;
		break;
	case Powers::Power::SkateDown:
		if (m_speed > 1)
			m_speed--;
		break;
	case Powers::Power::SoftBlockPass:
		m_softBlockPass = 1;
		break;
	case Powers::Power::BombPass:
		m_bombPass = 1;
		break;
	case Powers::Power::Heart:
		m_health++;
		break;
	case Powers::Power::Vest:
		m_vest = 1;
		break;
	case Powers::Power::RemoteControl:
		m_remoteControl=1;
		break;
	default:
		break;
	}
}

bool Player::IsOnBomb()
{
	for(int index=0; index<m_placedBombs.size(); ++index)
		if(m_coordX == m_placedBombs[index]->GetCoordX() && m_coordY == m_placedBombs[index]->GetCoordY())
			return true;
	return false;
}

void Player::AddScore(uint16_t value)
{
	m_score += value;
}


void Player::playerIsHitt(Map& map, uint16_t index1, uint16_t index2, uint16_t flame, bool& playerIsHit, uint16_t op)
{
	while (!dynamic_cast<Powers*>(map[{index1, index2}]) &&
		dynamic_cast<Block*>(map[{index1, index2}])->GetType() == Block::Type::NoneBlock &&
		flame != 0)
	{
		bool ok = 0;
		for (int index = 0; index < m_placedBombs.size(); ++index)
			if (m_placedBombs[index]->GetCoordX() == index1 && m_placedBombs[index]->GetCoordY() == index2)
			{
				ExplodeBomb(map, m_placedBombs[index]->GetID());
				ok = 1;
			}
		if(!ok)
		switch (op)
		{
		case 0: map.SetBlock(Block::Type::VerticalFire, index1--, index2);
			break;
		case 1: map.SetBlock(Block::Type::VerticalFire, index1++, index2);
			break;
		case 2: map.SetBlock(Block::Type::HorizontalFire, index1, index2--);
			break;
		case 3: map.SetBlock(Block::Type::HorizontalFire, index1, index2++);
			break;
		default:
			break;
		}
		flame--;
		if (m_coordX == index1 && m_coordY == index2)
			playerIsHit = 1;
	}
	if (dynamic_cast<Powers*>(map[{index1, index2}]))
	{
		if (flame != 0)
			if (dynamic_cast<Powers*>(map[{index1, index2}])->GetPowerStatus() == 1)
				dynamic_cast<Powers*>(map[{index1, index2}])->SetPowerStatus(0);
			else
			{
				switch (op)
				{
				case 0: map.SetBlock(Block::Type::NoneBlock, index1--, index2);
					break;
				case 1: map.SetBlock(Block::Type::NoneBlock, index1++, index2);
					break;
				case 2: map.SetBlock(Block::Type::NoneBlock, index1, index2--);
					break;
				case 3: map.SetBlock(Block::Type::NoneBlock, index1, index2++);
					break;
				default:
					break;
				}
			}

	}
	else
		if (dynamic_cast<Block*>(map[{index1, index2}])->GetType() == Block::Type::SoftBlock && flame != 0)
		{
			switch (op)
			{
			case 0: map.SetBlock(Block::Type::ExplodedBlock, index1--, index2);
				break;
			case 1: map.SetBlock(Block::Type::ExplodedBlock, index1++, index2);
				break;
			case 2: map.SetBlock(Block::Type::ExplodedBlock, index1, index2--);
				break;
			case 3: map.SetBlock(Block::Type::ExplodedBlock, index1, index2++);
				break;
			default:
				break;
			}
		}

		else
			if (dynamic_cast<Block*>(map[{index1, index2}])->GetType() == Block::Type::Exit && flame != 0)
				dynamic_cast<Block*>(map[{index1, index2}])->SetExitStatus(false);

}
bool Player::ExplodeBomb(Map& map, uint16_t bomb)
{
	map.SetBlock(Block::Type::ExplodedBomb, m_placedBombs[bomb]->GetCoordX(), m_placedBombs[bomb]->GetCoordY());
	uint16_t index1 = m_placedBombs[bomb]->GetCoordX();
	uint16_t index2 = m_placedBombs[bomb]->GetCoordY();
	bool playerIsHit = 0;
	if (m_coordX == index1 && m_coordY == index2)
		playerIsHit = 1;
	playerIsHitt(map, index1 - 1, index2, m_fire, playerIsHit, 0);
	playerIsHitt(map, index1 + 1, index2, m_fire, playerIsHit, 1);
	playerIsHitt(map, index1, index2 - 1, m_fire, playerIsHit, 2);
	playerIsHitt(map, index1, index2 + 1, m_fire, playerIsHit, 3);
	DeleteBomb(bomb);

	return playerIsHit;
}


Bomb* Player::operator[](int index)
{
	return m_placedBombs[index];
}

const Bomb* Player::operator[](int index) const
{
	return m_placedBombs[index];
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	return out << "[]";
}
