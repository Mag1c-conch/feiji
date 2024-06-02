#pragma once
#include"../GameFrame/GameFrame.h"
#include"../BackGround/BackGround.h"
#include"../Player/Player.h"
#include"../GunnerBox/GunnerBox.h"
#include"../FoePlaneBox/FoePlaneBox.h"
class CPlaneApp :public CGameFrame {
public:
	CBackGround m_back;
	CPlayer m_player;
	CGunnerBox m_gunBox;
	CFoePlaneBox m_foeBox;
	int m_score;
	IMAGE m_board;
	int currentLevel;  // 当前关卡
	int scoreThreshold;  // 达到下一关所需的分数
	int FOEBIG_CREATE_INTERVAL;
	int FOEMID_CREATE_INTERVAL;
	int FOESMA_CREATE_INTERVAL;
	bool tip;
public:
	CPlaneApp();
	~CPlaneApp();
public:
	void ShowScore();
	void SetTimer();
	void KillTimer();
	void CheckLevelUp();
	virtual void InitGame();
	virtual void CloseGame();
	virtual void PaintGame();
	virtual void On_WM_KEYDOWN(BYTE key);
	virtual void On_WM_TIMER(WPARAM, LPARAM);

};
