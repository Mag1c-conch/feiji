#pragma once
#include <easyx.h>


class CBackGround {
public:
	IMAGE m_imgBack;

	int m_x;
	int m_y;
public:
	CBackGround();
	~CBackGround();
	void InitBack();
	void ShowBack();
	void MoveBack(int step);

};

