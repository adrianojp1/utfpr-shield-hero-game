//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Weak_Stone
// Static_Spike

//======================================================================================================================================//
// === Character Class === //
class Obstacle : public Entity
{
protected:
	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _obs_collider;

	Timer _cd_action;

	int _state;

public:
	//================================================================//
	// ========== Constructors ========== //
	Obstacle(const sf::Vector2f initPosition);
	Obstacle();

	// ========== Destructors ========== //
	virtual ~Obstacle();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_AllColliders();
	virtual void initialize_animator() = 0;

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw() const;

	//================================================================//
	// ========== Motion ========== //
	virtual void updateAction(const float deltaTime);
	virtual void updatePosition(const float deltaTime);
};

