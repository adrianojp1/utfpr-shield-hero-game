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

	void clear();
	void includeEntity(Entity* pe);
	void removeEntity(Entity* pe);
	void execute_entities(const float deltaTime);
	void draw_entities();
	void delete_entities();

	//TODO
	void recordEntity();
	void recoverEntity();


};

