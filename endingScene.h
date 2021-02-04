#pragma once
#include "gameNode.h"

enum RESULT
{
	VICTORY,
	DEFEAT
};

class endingScene : public gameNode
{
private:

	bool _isGameOver;
	RECT _mainSelectRc;
	RECT _exitSelectRc;
	RESULT _result;

public:
	endingScene();
	~endingScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

