#include"GameFrame.h"
#include<Windowsx.h>


CGameFrame* pGame = nullptr;  

//声明创建子类对象的函数
CGameFrame* CreateObject();
extern int wnd_pos_x;
extern int wnd_pos_y;
extern int wnd_width;
extern int wnd_height;
extern const TCHAR* wnd_title;


LRESULT CALLBACK WindowProc(_In_  HWND hwnd, _In_  UINT uMsg, _In_  WPARAM wParam, _In_  LPARAM lParam) {
	if (pGame->m_MsgMap.count(uMsg)) {   //消息存在
		if (pGame->m_MsgMap[uMsg].MsgType == EX_MOUSE) {  //类别为鼠标相关的
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };  //坐标点的结构体
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_MOUSE)(po);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_KEY) { //类别为键盘相关的

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_KEY)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_CHAR) { //字符类型

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_CHAR)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_WINDOW) { //窗口类型

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_WINDOW)(wParam, lParam);
		}

		if (uMsg != WM_PAINT) {
			RECT rect{ 0,0,wnd_width,wnd_height };   
			//将窗口的某个区域变为无效的，会主动触发重绘
			::InvalidateRect(pGame->hWnd,  &rect,  FALSE);  //函数用来设置某个区域为无效的
		}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);  
}




int main() {
	pGame = CreateObject();
	pGame->InitGame(wnd_pos_x, wnd_pos_y, wnd_width, wnd_height, wnd_title);  
	

	while (!pGame->GetQuit()) {
		Sleep(1000);
	}

	if (pGame)
	{
		delete pGame;
		pGame = nullptr;
	}
	return 0;
}
