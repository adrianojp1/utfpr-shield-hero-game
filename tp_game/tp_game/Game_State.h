#pragma once

//======================================================================================================================================//
// === Game_State Class === //
class Game_State
{
protected:
	void changeState(Game_State* pState);
public:
	//================================================================//
	// ========== Constructors ========== //
	Game_State();
	// ========== Destructors ========== //
	virtual ~Game_State();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() = 0;
};

//======================================================================================================================================//
// === RunningStage Class === //
class RunningStage : public Game_State
{
private:
	static Game_State* _instance;
protected:
	//================================================================//
	// ========== Constructors ========== //
	RunningStage();
public:
	// ========== Destructors ========== //
	virtual ~RunningStage();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	// ========== Singleton methods ========== //
	static Game_State* getInstance();
};

//======================================================================================================================================//
// === On_MainMenu Class === //
class On_MainMenu : public Game_State
{
private:
	static Game_State* _instance;
protected:
	//================================================================//
	// ========== Constructors ========== //
	On_MainMenu();
public:
	// ========== Destructors ========== //
	virtual ~On_MainMenu();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	// ========== Singleton methods ========== //
	static Game_State* getInstance();
};

//======================================================================================================================================//
// === On_NewGameMenu Class === //
class On_NewGameMenu : public Game_State
{
private:
	static Game_State* _instance;
protected:
	//================================================================//
	// ========== Constructors ========== //
	On_NewGameMenu();
public:
	// ========== Destructors ========== //
	virtual ~On_NewGameMenu();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	// ========== Singleton methods ========== //
	static Game_State* getInstance();
};

//======================================================================================================================================//
// === On_PauseMenu Class === //
class On_PauseMenu : public Game_State
{
private:
	static Game_State* _instance;
protected:
	//================================================================//
	// ========== Constructors ========== //
	On_PauseMenu();
public:
	// ========== Destructors ========== //
	virtual ~On_PauseMenu();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	// ========== Singleton methods ========== //
	static Game_State* getInstance();
};
