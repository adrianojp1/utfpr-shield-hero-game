#include "stdafx.h"
#include "CEnt_List.h"

CEnt_List::CEnt_List()
{
}

CEnt_List::~CEnt_List()
{
	clearList();
}

void CEnt_List::clearList()
{
	CE_List.clear();
}

void CEnt_List::includeEntity(Entity* pe)
{
	if (pe != NULL)
		CE_List.includeObject(pe);
	else
		std::cout << "Error! Invalid Element pointer" << std::endl;
}
