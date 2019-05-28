//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Menu.h"

//======================================================================================================================================//
// === Menu methods === //

Menu::Menu(const sf::Vector2f initPosit, const float keysCD) :
	Entity(initPosit), _betweenKeys(keysCD)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_onOp = 0;
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

void Menu::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
	_onOp = 0;
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

//======================================================================================================================================//
// === Option methods === //

Menu::Option::Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor) :
	Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_charSize_active = actSize;
	_charSize_deactive = deactSize;

	_textColor_active = actColor;
	_textColor_deactive = deactColor;

	this->desactivate();
}

Menu::Option::Option(const std::string label) : Entity(), _text()
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

void Menu::Option::initializeText(sf::Font* font, const std::string label, const sf::Vector2f position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text = new sf::Text(label, *font);
	_text->setPosition(position);
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

void Menu::Option::setPosition(const sf::Vector2f position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_text->setPosition(position);
}

sf::Vector2f Menu::Option::getPosition() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _text->getPosition();
}
