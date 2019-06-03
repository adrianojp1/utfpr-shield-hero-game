#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Graphical_Manager.h"
#include "Player.h"
#include "Orc.h"
#include "Block.h"
#include "Main_Menu.h"

//======================================================================================================================================//
// === Game Class === //
class Game
{
private:
	Graphical_Manager* _window;

	Main_Menu* _main_menu;
	//Pause_Menu* _pause_menu;
	//NewGame_Menu* _newGame_menu;
	//Saves_Menu* _saves_menu;

	Player* _player1;
	//Player* _player2;

	//Stage1* _stage1;
	//Stage1* _stage2;

	//Time control
	float _deltaTime;
	sf::Clock _clock; //To get the deltaTime

	//Temporary
	sf::RectangleShape* _background;
	sf::Texture* _bgtexture;
	std::vector<Block*> _vBlocks;
	Orc* _orc;
public:
	//================================================================//
	// ========== Constructors ========== //
	Game();
	// ========== Destructors ========== //
	~Game();

	//================================================================//
	// ========== Initializers ========== //
	void initialize();

	//================================================================//
	void main_loop();
	void close();

	//================================================================//
	// ========== Loop methods ========== //
	void execute(float deltaTime);
	void draw() const;

	//================================================================//
	//Temporary methods
	bool checkCollision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* collisionDirection, float push);
	bool checkCollision(Entity* ent1, Entity* ent2);
	void executeStage(float deltaTime);
};