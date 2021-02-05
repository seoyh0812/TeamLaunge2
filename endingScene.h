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

	RECT _mainSelectRc;
	RECT _exitSelectRc;
	RECT _mainRc;
	RECT	_exitRc;
	RECT	_retryRc;
	RESULT _result;
	int _score;

public:
	endingScene();
	~endingScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

