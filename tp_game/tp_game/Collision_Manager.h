#pragma once
//======================================================================================================================================//
// === Classes Declaration === //
//Entities
class Entity;
class Player;
class Enemy;
class Obstacle;
class Tile;
class Projectile;

//Lists
class Tile_List;
class Enemy_List;
class Obstacle_List;
class Projectile_List;

//======================================================================================================================================//
// === Collision_Manager Class === //
typedef class Collision_Manager
{
private:
	static Collision_Manager* _instance;

private:
	//================================================================//
	// ========== Constructors ========== //
	Collision_Manager();
public:
	// ========== Destructors ========== //
	virtual ~Collision_Manager();

	// ========== Singleton ========== //
	static Collision_Manager* getInstance();

	// ========== Collisions ========== //
	//Single collisions
	void collide(Player* pPlayer, Tile* pTile);
	void collide(Player* pPlayer, Enemy* pEnemy);
	void collide(Player* pPlayer, Obstacle* pObstacle);
	void collide(Player* pPlayer, Projectile* pProjectile);
	void collide(Enemy* pEnemy, Tile* pTile);
	void collide(Enemy* pEnemy, Obstacle* pObstacle);
	void collide(Enemy* pEnemy, Projectile* pProjectile);
	void collide(Obstacle* pObstacle, Tile* pTile);

	//Lists collisions
	void collide(Player* pPlayer, Tile_List* t_list);
	void collide(Player* pPlayer, Enemy_List* e_list);
	void collide(Player* pPlayer, Obstacle_List* o_list);
	void collide(Player* pPlayer, Projectile_List* p_list);
	void collide(Enemy_List* e_list, Tile_List* t_list);
	void collide(Enemy_List* e_list, Obstacle_List* o_list);
	void collide(Enemy_List* e_list, Projectile_List* p_list);
	void collide(Obstacle_List* o_list, Tile_List* t_list);

	// ========== Collision Management ========== //
	virtual bool check_collision(Entity* ent1, Entity* ent2);
	virtual bool check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual bool check_collision(sf::RectangleShape* rect1, sf::RectangleShape* rect2, sf::Vector2f* intersection, sf::Vector2f* coll_direction);
	virtual void push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push);
	virtual bool contains(Entity* ent, sf::Vector2f point);
	virtual bool intersects(Entity* ent, sf::RectangleShape* rect);
	virtual bool intersects(Entity* ent, sf::RectangleShape* rect, sf::Vector2f* coll_direction);
} cMng;