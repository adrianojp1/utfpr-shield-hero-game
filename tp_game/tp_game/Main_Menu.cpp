// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Main_Menu.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Main_Menu::menu_position = { 0.0f, -300.0f };

const std::string Main_Menu::title_str = "Shield Hero";
const int Main_Menu::title_charSize(150);
sf::Color Main_Menu::title_textColor(sf::Color(255, 255, 255));
sf::Color Main_Menu::title_outLine_color(sf::Color(105, 210, 0));
const float Main_Menu::title_outLine_thickness(10.0f);

const int Main_Menu::ops_act_charSize(120);
const int Main_Menu::ops_deact_charSize(90);

sf::Color Main_Menu::ops_act_fillColor(sf::Color(105, 210, 0)); //Green
sf::Color Main_Menu::ops_deact_fillColor(sf::Color(255, 255, 255)); //White

const std::string Main_Menu::op0_string = "New Game";
const sf::Vector2f Main_Menu::op0_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 1.0f };

const std::string Main_Menu::op1_string = "Load Game";
const sf::Vector2f Main_Menu::op1_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 2.0f };

const std::string Main_Menu::op2_string = "Ranking";
const sf::Vector2f Main_Menu::op2_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 3.0f };

const std::string Main_Menu::op3_string = "Exit";
const sf::Vector2f Main_Menu::op3_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 4.0f };

//======================================================================================================================================//
// === Main_Menu methods === //
Main_Menu::Main_Menu() :
	Menu(menu_position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initializeTitle(title_str, title_charSize, menu_position, title_textColor, title_outLine_color, title_outLine_thickness);
	initializeAllOps();
}

Main_Menu::~Main_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Main_Menu::initializeAllOps()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Option* pOp;

	initialize_n_addOp(pOp, op0_position, op0_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op1_position, op1_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op2_position, op2_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op3_position, op3_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
}

void Main_Menu::execute_onOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	switch (_onOp)
	{
	case 0:
		open_newGame_menu();
		break;
	case 1:
		open_saves_menu();
		break;
	case 2:
		show_ranking();
		break;
	case 3:
		close_game();
		break;
	default:
		break;
	}
}

void Main_Menu::open_newGame_menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

 	Game::getInstance()->open_NewGame_Menu();
}

void Main_Menu::open_saves_menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//_pGame->open_saves_menu();
}

void Main_Menu::show_ranking()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//_pGame->show_ranking();
}

void Main_Menu::close_game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Game::getInstance()->close();
}
