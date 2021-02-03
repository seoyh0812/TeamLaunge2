#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include "interaction.h"

class mainScene :public gameNode
{
private:
	image*					_backGround;
	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;
	interaction*			_ia;

	int _alpha; // ������� �����Ű����

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	
	unitManager* getUM() { return _um; } // �̰� �÷��̱׶��忡�� �̴ϸ� �׸���� �ִ°�

	
};

