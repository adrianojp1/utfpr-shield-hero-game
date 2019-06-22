#pragma once
#include "List.h"
#include "Entity.h"

class CEnt_List
{
private:

	List <Entity*> _CEnt_List;

public:

	CEnt_List();
	~CEnt_List();

	typedef List<Entity*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeEntity(Entity* pe);
	void removeEntity(Entity* pe);
	void draw_entities();

	//TODO
	void recordEntity();
	void recoverEntity();


};

