#pragma once
#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h" //base class
#include "Player.h"
#include "Orc.h"
#include "Block.h"
#include "WhiteSkeleton.h"
#include "BlackSkeleton.h"
#include "Projectile.h"

//======================================================================================================================================//
// === Stage Class === //
class Stage : public Abstract_Entity
{
protected:
	sf::RectangleShape* _background;
	sf::Texture* _bgtexture;
	std::vector<Block*> _vBlocks;
	Orc* _orc;
	WhiteSkeleton* _WSklt;
	BlackSkeleton* _BSklt;
	Projectile* _WSproj;



	Player* _pPlayer1;
	Player* _pPlayer2;

public:
	// ========== Constructors ========== //
	Stage(Player* pP1 = NULL, Player* pP2 = NULL);
	//Stage();
	// ========== Destructors ========== //
	virtual ~Stage();

	// ========== Initializers ========== //
	virtual void initializeStage();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw() const;

	// ========== Players methods ========== //
	virtual void executePlayers(const float deltaTime);
	virtual void drawPlayers() const;

	// ========== State ========== //
	virtual void pause();
	virtual void unpause();
	virtual bool isPaused();
	virtual void check_pauseKey();
	virtual bool pauseKey_isPressed();

	// ========== Sets & Gets ========== //
	virtual void setPlayer1(Player* pP1);
	virtual Player* getPlayer1();
	virtual void setPlayer2(Player* pP2);
	virtual Player* getPlayer2();

	// ========== Collision Management ========== //
	virtual void manage_collisions();
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
};

