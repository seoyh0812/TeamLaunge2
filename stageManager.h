#pragma once
#include "gameNode.h"
#include "mapTool.h"

enum STAGE
{
	STAGE1,
	STAGE2,
	STAGE3
};

enum STAGEMOVE
{
	S_MOVE, S_UNMOVE
};

class stageManager : public gameNode
{
private:
	tagIsoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	STAGEMOVE			_sMove[TILEX * TILEY];					//맵툴에서 가져온 속성이 무브인지 언무브인지 담아둘 곳

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void setStage(STAGE stage);
	tagIsoTile* getIsoTile() { return _isoTile; }
	STAGEMOVE* getStageMove() { return _sMove; }
};

