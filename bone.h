#pragma once
#include "unit.h"
class bone :
	public unit
{

private:

public:
	bone();
	~bone();

	virtual HRESULT init(BELONG belong, float x, float y);	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	virtual void reRender();

	virtual void setState(STATE state);
};
