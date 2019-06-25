//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Graphical_Manager.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2u Graphical_Manager::windowRatio = {16, 9};
const unsigned int Graphical_Manager::ratioMultiplier = 84;
const std::string Graphical_Manager::windowName = "Shield Hero";
const sf::Vector2u Graphical_Manager::windowSize = {windowRatio.x * ratioMultiplier, 728};

std::vector<sf::Texture *> Graphical_Manager::_vTextures;

const bool Graphical_Manager::CONSOLE_LOG = false;
const bool Graphical_Manager::COLLISION_DBG = false;

const float Graphical_Manager::gravity(1400.0f);

const std::string Graphical_Manager::textures_dir = "Textures/";
const std::string Graphical_Manager::fonts_dir = "Fonts/";
const std::string Graphical_Manager::levels_dir = "Stages/";

const std::string Graphical_Manager::tile_sufix = "_tile_layers.txt";

const sf::Vector2f Graphical_Manager::textures_scale = {3.5f, 3.5f};

const std::string Graphical_Manager::menu_ops_Ft_Fp = fonts_dir + "romulus.ttf";
const std::string Graphical_Manager::menu_title_Ft_Fp = fonts_dir + "alagard.ttf";
sf::Font* Graphical_Manager::menu_ops_ft = NULL;
sf::Font* Graphical_Manager::menu_title_ft = NULL;

const std::string Graphical_Manager::tileset_Fp = textures_dir + "stage/tileset.png";
sf::Texture *Graphical_Manager::tileset_texture = NULL;

const std::string Graphical_Manager::energy_ball_Fp = textures_dir + "stage/energy_ball.png";
sf::Texture* Graphical_Manager::energy_ball_texture = NULL;

const std::string Graphical_Manager::player_idle_Sp_Fp = textures_dir + "shield-hero/shield_hero-idle.png";
const std::string Graphical_Manager::player_walk_Sp_Fp = textures_dir + "shield-hero/shield_hero-walk.png";
const std::string Graphical_Manager::player_def1_Sp_Fp = textures_dir + "shield-hero/shield_hero-def1.png";
const std::string Graphical_Manager::player_def2_Sp_Fp = textures_dir + "shield-hero/shield_hero-def2.png";
const std::string Graphical_Manager::player_die_Sp_Fp = textures_dir + "shield-hero/shield_hero-die.png";

sf::Texture *Graphical_Manager::player_idle_texture = NULL;
sf::Texture *Graphical_Manager::player_walk_texture = NULL;
sf::Texture *Graphical_Manager::player_def1_texture = NULL;
sf::Texture *Graphical_Manager::player_def2_texture = NULL;
sf::Texture *Graphical_Manager::player_die_texture = NULL;

const std::string Graphical_Manager::orc_idle_Sp_Fp = textures_dir + "orc/orc-idle.png";
const std::string Graphical_Manager::orc_walk_Sp_Fp = textures_dir + "orc/orc-walk.png";
const std::string Graphical_Manager::orc_atk_Sp_Fp = textures_dir + "orc/orc-atk.png";
const std::string Graphical_Manager::orc_die_Sp_Fp = textures_dir + "orc/orc-die.png";

sf::Texture *Graphical_Manager::orc_idle_texture = NULL;
sf::Texture *Graphical_Manager::orc_walk_texture = NULL;
sf::Texture *Graphical_Manager::orc_atk_texture = NULL;
sf::Texture *Graphical_Manager::orc_die_texture = NULL;

const std::string Graphical_Manager::white_skeleton_idle_Sp_Fp = textures_dir + "skeleton/skeleton_1-idle.png";
const std::string Graphical_Manager::white_skeleton_walk_Sp_Fp = textures_dir + "skeleton/skeleton_1-walk.png";
const std::string Graphical_Manager::white_skeleton_atk_Sp_Fp = textures_dir + "skeleton/skeleton_1-atk.png";
const std::string Graphical_Manager::white_skeleton_die_Sp_Fp = textures_dir + "skeleton/skeleton_1-die.png";

sf::Texture* Graphical_Manager::white_skeleton_idle_texture = NULL;
sf::Texture* Graphical_Manager::white_skeleton_walk_texture = NULL;
sf::Texture* Graphical_Manager::white_skeleton_atk_texture = NULL;
sf::Texture* Graphical_Manager::white_skeleton_die_texture = NULL;

const std::string Graphical_Manager::black_skeleton_idle_Sp_Fp = textures_dir + "skeleton/skeleton_2-idle.png";
const std::string Graphical_Manager::black_skeleton_walk_Sp_Fp = textures_dir + "skeleton/skeleton_2-walk.png";
const std::string Graphical_Manager::black_skeleton_atk_Sp_Fp = textures_dir + "skeleton/skeleton_2-atk.png";
const std::string Graphical_Manager::black_skeleton_die_Sp_Fp = textures_dir + "skeleton/skeleton_2-die.png";

sf::Texture* Graphical_Manager::black_skeleton_idle_texture = NULL;
sf::Texture* Graphical_Manager::black_skeleton_walk_texture = NULL;
sf::Texture* Graphical_Manager::black_skeleton_atk_texture = NULL;
sf::Texture* Graphical_Manager::black_skeleton_die_texture = NULL;

const std::string Graphical_Manager::white_skeleton_proj_Sp_Fp = textures_dir + "skeleton/skeleton_1-proj.png";
const std::string Graphical_Manager::black_skeleton_proj_Sp_Fp = textures_dir + "skeleton/skeleton_2-proj.png";

sf::Texture* Graphical_Manager::white_skeleton_proj_texture = NULL;
sf::Texture* Graphical_Manager::black_skeleton_proj_texture = NULL;

const std::string Graphical_Manager::boss_idle_Sp_Fp = textures_dir + "boss/boss-idle";
const std::string Graphical_Manager::boss_walk_Sp_Fp = textures_dir + "boss/boss-walk";
const std::string Graphical_Manager::boss_atk_Sp_Fp = textures_dir + "boss/boss-atk";

sf::Texture* Graphical_Manager::boss_idle_texture = NULL;
sf::Texture* Graphical_Manager::boss_walk_texture = NULL;
sf::Texture* Graphical_Manager::boss_atk_texture = NULL;

//======================================================================================================================================//
// === Graphical_Manager methods === //
Graphical_Manager::Graphical_Manager() : sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), gMng::windowName, sf::Style::Close | sf::Style::Titlebar)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	loadAllTextures();
	loadAllFonts();
	initializeView({0.0f, 0.0f}, (sf::Vector2f)this->getSize());
	this->setFramerateLimit(60);
} // end constr

Graphical_Manager::~Graphical_Manager()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (pView != NULL)
		delete pView;

	for (sf::Texture *pTexture : _vTextures)
	{
		if (pTexture)
			delete pTexture;
	}
	_vTextures.clear();
} // end destr

void Graphical_Manager::initializeView(sf::Vector2f center, sf::Vector2f windowSize)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	pView = new sf::View;
	pView->setCenter(center);
	pView->setSize(windowSize);
	this->setView(*pView);
} // end initializeView

void Graphical_Manager::loadAllTextures()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Tilet
	loadTexture(tileset_Fp, &tileset_texture);
	loadTexture(energy_ball_Fp, &energy_ball_texture);

	//Player
	loadTexture(player_idle_Sp_Fp, &player_idle_texture);
	loadTexture(player_walk_Sp_Fp, &player_walk_texture);
	loadTexture(player_def1_Sp_Fp, &player_def1_texture);
	loadTexture(player_def2_Sp_Fp, &player_def2_texture);
	loadTexture(player_die_Sp_Fp, &player_die_texture);

	//Orc
	loadTexture(orc_idle_Sp_Fp, &orc_idle_texture);
	loadTexture(orc_walk_Sp_Fp, &orc_walk_texture);
	loadTexture(orc_atk_Sp_Fp, &orc_atk_texture);
	loadTexture(orc_die_Sp_Fp, &orc_die_texture);

	//White_Skeleton
	loadTexture(white_skeleton_idle_Sp_Fp, &white_skeleton_idle_texture);
	loadTexture(white_skeleton_walk_Sp_Fp, &white_skeleton_walk_texture);
	loadTexture(white_skeleton_die_Sp_Fp, &white_skeleton_die_texture);
	loadTexture(white_skeleton_atk_Sp_Fp, &white_skeleton_atk_texture);
	loadTexture(white_skeleton_proj_Sp_Fp, &white_skeleton_proj_texture);

	//Black_Skeleton
	loadTexture(black_skeleton_idle_Sp_Fp, &black_skeleton_idle_texture);
	loadTexture(black_skeleton_walk_Sp_Fp, &black_skeleton_walk_texture);
	loadTexture(black_skeleton_die_Sp_Fp, &black_skeleton_die_texture);
	loadTexture(black_skeleton_atk_Sp_Fp, &black_skeleton_atk_texture);
	loadTexture(black_skeleton_proj_Sp_Fp, &black_skeleton_proj_texture);

	//Boss
	loadTexture(boss_idle_Sp_Fp, &boss_idle_texture);
	loadTexture(boss_walk_Sp_Fp, &boss_walk_texture);
	loadTexture(boss_atk_Sp_Fp, &boss_atk_texture);
}

void Graphical_Manager::loadAllFonts()
{
	//Menu
	loadFont(menu_ops_Ft_Fp, &menu_ops_ft);
	loadFont(menu_title_Ft_Fp, &menu_title_ft);
}

void Graphical_Manager::execute()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Window event
	sf::Event evnt;

	//Window event poll loop
	while (this->pollEvent(evnt))
	{
		//Close window
		if (evnt.type == sf::Event::Closed)
			this->close();
	}
} // end execute

void Graphical_Manager::setViewCenter(sf::Vector2f center)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	pView->setCenter(center);
	this->setView(*pView);
}

void Graphical_Manager::moveView(sf::Vector2f offset)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	pView->move(offset);
	this->setView(*pView);
}

void Graphical_Manager::printConsole_log(std::string log)
{
	if (CONSOLE_LOG)
		std::cerr << log << std::endl;
}

void Graphical_Manager::loadFont(const std::string file_path, sf::Font** pFont)
{
	if (!*pFont)
	{
		*pFont = new sf::Font;
	}
	if (!(*pFont)->loadFromFile(file_path))
		getchar();
}

void Graphical_Manager::loadTexture(const std::string file_path, sf::Texture **pTexture)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!*pTexture)
	{
		*pTexture = new sf::Texture;
		_vTextures.push_back(*pTexture);
	}
	if (!(*pTexture)->loadFromFile(file_path))
		getchar();
}

void Graphical_Manager::load_n_setTexture(sf::RectangleShape *pShape, const std::string file_path, sf::Texture *pTexture)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!pTexture)
		pTexture = new sf::Texture;

	loadTexture(file_path, &pTexture);
	pShape->setTexture(pTexture);
	pShape->setScale(textures_scale);
}