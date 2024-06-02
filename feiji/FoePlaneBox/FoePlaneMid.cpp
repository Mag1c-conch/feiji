#include "FoePlaneMid.h"
#include"../GameConfig/GameConfig.h"

void CFoePlaneMid::lnitFoe()
{
	::loadimage(&m_imgFoe, L"./res/foeplanemid.jpg");
	m_x = rd() % (IMG_BACK_WIDTH - IMG_FOE_MID_WIDTH + 1);
	m_y = -IMG_FOE_MID_HEIGHT;
	m_blood = FOEMID_BLOOD;
	m_showid = 3;
}

void CFoePlaneMid::ShowFoe()
{
	::putimage(m_x, m_y, IMG_FOE_MID_WIDTH, IMG_FOE_MID_HEIGHT, &m_imgFoe, IMG_FOE_MID_WIDTH, (3 - m_showid) * IMG_FOE_MID_HEIGHT, SRCPAINT);
	::putimage(m_x, m_y, IMG_FOE_MID_WIDTH, IMG_FOE_MID_HEIGHT, &m_imgFoe, 0, (3 - m_showid) * IMG_FOE_MID_HEIGHT, SRCAND);
}

void CFoePlaneMid::MoveFoe()
{
	m_y += FOEMID_MOVE_STEP;
}

bool CFoePlaneMid::IsHitPlayer(CPlayer& player)
{
	int x = player.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOE_MID_WIDTH && m_y <= player.m_y && player.m_y <= m_y + IMG_FOE_MID_HEIGHT)
	{
		return true;
	}
	int y = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= m_x + IMG_FOE_MID_WIDTH && m_y <= y && y <= m_y + IMG_FOE_MID_HEIGHT)
	{
		return true;
	}
	int x1 = player.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOE_MID_WIDTH && m_y <= y && y <= m_y + IMG_FOE_MID_HEIGHT)
	{
		return true;
	}

	return false;
}

bool CFoePlaneMid::IsHitGunner(CGunner* pGun)
{
	if (pGun)
	{
		int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
		if (m_x <= x && x <= m_x + IMG_FOE_MID_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOE_MID_HEIGHT)
		{
			return true;
		}
	}

	return false;
}
