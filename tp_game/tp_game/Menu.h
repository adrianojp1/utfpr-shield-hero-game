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
protected:
	//Menu option class
	class Option : public Entity
	{
	private:
		sf::Text* _text;

		int _charSize_active;
		int _charSize_deactive;

		sf::Color _textColor_active;
		sf::Color _textColor_deactive;

	public:
		// ========== Constructors ========== //
		Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor);
		Option(const std::string label = "");
		// ========== Destructors ========== //
		virtual ~Option();

		// ========== Initializers ========== //
		virtual void initializeText(sf::Font* font, const std::string label, const sf::Vector2f position);

		// ========== Loop methods ========== //
		virtual void execute(const float deltaTime);
		virtual void draw(MyWindow* window) const;

		// ========== Activation methods ========== //
		virtual void activate();
		virtual void desactivate();

		// ========== Sets & Gets ========== //
		//_text
		virtual void setText(sf::Text* text);
		virtual sf::Text* getText();
		//_position
		virtual void setPosition(const sf::Vector2f position);
		virtual sf::Vector2f getPosition() const;
	};

	//Vector for menu options 
	std::vector<Option*> _vOptions;

	Timer _betweenKeys;
	int _onOp;

	//Animator* _animator; //Wallpaper?
public:
	//================================================================//
	// ========== Constructors ========== //
	Menu(const sf::Vector2f initPosit, const float keysCD);
	Menu();
	// ========== Destructors ========== //
	virtual ~Menu();

	//================================================================//
	// ========== Initializers ========== //
	
	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw(MyWindow* window) const;

	// ========== Activation methods ========== //
	virtual void activate();
	//virtual void desactivate();

	// ========== Option methods ========== //
	virtual void add_option(Option* pOp);
	virtual void operator<<(Option* pOp);
};
