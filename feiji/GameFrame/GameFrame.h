#pragma once
#include<easyx.h>
#include<map>
#include <WinUser.h>

using namespace std;

//回调函数
LRESULT CALLBACK WindowProc(_In_  HWND hwnd, _In_  UINT uMsg, _In_  WPARAM wParam, _In_  LPARAM lParam);


#define INIT_MSGMAP(MSG_ID,MSG_TYPE)\
	m_MsgMap[MSG_ID].MsgType = MSG_TYPE;\
	m_MsgMap[MSG_ID].msgFun.p_fun_##MSG_TYPE = &CGameFrame::On_##MSG_ID;


class CGameFrame {

	//friend ：定义友元, WindowProc 函数是CGameFrame 的朋友，所以在朋友的函数里面可以直接使用私有的
	friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

protected:
	HWND hWnd;  
private:
	bool m_isQuit;   


	typedef void (CGameFrame ::* P_FUN_MOUSE)(POINT);  
	typedef void (CGameFrame::* P_FUN_KEY)(BYTE); 
	typedef void (CGameFrame::* P_FUN_CHAR)(WPARAM);
	typedef void (CGameFrame::* P_FUN_WINDOW)(WPARAM, LPARAM);  

	struct MsgFun {
		size_t MsgType;    //消息的类别
		union Fun {
			P_FUN_MOUSE p_fun_EX_MOUSE;   
			P_FUN_KEY p_fun_EX_KEY;   
			P_FUN_CHAR p_fun_EX_CHAR;  
			P_FUN_WINDOW p_fun_EX_WINDOW; 
		} msgFun;
	};

	map<UINT, MsgFun>  m_MsgMap;  //消息映射表

	void InitMsgMap() {
		    INIT_MSGMAP(WM_LBUTTONDOWN, EX_MOUSE)

			INIT_MSGMAP(WM_KEYDOWN, EX_KEY)

			INIT_MSGMAP(WM_CHAR, EX_CHAR)
			INIT_MSGMAP(WM_CLOSE, EX_WINDOW)
			INIT_MSGMAP(WM_PAINT, EX_WINDOW)
			INIT_MSGMAP(WM_TIMER, EX_WINDOW)
	}
public:
	CGameFrame() :m_isQuit(false) {
	}
	virtual ~CGameFrame() {
	}

	bool GetQuit() {
		return m_isQuit;
	}
public:
	void InitGame(int x, int y, int width, int height, const TCHAR* pTitle) {
		
		hWnd = ::initgraph(width, height);   

		::MoveWindow(hWnd, x, y, width, height, TRUE);

		
		::SetWindowText(hWnd, pTitle);

		::setbkcolor(RGB(255, 255, 255));   //白色
		::cleardevice();   //使设置的白色，立即生效

		//为 hWnd 窗口设定回调函数
		::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)&WindowProc);

		InitMsgMap(); 

		InitGame();

	}

	void On_WM_PAINT(WPARAM, LPARAM) {
		::BeginBatchDraw();  //批量绘图
		::cleardevice();  //清屏

		PaintGame();  

		::EndBatchDraw();  
	}
	void On_WM_CLOSE(WPARAM, LPARAM) {
		CloseGame();  
		::closegraph();  
		m_isQuit = true;  
	}


	virtual void InitGame() = 0;   
	virtual void CloseGame() = 0;
	virtual void PaintGame() = 0;
	virtual void On_WM_LBUTTONDOWN(POINT po) {}
	virtual void On_WM_KEYDOWN(BYTE key) {}  
	virtual void On_WM_CHAR(WPARAM wParam) {}
	virtual void On_WM_TIMER(WPARAM, LPARAM) {}
};

#define CREATE_OBJECT(CLASS)\
CGameFrame* CreateObject() {\
	return new CLASS;\
}

#define WND_PARAM(X,Y,WIDTH,HEIGHT,TITLE)\
int wnd_pos_x = X;\
int wnd_pos_y = Y;\
int wnd_width = WIDTH;\
int wnd_height = HEIGHT;\
const TCHAR* wnd_title = TITLE;

