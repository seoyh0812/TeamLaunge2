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
	tile _tiles[TILEX*TILEY];


	// 8방향 어케하는지 보여주기용 저글링 (나중에 지울거임)
	RECT _zerling;
	float _destX, _destY, _x, _y, _angle;
	RECT _destRc;
	int _indexX, _indexY, _count;

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

