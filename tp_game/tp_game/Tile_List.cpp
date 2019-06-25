//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Tile_List.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Player.h"
#include "Enemy.h"

//======================================================================================================================================//
// === Tile_List methods === //
Tile_List::Tile_List()
{
}

Tile_List::~Tile_List()
{
	clear();
}

Tile_List::iterator Tile_List::begin()
{
	return _tile_set.begin();
}

Tile_List::iterator Tile_List::end()
{
	return _tile_set.end();
}

void Tile_List::clear()
{
	_tile_set.clear();
}

void Tile_List::includeTile(Tile* pT)
{
	_tile_set.insert(pT);
}

void Tile_List::draw_tiles()
{
	for (Tile* pT : *this)
	{
		pT->draw();
	}
}

void Tile_List::delete_tiles()
{
	for (Tile* pT : *this)
	{
		if (pT)
			delete pT;
	}
	clear();
}
