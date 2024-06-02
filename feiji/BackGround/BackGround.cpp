#include "BackGround.h"
#include"../GameConfig/GameConfig.h"

CBackGround::CBackGround():m_x(0),m_y(0)
{

}
CBackGround::~CBackGround()
{

}

void CBackGround::InitBack()
{
	::loadimage(&m_imgBack, L"./res/±³¾°.jpg");
	m_x = 0;
	m_y = -IMG_BACK_HEIGHT;
}

void CBackGround::ShowBack()
{
	::putimage(m_x, m_y, &m_imgBack);
}

void CBackGround::MoveBack(int step)
{
	m_y += step;
	if (m_y >= 0)
	{
		m_y = -IMG_BACK_HEIGHT;
	}
}
