#pragma once
#include "gameNode.h"
#include "tile.h"

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
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	STAGEMOVE			_sMove[TILEX * TILEY];					//�������� ������ �Ӽ��� �������� �𹫺����� ��Ƶ� ��

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }
	STAGEMOVE* getStageMove() { return _sMove; }
};

