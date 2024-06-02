#include "Gunner.h"
#include"../GameConfig/GameConfig.h"

CGunner::CGunner():m_x(0),m_y(0)
{

}

CGunner::~CGunner()
{

}

void CGunner::lnitGunner(int x, int y)
{
	::loadimage(&m_imgGun, L"./res/gunner.jpg");
	m_x = x;
	m_y = y;
}

void CGunner::ShowGunner()
{
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH/*在窗口显示的宽度*/,IMG_GUNNER_HEIGHT/*在窗口显示的高度*/, &m_imgGun, IMG_GUNNER_WIDTH/*从源图的哪个位置开始截取图（x）*/, 0/*(y)*/, SRCPAINT);
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_imgGun, 0, 0, SRCAND);
}

void CGunner::MoveGunner()
{
	m_y -= GUNNER_MOVE_STEP;
}
