#pragma once

//======================================================================================================================================//
// === MyWindow Class === //
class Graphical_Manager : public sf::RenderWindow
{
private:
	sf::View* pView;

	static std::vector<sf::Texture*> _vTextures;
public:
	//================================================================//
	// ========== Constructors ========== //
	Graphical_Manager();
	// ========== Destructors ========== //
	virtual ~Graphical_Manager();

	//================================================================//
	// ========== Initializers ========== //
	void initializeView(sf::Vector2f center, sf::Vector2f windowSize);
	void loadAllTextures();

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
	static void loadTexture(const std::string file_path, sf::Texture** pTexture);
	static void load_n_setTexture(sf::RectangleShape* pShape, const std::string file_path, sf::Texture* pTexture);

	//================================================================//
	//======================== Static Consts =========================//
private:
	// ========== Window ========== //
	static const sf::Vector2u windowRatio;
	static const unsigned int ratioMultiplier;
	static const std::string windowName;
	static const sf::Vector2u windowSize;

public:
	// ========== Debug ========== //
	static const bool CONSOLE_LOG;
	static const bool COLLISION_DBG;

	// ========== Stage ========== //
	static const float gravity;

	// ========== Textures ========== //
	static const sf::Vector2f textures_scale;

	// ========== Fonts (Ft) file paths (Fp) ========== //
	static const std::string menu_Ft_Fp;

	// ========== Sprites (Sp) file paths (Fp) ========== //
	//Tiled
	static const std::string tileset_Fp;
	static sf::Texture* tileset_texture;

	//Player
	static const std::string player_idle_Sp_Fp;
	static const std::string player_walk_Sp_Fp;
	static const std::string player_def1_Sp_Fp;
	static const std::string player_def2_Sp_Fp;
	static const std::string player_die_Sp_Fp;

	static sf::Texture* player_idle_texture;
	static sf::Texture* player_walk_texture;
	static sf::Texture* player_def1_texture;
	static sf::Texture* player_def2_texture;
	static sf::Texture* player_die_texture;

	//Orc
	static const std::string orc_idle_Sp_Fp;
	static const std::string orc_walk_Sp_Fp;
	static const std::string orc_atk_Sp_Fp;
	static const std::string orc_die_Sp_Fp;

	static sf::Texture* orc_idle_texture;
	static sf::Texture* orc_walk_texture;
	static sf::Texture* orc_atk_texture;
	static sf::Texture* orc_die_texture;

	//White_Skeleton


	//Black_Skeleton

};

typedef Graphical_Manager gMng;

