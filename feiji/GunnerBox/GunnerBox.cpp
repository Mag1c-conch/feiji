#include "GunnerBox.h"
#include"../GameConfig/GameConfig.h"

CGunnerBox::CGunnerBox()
{
}

CGunnerBox::~CGunnerBox()
{
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end())
	{
		if (*ite)
		{
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();
}

void CGunnerBox::PushGunner(CGunner* pGun)
{
	if (pGun)
	{
		m_lstGun.push_back(pGun);
	}
}

void CGunnerBox::ShowAllGunner()
{
	for (CGunner* pgun : m_lstGun)
	{
		if (pgun)
			pgun->ShowGunner();
	}
}

void CGunnerBox::MoveAllGunner()
{
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end())
	{
		if (*ite)
		{
			(*ite)->MoveGunner();

			if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT)
			{
				delete (*ite);
				(*ite) = nullptr;

				ite = m_lstGun.erase(ite);
				continue;

			}
		}
		ite++;
	}
}
