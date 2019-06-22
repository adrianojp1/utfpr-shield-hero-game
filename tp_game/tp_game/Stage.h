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
	int _currentScenarioId;

	int _nObstacles;
	int _nEnemies;

public:
	// ========== Constructors ========== //
	Stage();
	// ========== Destructors ========== //
	virtual ~Stage();

	// ========== Initializers ========== //
	virtual void initializeStage();

	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	// ========== State ========== //
	virtual void pause();
	virtual void unpause();
	virtual bool isPaused();
	virtual void check_pauseKey();
	virtual bool pauseKey_isPressed();

	// ========== Sets & Gets ========== //
	virtual const std::string get_stg_fp(const int stg_id) const;
	virtual const std::string get_lv_fp(const int stg_id, const int lv_id) const;
};
