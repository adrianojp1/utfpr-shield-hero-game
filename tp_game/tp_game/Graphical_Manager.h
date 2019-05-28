#pragma once

//======================================================================================================================================//
// === MyWindow Class === //
class Graphical_Manager : public sf::RenderWindow
{
private:
	sf::View* pView;

public:
	//================================================================//
	// ========== Constructors ========== //
	Graphical_Manager();
	// ========== Destructors ========== //
	virtual ~Graphical_Manager();

	//================================================================//
	// ========== Initializers ========== //
	void initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom);

	//================================================================//
	// ========== Loop methods ========== //
	void execute();

	//================================================================//
	// ========== View methods ========== //
	void setViewCenter(sf::Vector2f center);
	void moveView(sf::Vector2f offset);

	//================================================================//
	// ========== Log method ========== //
	static void printConsole_log(std::string log);

	//================================================================//
	//======================== Static Consts =========================//
private:
	// ========== Window ========== //
	static const sf::Vector2u windowRatio;
	static const unsigned int ratioMultiplier;
	static const std::string windowName;
	static const sf::Vector2u windowSize;

	// ========== View ========== //
	static const float viewZoom;

public:
	// ========== Debug ========== //
	static const bool CONSOLE_LOG;
	static const bool COLLISION_DBG;

	// ========== Sprites (Sp) file paths (Fp) ========== //
	//Player
	static const std::string player_idle_Sp_Fp;
	static const std::string player_walk_Sp_Fp;
	static const std::string player_def1_Sp_Fp;
	static const std::string player_def2_Sp_Fp;
	static const std::string player_die_Sp_Fp;

	//Orc


	//White_Skeleton


	//Black_Skeleton

};

typedef Graphical_Manager gMng;

