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
	_onOp = 0;
}

Menu::Menu() : Entity(), _betweenKeys()
{
	_onOp = 0;
}

Menu::~Menu()
{
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

void Menu::draw(Graphical_Manager* window) const
{
	//window->draw(*_animator->getpSprite());
	/*for (int i = 0; i < _vOptions.size(); i++)
	{
		_vOptions[i]->draw(window);
	}
	*/
	for (Option* option : _vOptions)
	{
		option->draw(window);
	}
}

void Menu::activate()
{
	_active = true;
	_onOp = 0;
}

void Menu::add_option(Option* pOp)
{
	if (pOp)
		_vOptions.push_back(pOp);
}

void Menu::operator<<(Option* pOp)
{
	if (pOp)
		add_option(pOp);
}

//======================================================================================================================================//
// === Option methods === //

Menu::Option::Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor) :
	Entity()
{
	_charSize_active = actSize;
	_charSize_deactive = deactSize;

	_textColor_active = actColor;
	_textColor_deactive = deactColor;

	this->desactivate();
}

Menu::Option::Option(const std::string label) : Entity(), _text()
{
	_text = NULL;

	_charSize_active = 0;
	_charSize_deactive = 0;

	_textColor_active = sf::Color::White;
	_textColor_deactive = sf::Color::White;
}

Menu::Option::~Option()
{
}

void Menu::Option::initializeText(sf::Font* font, const std::string label, const sf::Vector2f position)
{
	_text = new sf::Text(label, *font);
	_text->setPosition(position);
}

void Menu::Option::execute(const float deltaTime)
{
}

void Menu::Option::draw(Graphical_Manager* window) const
{
	window->draw(*_text);
}

void Menu::Option::activate()
{
	_active = true;
	_text->setFillColor(_textColor_active);
	_text->setCharacterSize(_charSize_active);
}

void Menu::Option::desactivate()
{
	_active = false;
	_text->setFillColor(_textColor_deactive);
	_text->setCharacterSize(_charSize_deactive);
}

void Menu::Option::setText(sf::Text* text)
{
	_text = text;
}

sf::Text* Menu::Option::getText()
{
	return _text;
}

void Menu::Option::setPosition(const sf::Vector2f position)
{
	_text->setPosition(position);
}

sf::Vector2f Menu::Option::getPosition() const
{
	return _text->getPosition();
}
