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
	void loadAllFonts();

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
	static void loadFont(const std::string file_path, sf::Font** pFont);
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

	// ========== Directories ========== //
	static const std::string textures_dir;
	static const std::string fonts_dir;
	static const std::string levels_dir;
	//static const std::string sound_dir;

	static const std::string tile_sufix;

	// ========== Stage ========== //
	static const float gravity;

	// ========== Levels ========== //
	//Stage 1
	
	//Stage 2

	// ========== Tileset ========== //
	static const sf::Vector2f textures_scale;

	// ========== Menu (Ft) file paths (Fp) ========== //
	static const std::string menu_ops_Ft_Fp;
	static const std::string menu_title_Ft_Fp;
	static sf::Font* menu_ops_ft;
	static sf::Font* menu_title_ft;

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
	static const std::string white_skeleton_idle_Sp_Fp;
	static const std::string white_skeleton_walk_Sp_Fp;
	static const std::string white_skeleton_atk_Sp_Fp;
	static const std::string white_skeleton_die_Sp_Fp;

	static sf::Texture* white_skeleton_idle_texture;
	static sf::Texture* white_skeleton_walk_texture;
	static sf::Texture* white_skeleton_atk_texture;
	static sf::Texture* white_skeleton_die_texture;

	//Black_Skeleton
	static const std::string black_skeleton_idle_Sp_Fp;
	static const std::string black_skeleton_walk_Sp_Fp;
	static const std::string black_skeleton_atk_Sp_Fp;
	static const std::string black_skeleton_die_Sp_Fp;

	static sf::Texture* black_skeleton_idle_texture;
	static sf::Texture* black_skeleton_walk_texture;
	static sf::Texture* black_skeleton_atk_texture;
	static sf::Texture* black_skeleton_die_texture;

	//Projectile
	static const std::string white_skeleton_proj_Sp_Fp;
	static const std::string black_skeleton_proj_Sp_Fp;

	static sf::Texture* white_skeleton_proj_texture;
	static sf::Texture* black_skeleton_proj_texture;
};

typedef Graphical_Manager gMng;