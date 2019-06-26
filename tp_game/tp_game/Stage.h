#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Level.h"

//======================================================================================================================================//
// === Stage Class === //
class Stage : public Abstract_Entity
{
protected:
	std::vector<Level*> _vLevels;
	unsigned int _currentLevel_index;

	int _nObstacles;
	int _nEnemies;

	int _nPlayers;
	bool _running;

public:
	// ========== Constructors ========== //
	Stage(const int id = 1, const int nPlayers = 1);
	// ========== Destructors ========== //
	virtual ~Stage();

	// ========== Initializers ========== //
	virtual void initializeLevels(Stage* pStage, int nLevels = 1);

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	// ========== State ========== //
	virtual void start();
	virtual void stop();
	virtual bool isRunning();
	virtual void pause();
	virtual void unpause();
	virtual bool isPaused();
	virtual void check_pauseKey();
	virtual bool pauseKey_isPressed();
	virtual Enemy* get_an_enemy(sf::Vector2f pos) = 0;
	virtual Obstacle* get_spike(sf::Vector2f pos) = 0;
	virtual void goToNextLevel();
	// ========== Sets & Gets ========== //
	virtual const std::string get_stg_fp(const int stg_id) const;
	virtual const std::string get_lv_fp(const int stg_id, const int lv_id) const;

	virtual const int get_lv_id() const;
	virtual void set_lv_id(const int lv_id);
	virtual void start_currentLv();
};
