#pragma once
#include "gameNode.h"
#include "tile.h"
#include "mapTool.h" // 디파인문 쓰려고
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include "interaction.h"

class mainScene :public gameNode
{
private:

	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;
	interaction*			_ia;

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void uiRender();
};

