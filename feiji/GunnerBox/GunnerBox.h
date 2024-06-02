#pragma once
#include<list>
#include"Gunner.h"
using namespace std;

class CGunnerBox {
public:
	list<CGunner*> m_lstGun;
public:
	CGunnerBox();
	~CGunnerBox();
	void PushGunner(CGunner* pGun);

	void ShowAllGunner();

	void MoveAllGunner();
};

