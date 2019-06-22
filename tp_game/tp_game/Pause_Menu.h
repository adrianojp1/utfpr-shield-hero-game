#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Menu.h" //base class

//======================================================================================================================================//
// === NewGame_Menu Class === //
class Pause_Menu :
	public Menu
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Pause_Menu();

	// ========== Destructors ========== //
	virtual ~Pause_Menu();

	//================================================================//
	// ========== Initializers ========== //
	void initializeAllOps();

	//================================================================//
	// ========== Selection methods ========== //
	void execute_onOp();

	//================================================================//
	// ========== Options methods ========== //
	void unpause_game();
	void save_game();
	void exit_to_main_menu();

	//================================================================//
	//======================== Static Consts =========================//
private:
	// ========== NewGame_Menu ========== //
	static const sf::Vector2f menu_position;

	static const std::string title_str;
	static const int title_charSize;
	static sf::Color title_textColor;
	static sf::Color title_outLine_color;
	static const float title_outLine_thickness;

	static const int ops_act_charSize;
	static const int ops_deact_charSize;

	static sf::Color ops_act_fillColor;
	static sf::Color ops_deact_fillColor;

	// ========== Options ========== //
	//op0
	static const std::string op0_string;
	static const sf::Vector2f op0_position;
	//op1
	static const std::string op1_string;
	static const sf::Vector2f op1_position;
	//op2
	static const std::string op2_string;
	static const sf::Vector2f op2_position;
	/*
	//op3
	static const std::string op3_string;
	static const sf::Vector2f op3_position;
	*/
};

