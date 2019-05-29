//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Menu.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Static initializations === //
Game* Menu::_pGame = NULL;
const float Menu::keysCD = 0.010f;
sf::Font* Menu::menu_font = NULL;

//======================================================================================================================================//
// === Menu methods === //

Menu::Menu(const sf::Vector2f initPosit) :
	Entity(initPosit), _betweenKeys(keysCD)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_onOp = 0;
	if (!menu_font)
	{
		menu_font = new sf::Font;
		if(!menu_font->loadFromFile(gMng::menu_Ft_Fp))
			getchar();
	}
}

Menu::Menu() : Entity(), _betweenKeys()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_onOp = 0;
}

Menu::~Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	/*for (int i = 0; i < _vOptions.size(); i++)
	{
		if (_vOptions[i])
			delete _vOptions[i];
	}
	*/
	for (Option* option : _vOptions)
	{
		if (option)
			delete option;
	}
	_vOptions.clear();
}

void Menu::initialize_n_addOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font)
{
	initializeOp(pOp, position, label, actSize, deactSize, actColor, deactColor);
	this->operator<<(pOp);
}

void Menu::initializeOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font)
{
	pOp = new Option(font, position, label, actSize, deactSize, actColor, deactColor);
}

void Menu::execute(const float deltaTime)
{
	if (this->isActive())
	{
		desactivate_allOps();

		activate_onOp();

		if (selectionKey_isPressed())
		{
			execute_onOp();
			this->close();
		}
	}
}

void Menu::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//window->draw(*_animator->getpSprite());
	/*for (int i = 0; i < _vOptions.size(); i++)
	{
		_vOptions[i]->draw(window);
	}
	*/
	for (Option* option : _vOptions)
	{
		option->draw();
	}
}

bool Menu::selectionKey_isPressed()
{
	return(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
}

void Menu::close()
{
	this->desactivate();
}

void Menu::open()
{
	this->activate();
}

void Menu::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
	_onOp = 0;
}
/*
void Menu::execute_allOps()
{
	for (Option* option : _vOptions)
	{
		option->execute();
	}
}*/

void Menu::desactivate_allOps()
{
	for (Option* option : _vOptions)
	{
		option->desactivate();
	}
}

void Menu::add_option(Option* pOp)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (pOp)
		_vOptions.push_back(pOp);
}

void Menu::operator<<(Option* pOp)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (pOp)
		add_option(pOp);
}

void Menu::setpGame(Game* pGame)
{
	_pGame = pGame;
}

Game* Menu::getpGame()
{
	return _pGame;
}

//======================================================================================================================================//
// === Option methods === //

Menu::Option::Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor) :
	Entity(position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_charSize_active = actSize;
	_charSize_deactive = deactSize;

	_textColor_active = actColor;
	_textColor_deactive = deactColor;

	initializeText(font, label); //position 
	this->desactivate();
}

Menu::Option::Option() : Entity(), _text()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_text = NULL;

	_charSize_active = 0;
	_charSize_deactive = 0;

	_textColor_active = sf::Color::White;
	_textColor_deactive = sf::Color::White;
}

Menu::Option::~Option()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Menu::Option::initializeText(sf::Font* font, const std::string label)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text = new sf::Text(label, *font);
	_text->setPosition(this->getPosition());
}

void Menu::Option::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Menu::Option::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Entity::_pGraphMng->draw(*_text);
}

void Menu::Option::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
	_text->setFillColor(_textColor_active);
	_text->setCharacterSize(_charSize_active);
}

void Menu::Option::desactivate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = false;
	_text->setFillColor(_textColor_deactive);
	_text->setCharacterSize(_charSize_deactive);
}

void Menu::Option::setText(sf::Text* text)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text = text;
}

sf::Text* Menu::Option::getText()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _text;
}