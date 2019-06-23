#include "stdafx.h"
#include "CEnt_List.h"


CEnt_List::CEnt_List()
{
}

CEnt_List::~CEnt_List()
{
	clear();
}

CEnt_List::iterator CEnt_List::begin()
{
	return _CEnt_List.begin();
}

CEnt_List::iterator CEnt_List::end()
{
	return _CEnt_List.end();
}

void CEnt_List::clear()
{
	_CEnt_List.clear();
}

void CEnt_List::includeEntity(Entity* pe)
{
	_CEnt_List.pushBack(pe);
}

void CEnt_List::removeEntity(Entity* pe)
{
	_CEnt_List.remove(pe);
}

void CEnt_List::execute_entities(const float deltaTime)
{
	for (Entity* pEnt : *this)
	{
		pEnt->execute(deltaTime);
	}
}

void CEnt_List::draw_entities()
{
	for (Entity* pEnt : *this)
	{
		pEnt->draw();
	}
}
