#pragma once
#include "List.h"
#include "Entity.h"

class CEnt_List
{
private:

	List <Entity> CE_List;

public:

	CEnt_List();
	~CEnt_List();

	void clearList();
	void includeEntity(Entity* pe);

	//TODO
	void drawEntity();

	//TODO
	void recordEntity();
	void recoverEntity();


};

