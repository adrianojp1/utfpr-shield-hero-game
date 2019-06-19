#include "stdafx.h"
#include "CEnt_List.h"


CEnt_List::CEnt_List()
{
}

CEnt_List::~CEnt_List()
{
	clearList();
}

CEnt_List::iterator CEnt_List::begin()
{
	return _CEnt_List.begin();
}

CEnt_List::iterator CEnt_List::end()
{
	return _CEnt_List.end();
}

void CEnt_List::clearList()
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

void CEnt_List::drawList()
{
	for (List<Entity*>::iterator it = _CEnt_List.begin(); it != _CEnt_List.end(); it++)
	{
		it->draw();
	}
}
