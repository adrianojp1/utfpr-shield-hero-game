#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Tile.h"

//======================================================================================================================================//
// === Classes Declaration === //
class Enemy;

//======================================================================================================================================//
// === Tile_List Class === //
class Tile_List
{
private:
	std::set<Tile*> _tile_set;
public:
	Tile_List();
	virtual ~Tile_List();

	typedef std::set<Tile*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeTile(Tile* pT);
	//void removeTile(Tile* pT);
	void draw_tiles();
};

