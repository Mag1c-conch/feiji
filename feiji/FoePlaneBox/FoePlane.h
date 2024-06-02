#pragma once
#include "../Player/Player.h"
#include <easyx.h>
#include<random>

class CFoePlane {
public:
	IMAGE m_imgFoe;
	int m_x;
	int m_y;
	int m_blood;
	int m_showid; 
	static std::random_device rd;
public:
	CFoePlane();
	virtual ~CFoePlane();
	virtual void lnitFoe() = 0;
	virtual void ShowFoe() = 0;
	virtual void MoveFoe() = 0;

	virtual bool IsHitPlayer(CPlayer& player) = 0;

	virtual bool IsHitGunner(CGunner* pGun) = 0;
};

