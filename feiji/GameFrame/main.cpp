#include"GameFrame.h"
#include<Windowsx.h>


CGameFrame* pGame = nullptr;  

//���������������ĺ���
CGameFrame* CreateObject();
extern int wnd_pos_x;
extern int wnd_pos_y;
extern int wnd_width;
extern int wnd_height;
extern const TCHAR* wnd_title;


LRESULT CALLBACK WindowProc(_In_  HWND hwnd, _In_  UINT uMsg, _In_  WPARAM wParam, _In_  LPARAM lParam) {
	if (pGame->m_MsgMap.count(uMsg)) {   //��Ϣ����
		if (pGame->m_MsgMap[uMsg].MsgType == EX_MOUSE) {  //���Ϊ�����ص�
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };  //�����Ľṹ��
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_MOUSE)(po);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_KEY) { //���Ϊ������ص�

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_KEY)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_CHAR) { //�ַ�����

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_CHAR)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EX_WINDOW) { //��������

			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EX_WINDOW)(wParam, lParam);
		}

		if (uMsg != WM_PAINT) {
			RECT rect{ 0,0,wnd_width,wnd_height };   
			//�����ڵ�ĳ�������Ϊ��Ч�ģ������������ػ�
			::InvalidateRect(pGame->hWnd,  &rect,  FALSE);  //������������ĳ������Ϊ��Ч��
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
