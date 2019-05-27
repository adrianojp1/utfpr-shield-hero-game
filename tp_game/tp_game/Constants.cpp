#pragma once
#include "stdafx.h"

//Constants definition file separated by namespaces
//======================================================================================================================================//
// === Console === //
namespace consoleNS {
	int const CONSOLE_LOG = 1;
}

//======================================================================================================================================//
// === Debug === //
namespace debugNS {

}

//======================================================================================================================================//
// === Window === //
namespace windowNS {
	const float viewZoom = 5.0f;
	const sf::Vector2u windowRatio = { 4, 3 };
	const unsigned int ratioMultiplier = 250;
	const std::string windowName = "Shield Hero";
}

//======================================================================================================================================//
// === Player === //
namespace playerNS {
	const std::string idle_sprite_filePath = "Media/shield-hero/shield_hero-idle.png";
	const std::string walk_sprite_filePath = "Media/shield-hero/shield_hero-walk.png";
	const std::string def1_sprite_filePath = "Media/shield-hero/shield_hero-def1.png";
	const std::string def2_sprite_filePath = "Media/shield-hero/shield_hero-def2.png";
	const std::string die_sprite_filePath = "Media/shield-hero/shield_hero-die.png";

}

//======================================================================================================================================//
// === Orc-Enemy === //
namespace orcNS {
	const std::string idle_sprite_filePath = "Media/orc/orc-idle.png";
	const std::string walk_sprite_filePath = "Media/orc/orc-walk.png";
}

//======================================================================================================================================//
// === Block === //
namespace blockNS {
	const sf::Vector2f blockSize = { 16.0f, 16.0f };
}