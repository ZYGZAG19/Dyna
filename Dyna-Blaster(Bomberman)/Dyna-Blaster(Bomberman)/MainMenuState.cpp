#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	/*if (!m_font.loadFromFile("Fonts\Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}*/
}

void MainMenuState::InitKeyBinds()
{
	/*m_keyBinds.emplace("MOVE_LEFT", this->suportedKeys->at("A"));
	m_keyBinds.emplace("MOVE_RIGHT", this->suportedKeys->at("D"));
	m_keyBinds.emplace("MOVE_UP", this->suportedKeys->at("W"));
	m_keyBinds.emplace("MOVE_DOWN", this->suportedKeys->at("S"));*/
}

void MainMenuState::InitButtons()
{
	m_buttons["GAME_STATE"] = new Button(m_window->getSize().x / 2 - 75, m_window->getSize().y / 2 + 30, 150, 50,
		&m_font, "New Game",
		sf::Color(10, 10, 10, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_buttons["BATTLE_STATE"] = new Button(m_window->getSize().x / 2 - 75, m_window->getSize().y / 2 + 81, 150, 50,
		&m_font, "Battle",
		sf::Color(10, 10, 10, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_buttons["SETUP_STATE"] = new Button(m_window->getSize().x / 2 - 75, m_window->getSize().y / 2 + 132, 150, 50,
		&m_font, "Setup",
		sf::Color(10, 10, 10, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	m_buttons["PASSWORD_STATE"] = new Button(m_window->getSize().x / 2 - 75, m_window->getSize().y / 2 + 183, 150, 50,
		&m_font, "Password",
		sf::Color(10, 10, 10, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suportedKeys, std::stack<State*>* states)
	:State(window, suportedKeys, states)
{
	this->initFonts();
	this->InitKeyBinds();
	this->InitButtons();

	m_background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	m_background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuStates!" << std::endl;
}

void MainMenuState::UpdateInput(const float& dt)
{
	this->CheckForQuit();
}

void MainMenuState::UpdateButtons()
{
	for (auto& it : m_buttons)
	{
		it.second->update(m_mousePosView);
	}

	if (m_buttons["GAME_STATE"]->isPressed())
	{
		m_states->push(new GameState(m_window, m_suportedKeys, m_states));
	}
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePositions();
	this->UpdateInput(dt);
	this->UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : m_buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;
	target->draw(m_background);
	RenderButtons(target);
}