#pragma once
#include "gameNode.h"
class endingScene : public gameNode
{
private:

public:
	endingScene();
	~endingScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

