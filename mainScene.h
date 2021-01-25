#pragma once
#include "gameNode.h"
#include "tile.h"
#include "mapTool.h" // �����ι� ������
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include "interaction.h"

class mainScene :public gameNode
{
private:
	tile _tiles[TILEX*TILEY];


	// 8���� �����ϴ��� �����ֱ�� ���۸� (���߿� �������)
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

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void uiRender();
};

