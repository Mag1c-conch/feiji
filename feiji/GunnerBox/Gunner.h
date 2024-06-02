#pragma once
#include <easyx.h>

class CGunner {
public:
	IMAGE m_imgGun;

public:

	int m_x;
	int m_y;
public:
	CGunner();
	~CGunner();
public:
	void lnitGunner(int x ,int y);

	void ShowGunner();

	void MoveGunner();

};


