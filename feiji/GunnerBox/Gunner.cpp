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
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH/*�ڴ�����ʾ�Ŀ��*/,IMG_GUNNER_HEIGHT/*�ڴ�����ʾ�ĸ߶�*/, &m_imgGun, IMG_GUNNER_WIDTH/*��Դͼ���ĸ�λ�ÿ�ʼ��ȡͼ��x��*/, 0/*(y)*/, SRCPAINT);
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_imgGun, 0, 0, SRCAND);
}

void CGunner::MoveGunner()
{
	m_y -= GUNNER_MOVE_STEP;
}
