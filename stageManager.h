#pragma once
#include "gameNode.h"
#include "tile.h"
#include "mapTool.h"

enum STAGE
{
	STAGE1,
	STAGE2
};


class stageManager : public gameNode
{
private:
	tile _tiles[TILENUMX*TILENUMY];
	STAGE _stage;

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void setStage(STAGE stage);
};

