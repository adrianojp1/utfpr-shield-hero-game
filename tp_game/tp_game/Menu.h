#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h"		//Base class

//======================================================================================================================================//
// === Classes Declaration === //

//======================================================================================================================================//
// === Derived classes from this === //
// Main_Menu
// nPlayers_Menu
// Pause_Menu
// Saves_Menu

class Menu : public Entity
{
private:
	//Menu option class
	class Option
	{
		sf::Text _text;
		std::string _label;
		sf::Vector2f _position; //relative to menu position
	};

	//Vector for menu options 
	std::vector<Option*> _menuOptions;

	Timer _betweenKeys;
	int _onOp;

	int _opsSize;
	sf::Font _opsFont;
	sf::Color _opsSelected_color;
	sf::Color _opsDefault_color;
public:
	//================================================================//
	// ========== Constructors ========== //
	Menu();
	// ========== Destructors ========== //
	virtual ~Menu();

	//================================================================//
	// ========== Initializers ========== //
	
	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw(MyWindow* window) const = 0;

	void add_option(Option* pOp);

	void operator<<(Option* pOp);
};
