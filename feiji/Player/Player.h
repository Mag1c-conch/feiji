#pragma once
#include <easyx.h>
#include"../GunnerBox/Gunner.h"

class CPlayer {
public:
	IMAGE m_imgPlayer;
	IMAGE m_imgPlayerMask;
	int m_x;
	int m_y;
public:
	CPlayer();
	~CPlayer();
public:
	void InitPlayer();

	void ShowPlayer();

	void MovePlayer(BYTE direct);

	CGunner* SendGunner();
};

