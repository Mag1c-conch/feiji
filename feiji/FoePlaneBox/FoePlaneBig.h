#pragma once
#include"FoePlane.h"


class CFoePlaneBig :public CFoePlane {
public:
	void lnitFoe();
	void ShowFoe();
	void MoveFoe();

	bool IsHitPlayer(CPlayer& player);

	bool IsHitGunner(CGunner* pGun);
};


