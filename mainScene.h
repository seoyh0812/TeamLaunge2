#pragma once
#include "gameNode.h"
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

	RECT					_camMap;


public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	
	void yoonghoUpdate();
	void uiRender();

	
};

