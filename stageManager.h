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

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void setStage(STAGE stage);
};

