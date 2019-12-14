#pragma once
#include"State.h"

class GameState :
	public State
{
private:

public :
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void endStates();
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
};

