#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:

public:
	titleScene();
	~titleScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

