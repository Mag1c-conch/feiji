#include "FoePlaneBox.h"
#include"../GameConfig/GameConfig.h"

CFoePlaneBox::CFoePlaneBox()
{
}

#define DELETE_LIST(LIST)\
list<CFoePlane*>::iterator ite##LIST = LIST.begin();\
while (ite##LIST != LIST.end())\
{\
	if (*ite##LIST)\
	{\
		delete (*ite##LIST);\
		(*ite##LIST) = nullptr;\
	}\
	ite##LIST++;\
}LIST.clear();


CFoePlaneBox::~CFoePlaneBox()
{
	DELETE_LIST(m_lstFoe);
	DELETE_LIST(m_lstBoomFoe);
}

void CFoePlaneBox::PushFoe(CFoePlane*pFoe)
{
	if (pFoe)
	{
		m_lstFoe.push_back(pFoe);
	}
}

void CFoePlaneBox::PushBoomFoe(CFoePlane*pFoe)
{
	if (pFoe)
	{
		m_lstBoomFoe.push_back(pFoe);
	}
}

void CFoePlaneBox::ShowAllFoe()
{
	for (CFoePlane* pFoe : m_lstFoe)
	{
		if (pFoe)
		{
			pFoe->ShowFoe();
		}
	}
}

void CFoePlaneBox::ShowAllBoomFoe()
{
	for (CFoePlane* pFoe : m_lstBoomFoe)
	{
		if (pFoe)
		{
			pFoe->ShowFoe();
		}
	}
}

void CFoePlaneBox::MoveAllFoe()
{
	//for (CFoePlane* pFoe : m_lstFoe)
	//{
	//	if (pFoe)
	//	{
	//		pFoe->MoveFoe();
	//	}
	//}
	//
	list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end())
	{
		if (*ite)
		{
			(*ite)->MoveFoe();

			if ((*ite)->m_y >= IMG_BACK_HEIGHT)
			{
				delete(*ite);
				(*ite) = nullptr;
				ite = m_lstFoe.erase(ite);
				continue;
			}

		}
		ite++;

	}
}
