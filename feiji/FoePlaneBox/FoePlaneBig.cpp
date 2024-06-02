#include "FoePlaneBig.h"
#include"../GameConfig/GameConfig.h"

void CFoePlaneBig::lnitFoe()
{
	::loadimage(&m_imgFoe, L"./res/foeplanebig.jpg");
	m_x = rd()%(IMG_BACK_WIDTH - IMG_FOE_BIG_WIDTH+1);
	m_y = -IMG_FOE_BIG_HEIGHT;
	m_blood = FOEBIG_BLOOD;
	m_showid = 4;
}

void CFoePlaneBig::ShowFoe()
{
	::putimage(m_x, m_y, IMG_FOE_BIG_WIDTH, IMG_FOE_BIG_HEIGHT, &m_imgFoe, IMG_FOE_BIG_WIDTH, (4-m_showid)*IMG_FOE_BIG_HEIGHT, SRCPAINT);
	::putimage(m_x, m_y, IMG_FOE_BIG_WIDTH, IMG_FOE_BIG_HEIGHT, &m_imgFoe, 0, (4 - m_showid) * IMG_FOE_BIG_HEIGHT, SRCAND);
}

void CFoePlaneBig::MoveFoe()
{
	m_y += FOEBIG_MOVE_STEP;
}

bool CFoePlaneBig::IsHitPlayer(CPlayer& player)
{
	int x = player.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOE_BIG_WIDTH && m_y <= player.m_y && player.m_y <= m_y + IMG_FOE_BIG_HEIGHT)
	{
		return true;
	}
	int y = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= m_x + IMG_FOE_BIG_WIDTH && m_y <= y && y <= m_y + IMG_FOE_BIG_HEIGHT)
	{
		return true;
	}
	int x1 = player.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOE_BIG_WIDTH && m_y <= y && y <= m_y + IMG_FOE_BIG_HEIGHT)
	{
		return true;
	}

	return false;
}

bool CFoePlaneBig::IsHitGunner(CGunner* pGun)
{
	if (pGun)
	{
		int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
		if (m_x <= x && x <= m_x + IMG_FOE_BIG_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOE_BIG_HEIGHT)
		{
			return true;
		}
	}

	return false;
}
