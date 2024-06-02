#include "Player.h"
#include"../GameConfig/GameConfig.h"

CPlayer::CPlayer():m_x(0),m_y(0)
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::InitPlayer()
{
	::loadimage(&m_imgPlayer, L"./res/playerplane.jpg");
	::loadimage(&m_imgPlayerMask, L"./res/playerplane-mask.jpg");
		m_x = (IMG_BACK_WIDTH - IMG_PLAYER_WIDTH) / 2;
		m_y = IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT;
}

void CPlayer::ShowPlayer()
{
	::putimage(m_x, m_y, &m_imgPlayerMask, SRCPAINT);//SRCPAINT传输方式为位或
	::putimage(m_x, m_y, &m_imgPlayer, SRCAND);//SRCAND传输方式为位与

}

void CPlayer::MovePlayer(BYTE direct)
{
	if (direct == VK_UP)
	{
		m_y - PLAYER_MOVE_STEP >= 0 ? m_y -= PLAYER_MOVE_STEP : m_y = 0;
	}
	else if (direct == VK_DOWN)
	{
		m_y + PLAYER_MOVE_STEP <=IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT ? m_y += PLAYER_MOVE_STEP : m_y = IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT;
	}
	else if (direct == VK_LEFT)
	{
		m_x - PLAYER_MOVE_STEP >= 0 ? m_x -= PLAYER_MOVE_STEP : m_x = 0;
	}
	else if (direct == VK_RIGHT)
	{
		m_x + PLAYER_MOVE_STEP <= IMG_BACK_WIDTH - IMG_PLAYER_WIDTH ? m_x += PLAYER_MOVE_STEP : m_x = IMG_BACK_WIDTH - IMG_PLAYER_WIDTH;
	}
}

CGunner* CPlayer::SendGunner()
{
	CGunner* pGun = new CGunner;
	int x = m_x + (IMG_PLAYER_WIDTH-IMG_GUNNER_WIDTH) / 2;
	int y = m_y - IMG_GUNNER_HEIGHT;
	pGun->lnitGunner(x, y);
    return pGun;
}
