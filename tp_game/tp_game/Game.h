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
	void executeStage(float deltaTime);

	void manage_collisions();
	bool check_collision(Entity* ent1, Entity* ent2);
	bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
};