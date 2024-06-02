#include "FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"

void CFoePlaneSma::lnitFoe()
{
	::loadimage(&m_imgFoe, L"./res/foeplanesma.jpg");
	m_x = rd() % (IMG_BACK_WIDTH - IMG_FOE_SMA_WIDTH + 1);
	m_y = -IMG_FOE_SMA_HEIGHT;
	m_blood = FOESMA_BLOOD;
	m_showid = 2;
}

void CFoePlaneSma::ShowFoe()
{
	::putimage(m_x, m_y, IMG_FOE_SMA_WIDTH, IMG_FOE_SMA_HEIGHT, &m_imgFoe, IMG_FOE_SMA_WIDTH, (2 - m_showid) * IMG_FOE_SMA_HEIGHT, SRCPAINT);
	::putimage(m_x, m_y, IMG_FOE_SMA_WIDTH, IMG_FOE_SMA_HEIGHT, &m_imgFoe, 0, (2 - m_showid) * IMG_FOE_SMA_HEIGHT, SRCAND);
}

void CFoePlaneSma::MoveFoe()
{
	m_y += FOESMA_MOVE_STEP;
}

bool CFoePlaneSma::IsHitPlayer(CPlayer& player)
{
	int x = player.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOE_SMA_WIDTH && m_y <= player.m_y && player.m_y <= m_y + IMG_FOE_SMA_HEIGHT)
	{
		return true;
	}
	int y = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= m_x + IMG_FOE_SMA_WIDTH && m_y <= y && y <= m_y + IMG_FOE_SMA_HEIGHT)
	{
		return true;
	}
	int x1 = player.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOE_SMA_WIDTH && m_y <= y && y <= m_y + IMG_FOE_SMA_HEIGHT)
	{
		return true;
	}

	return false;
}

bool CFoePlaneSma::IsHitGunner(CGunner* pGun)
{
	if (pGun)
	{
		int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
		if (m_x <= x && x <= m_x + IMG_FOE_SMA_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOE_SMA_HEIGHT)
		{
			return true;
		}
	}

	return false;
}
