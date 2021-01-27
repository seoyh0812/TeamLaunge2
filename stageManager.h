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

enum tileObj
{
	S_NONE, S_TREE1, S_TREE2, S_TREE3, S_TREE4, S_TREE5, S_ZERGLING = 11
};

class stageManager : public gameNode
{
private:
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	STAGEMOVE			_sMove[TILEX * TILEY];					//�������� ������ �Ӽ��� �������� �𹫺����� ��Ƶ� ��
	tileObj				_tileObj[TILEX * TILEY];				//�������� ������ ������Ʈ �Ӽ��� �������� ��Ƶ� ��

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }
	STAGEMOVE* getStageMove() { return _sMove; }				//���� ,�𹫺� ����
	tileObj* getTileObj() { return _tileObj; }					//Ÿ���� ���� ������Ʈ �Ӽ� ����
};

