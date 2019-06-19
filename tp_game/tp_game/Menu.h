#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h"		//Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Main_Menu
// NewGame_Menu
// Pause_Menu
// Saves_Menu

//======================================================================================================================================//
// === Menu Class === //
class Menu : public Abstract_Entity
{
protected:
	//Menu option class
	class Option : public Abstract_Entity
	{
	protected:
		sf::Text* _text;

		int _charSize_active;
		int _charSize_deactive;

		sf::Color _textColor_active;
		sf::Color _textColor_deactive;

	public:
		// ========== Constructors ========== //
		Option(sf::Font* font, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor);
		Option();
		// ========== Destructors ========== //
		virtual ~Option();

		// ========== Initializers ========== //
		virtual void initializeText(sf::Font* font, const std::string label);

		// ========== Loop methods ========== //
		virtual void execute(const float deltaTime);
		virtual void draw();

		// ========== Activation methods ========== //
		virtual void activate();
		virtual void desactivate();

		// ========== Sets & Gets ========== //
		//_text
		virtual void setText(sf::Text* text);
		virtual sf::Text* getText();
	};

	//Vector for menu options 
	std::vector<Option*> _vOptions;

	Timer _betweenKeys; //Timer for delaying the key pressing
	int _onOp;
	int _nOps;

	//Animator* _animator; //Wallpaper?
public:
	//================================================================//
	// ========== Constructors ========== //
	Menu(const sf::Vector2f initPosition);
	Menu();
	// ========== Destructors ========== //
	virtual ~Menu();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initializeAllOps() = 0;
	virtual void initialize_n_addOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font = menu_font);
	virtual void initializeOp(Option*& pOp, const sf::Vector2f position, const std::string label, const int actSize, const int deactSize, sf::Color actColor, sf::Color deactColor, sf::Font* font = menu_font);
	
	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	// ========== Selection methods ========== //
	virtual void activate_onOp();
	virtual void execute_onOp() = 0;

	// ========== Activation methods ========== //
	virtual void close();
	virtual void open();

	virtual bool isOpen();

	// ========== Option methods ========== //
	virtual void add_option(Option* pOp);
	virtual void operator<<(Option* pOp);

	virtual void deactivate_allOps();

	virtual void upOp();
	virtual void downOp();

	virtual void check_allKeys();
	virtual bool selectionKey_isPressed();
	virtual bool upKey_isPressed();
	virtual bool downKey_isPressed();

	//================================================================//
	//======================== Static Consts =========================//
private:
	// ========== Menu ========== //
	static const float keysCD;
	static sf::Font* menu_font;
};
