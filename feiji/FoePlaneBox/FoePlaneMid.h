#pragma once
#include "../Player/Player.h"
#include"FoePlane.h"

class CFoePlaneMid:public CFoePlane{
public:
	void lnitFoe();
	void ShowFoe();
	void MoveFoe();

	bool IsHitPlayer(CPlayer& player);

	bool IsHitGunner(CGunner* pGun);
};


