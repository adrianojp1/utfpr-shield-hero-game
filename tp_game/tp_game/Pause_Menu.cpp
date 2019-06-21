// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Pause_Menu.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Pause_Menu::menu_position = { 0.0f, -300.0f };

const std::string Pause_Menu::title_str = "- Pause -";
const int Pause_Menu::title_charSize(140);
sf::Color Pause_Menu::title_textColor(sf::Color(255, 255, 255));
sf::Color Pause_Menu::title_outLine_color(sf::Color(105, 210, 0));
const float Pause_Menu::title_outLine_thickness(5.0f);

const int Pause_Menu::ops_act_charSize(120);
const int Pause_Menu::ops_deact_charSize(90);

sf::Color Pause_Menu::ops_act_fillColor(sf::Color(105, 210, 0)); //Green
sf::Color Pause_Menu::ops_deact_fillColor(sf::Color(255, 255, 255)); //White

const std::string Pause_Menu::op0_string = "Continue";
const sf::Vector2f Pause_Menu::op0_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 1.0f };

const std::string Pause_Menu::op1_string = "Save";
const sf::Vector2f Pause_Menu::op1_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 2.0f };

const std::string Pause_Menu::op2_string = "Exit to main menu";
const sf::Vector2f Pause_Menu::op2_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 3.0f };
/*
const std::string Main_Menu::op3_string = "Exit";
const sf::Vector2f Main_Menu::op3_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 3.0f };
*/
//======================================================================================================================================//
// === Pause_Menu methods === //

Pause_Menu::Pause_Menu() : Menu(menu_position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	initializeTitle(title_str, title_charSize, menu_position, title_textColor, title_outLine_color, title_outLine_thickness);
	initializeAllOps();
}

Pause_Menu::~Pause_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Pause_Menu::initializeAllOps()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Option* pOp;

	initialize_n_addOp(pOp, op0_position, op0_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op1_position, op1_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op2_position, op2_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
}

void Pause_Menu::execute_onOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	switch (_onOp)
	{
	case 0:
		unpause_game();
		break;

	case 1:
		save_game();
		break;

	case 2:
		exit_to_main_menu();
		break;

	default:
		break;
	}
}

void Pause_Menu::unpause_game()
{
	Game::getInstance()->unpause_stage();
}

void Pause_Menu::save_game()
{
	//_pGame->save_currentStage();
}

void Pause_Menu::exit_to_main_menu()
{
	Game::getInstance()->open_Main_Menu();
	Game::getInstance()->stop_runningStage();
}
