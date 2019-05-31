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

const int Main_Menu::ops_act_charSize(120);
const int Main_Menu::ops_deact_charSize(90);

//const sf::Color Main_Menu::ops_act_fillColor(sf::Color::Red);
//const sf::Color Main_Menu::ops_deact_fillColor(sf::Color::White);

const std::string Main_Menu::op0_string = "New Game";
const sf::Vector2f Main_Menu::op0_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 0.0f };

const std::string Main_Menu::op1_string = "Load Game";
const sf::Vector2f Main_Menu::op1_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 1.0f };

const std::string Main_Menu::op2_string = "Ranking";
const sf::Vector2f Main_Menu::op2_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 2.0f };

const std::string Main_Menu::op3_string = "Exit";
const sf::Vector2f Main_Menu::op3_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 3.0f };

//======================================================================================================================================//
// === Main_Menu methods === //
Main_Menu::Main_Menu() :
	Menu(menu_position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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

	initialize_n_addOp(pOp, op0_position, op0_string, ops_act_charSize, ops_deact_charSize, sf::Color::Red, sf::Color::White);
	initialize_n_addOp(pOp, op1_position, op1_string, ops_act_charSize, ops_deact_charSize, sf::Color::Red, sf::Color::White);
	initialize_n_addOp(pOp, op2_position, op2_string, ops_act_charSize, ops_deact_charSize, sf::Color::Red, sf::Color::White);
	initialize_n_addOp(pOp, op3_position, op3_string, ops_act_charSize, ops_deact_charSize, sf::Color::Red, sf::Color::White);
}

void Main_Menu::activate_onOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	switch (_onOp)
	{
	case 0:
		_vOptions[0]->activate();
		break;
	case 1:
		_vOptions[1]->activate();
		break;
	case 2:
		_vOptions[2]->activate();
		break;
	case 3:
		_vOptions[3]->activate();
		break;
	default:
		break;
	}
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

	//_pGame->open_newGame_menu();
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

	_pGame->close();
}