#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "loadingScene.h"
#include "mainScene.h"
#include "titleScene.h"
#include "endingScene.h"


class playGround : public gameNode
{
private:
	float _x; int _y;
	image* _backGround;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	
};

