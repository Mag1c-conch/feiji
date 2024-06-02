#pragma once
#include<list>
#include"FoePlane.h"
using namespace std;

class CFoePlaneBox {
public:
	list<CFoePlane*> m_lstFoe;
	list<CFoePlane*> m_lstBoomFoe;

public:
	CFoePlaneBox();
	~CFoePlaneBox();
public:
	void PushFoe(CFoePlane*);
	void PushBoomFoe(CFoePlane*);
	void ShowAllFoe();
	void ShowAllBoomFoe();
	void MoveAllFoe();
};

