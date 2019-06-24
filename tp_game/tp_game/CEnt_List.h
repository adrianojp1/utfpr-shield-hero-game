#pragma once
#include "List.h"
#include "Entity.h"

class CEnt_List
{
private:

	List <Entity*> _CEnt_List;

public:

	CEnt_List();
	virtual ~CEnt_List();

	typedef List<Entity*>::iterator iterator;

	iterator begin();
	iterator end();

	void clearList();
	void includeEntity(Entity* pe);
	void removeEntity(Entity* pe);
	void drawList();

	//TODO
	void recordEntity();
	void recoverEntity();


};

