// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "NewGame_Menu.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f NewGame_Menu::menu_position = { 0.0f, -300.0f };

const std::string NewGame_Menu::title_str = "- New Game -";
const int NewGame_Menu::title_charSize(140);
sf::Color NewGame_Menu::title_textColor(sf::Color(255, 255, 255));
sf::Color NewGame_Menu::title_outLine_color(sf::Color(105, 210, 0));
const float NewGame_Menu::title_outLine_thickness(5.0f);

const int NewGame_Menu::ops_act_charSize(120);
const int NewGame_Menu::ops_deact_charSize(90);

sf::Color NewGame_Menu::ops_act_fillColor(sf::Color(105, 210, 0)); //Green
sf::Color NewGame_Menu::ops_deact_fillColor(sf::Color(255, 255, 255)); //White

const std::string NewGame_Menu::op0_string = "1 Player";
const sf::Vector2f NewGame_Menu::op0_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 1.0f };

const std::string NewGame_Menu::op1_string = "2 Players";
const sf::Vector2f NewGame_Menu::op1_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 2.0f };
/*
const std::string NewGame_Menu::op2_string = "Ranking";
const sf::Vector2f NewGame_Menu::op2_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 3.0f };

const std::string Main_Menu::op3_string = "Exit";
const sf::Vector2f Main_Menu::op3_position = menu_position + sf::Vector2f{ 0.0f, (float)ops_act_charSize * 4.0f };
*/
//======================================================================================================================================//
// === NewGame_Menu methods === //

NewGame_Menu::NewGame_Menu() : Menu(menu_position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	initializeTitle(title_str, title_charSize, menu_position, title_textColor, title_outLine_color, title_outLine_thickness);
	initializeAllOps();
}

NewGame_Menu::~NewGame_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void NewGame_Menu::initializeAllOps()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Option* pOp;

	initialize_n_addOp(pOp, op0_position, op0_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
	initialize_n_addOp(pOp, op1_position, op1_string, ops_act_charSize, ops_deact_charSize, ops_act_fillColor, ops_deact_fillColor);
}

void NewGame_Menu::execute_onOp()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	switch (_onOp)
	{
	case 0:
		set_1player();
		break;
	case 1:
		set_2players();
		break;
	default:
		break;
	}
}

void NewGame_Menu::set_1player()
{
	Game::getInstance()->set_nPlayers(1);
	set_n_run_stage1();
}

void NewGame_Menu::set_2players()
{
	Game::getInstance()->set_nPlayers(2);
	set_n_run_stage1();
}

void NewGame_Menu::set_n_run_stage1()
{
	Game::getInstance()->initialize_stage1();
	Game::getInstance()->set_currentStage(1);
	Game::getInstance()->run_stage();
}

void NewGame_Menu::exit()
{
	Game::getInstance()->open_Main_Menu();
}
