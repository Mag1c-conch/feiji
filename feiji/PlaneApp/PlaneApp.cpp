#include "PlaneApp.h"
#include"../GameConfig/GameConfig.h"
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"
#include<typeinfo>

CREATE_OBJECT(CPlaneApp)

WND_PARAM(500,50,IMG_BACK_WIDTH+10,IMG_BACK_HEIGHT+40,L"飞机大战")


CPlaneApp::CPlaneApp():m_score(0), currentLevel(1), scoreThreshold(10), FOEBIG_CREATE_INTERVAL(12000),FOEMID_CREATE_INTERVAL(9000),FOESMA_CREATE_INTERVAL(6000),tip(false)
{

}
CPlaneApp::~CPlaneApp()
{

}

void CPlaneApp::InitGame()
{
	m_back.InitBack();
	m_player.InitPlayer();
	::loadimage(&m_board, L"./res/cardboard.png", 80, 50);

	SetTimer();
}

void CPlaneApp::CloseGame()
{

}

void CPlaneApp::PaintGame()	
{
	m_back.ShowBack();
	m_player.ShowPlayer();

	m_gunBox.ShowAllGunner();
	m_foeBox.ShowAllFoe();
	m_foeBox.ShowAllBoomFoe();
	ShowScore();
	
}

void CPlaneApp::On_WM_KEYDOWN(BYTE key)
{
	//m_player.MovePlayer(key);
}

void CPlaneApp::On_WM_TIMER(WPARAM w, LPARAM l)
{ 
	switch (w)
	{
		case BACK_MOVE_TIMERID:
		{
			m_back.MoveBack(BACK_MOVE_STEP);
		}
			break;
		case PLAYER_MOVE_TIMERID:
		{
			if (::GetAsyncKeyState(VK_UP))//获取键盘的状态
			{
				m_player.MovePlayer(VK_UP);
			}
			if (::GetAsyncKeyState(VK_DOWN))
			{
				m_player.MovePlayer(VK_DOWN);
			}
			if (::GetAsyncKeyState(VK_LEFT))
			{
				m_player.MovePlayer(VK_LEFT);
			}
			if (::GetAsyncKeyState(VK_RIGHT))
			{
				m_player.MovePlayer(VK_RIGHT);
			}
		}
		break;
		case GUNNER_SEND_TIMERID:
		{
			m_gunBox.PushGunner(m_player.SendGunner());
		}
			break;
		case GUNNER_MOVE_TIMERID:
		{
			m_gunBox.MoveAllGunner();
		}
		break;

		case FOEBIG_CREATE_TIMERID:
		{
			CFoePlane* pFoe = new CFoePlaneBig;
			pFoe->lnitFoe();
			m_foeBox.m_lstFoe.push_back(pFoe);
		}
		break;
		case FOEMID_CREATE_TIMERID:
		{
			CFoePlane* pFoe = new CFoePlaneMid;
			pFoe->lnitFoe();
			m_foeBox.m_lstFoe.push_back(pFoe);
		}
		break;
		case FOESMA_CREATE_TIMERID:
		{
			CFoePlane* pFoe = new CFoePlaneSma;
			pFoe->lnitFoe();
			m_foeBox.m_lstFoe.push_back(pFoe);
		}
		break;

		case FOE_MOVE_TIMERID:
		{
			m_foeBox.MoveAllFoe();
		}
		break;
		case CHECK_HIT_TIMERID:
		{
			list<CFoePlane*>::iterator ite = m_foeBox.m_lstFoe.begin();
			while (ite != m_foeBox.m_lstFoe.end())
			{
				bool IsBoom = false;
				if (*ite)
				{

					if ((*ite)->IsHitPlayer(m_player))
					{
						KillTimer();

						::MessageBox(hWnd, L"游戏结束", L"提示", MB_OK);

						::PostMessage(hWnd, WM_CLOSE, 0, 0);//模拟退出过程,发送WM_CLOSE消息
						return;
					}


					list<CGunner*>::iterator iteGun = m_gunBox.m_lstGun.begin();
					while (iteGun != m_gunBox.m_lstGun.end())
					{
						if ((*ite)->IsHitGunner(*iteGun))
						{
							delete (*iteGun);
							(*iteGun) = nullptr;

							iteGun = m_gunBox.m_lstGun.erase(iteGun);

							(*ite)->m_blood -= GUNNER_HURT;
							if ((*ite)->m_blood <= 0)
							{

								if (typeid(**ite) == typeid(CFoePlaneBig))
								{
									m_score += 5;
								}
								if (typeid(**ite) == typeid(CFoePlaneMid))
								{
									m_score += 3;
								}
								if (typeid(**ite) == typeid(CFoePlaneSma))
								{
									m_score += 1;
								}

								m_foeBox.PushBoomFoe((*ite));
								ite = m_foeBox.m_lstFoe.erase(ite);
								IsBoom = true;
								break;
							}
							continue;
						}
						iteGun++;
					}


				}
				if (!IsBoom)
				{
					ite++;
				}
			}
			CheckLevelUp();
		}
		break;

		case CHANGE_PIC_TIMERID:
		{
			list<CFoePlane*>::iterator ite = m_foeBox.m_lstBoomFoe.begin();
			while (ite != m_foeBox.m_lstBoomFoe.end())
			{
				if (*ite)
				{
					if (--(*ite)->m_showid < 0)
					{
						delete (*ite);
						(*ite) = nullptr;
						ite = m_foeBox.m_lstBoomFoe.erase(ite);
						continue;
					}
				}
				ite++;
			}
		}break;


	}
}

void CPlaneApp::ShowScore()
{
	::putimage(0, 0, &m_board);

	wstring str = L"分数为: ";
	wchar_t arrscore[5] = { 0 };

	_itow_s(m_score, arrscore, 10);//数字转换成宽字节字符串
	str += arrscore;

	RECT rect{ 0, 0, 80, 50 };//显示文字的矩形区
	settextcolor(RGB(200, 172, 45));//文字颜色
	::drawtext(str.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);//文字显示到窗口的指定位置

}
void CPlaneApp::SetTimer()
{
	::SetTimer(hWnd, BACK_MOVE_TIMERID, BACK_MOVE_INTERVAL, nullptr);

	::SetTimer(hWnd,PLAYER_MOVE_TIMERID,PLAYER_MOVE_INTERVAL,nullptr);//以极高的频率检测是否按下方向键

	::SetTimer(hWnd, GUNNER_SEND_TIMERID, GUNNER_SEND_INTERVAL, nullptr);

	::SetTimer(hWnd, GUNNER_MOVE_TIMERID, GUNNER_MOVE_INTERVAL, nullptr);

	::SetTimer(hWnd, FOEBIG_CREATE_TIMERID, FOEBIG_CREATE_INTERVAL, nullptr);
	::SetTimer(hWnd, FOEMID_CREATE_TIMERID, FOEMID_CREATE_INTERVAL, nullptr);
	::SetTimer(hWnd, FOESMA_CREATE_TIMERID, FOESMA_CREATE_INTERVAL, nullptr);

	::SetTimer(hWnd, FOE_MOVE_TIMERID, FOE_MOVE_INTERVAL, nullptr);

	::SetTimer(hWnd, CHECK_HIT_TIMERID, CHECK_HIT_INTERVAL, nullptr);

	::SetTimer(hWnd, CHANGE_PIC_TIMERID, CHANGE_PIC_INTERVAL, nullptr);

}

void CPlaneApp::KillTimer()
{
	::KillTimer(this->hWnd, BACK_MOVE_TIMERID);

	::KillTimer(this->hWnd, PLAYER_MOVE_TIMERID);

	::KillTimer(this->hWnd, GUNNER_SEND_TIMERID);
	::KillTimer(this->hWnd, GUNNER_MOVE_TIMERID);

	::KillTimer(this->hWnd, FOESMA_CREATE_TIMERID);
	::KillTimer(this->hWnd, FOEMID_CREATE_TIMERID);
	::KillTimer(this->hWnd, FOEBIG_CREATE_TIMERID);

	::KillTimer(this->hWnd, FOE_MOVE_TIMERID);

	::KillTimer(this->hWnd, CHECK_HIT_TIMERID);

	::KillTimer(this->hWnd, CHANGE_PIC_TIMERID);

}

void CPlaneApp::CheckLevelUp()
{
	if (m_score >= scoreThreshold) {
		currentLevel++; 
		scoreThreshold += 10; 
		if (currentLevel > 3) {
			if (!tip)
			{
				tip = true;
				KillTimer();
				int result = ::MessageBox(hWnd, L"最高难度！", L"注意躲避", MB_OK);

				if (result == IDOK) {
					SetTimer();
				}
			}
			
		}
		else {
			KillTimer();
			int result = ::MessageBox(hWnd, L"进入下一关！", L"关卡升级", MB_OK);


			if (result == IDOK) {

				if (FOEBIG_CREATE_INTERVAL >= 1000 && FOEMID_CREATE_INTERVAL >= 1000 && FOESMA_CREATE_INTERVAL >= 1000)
				{
					FOEBIG_CREATE_INTERVAL -= 5000;
					FOEMID_CREATE_INTERVAL -= 3500;
					FOESMA_CREATE_INTERVAL -= 2000;
				}
				SetTimer();
			}

		}
			
	}

}
